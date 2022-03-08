#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_CHAR 1024
#define MAX_TOKEN_NUM 32

struct Node {
    char *key;
    char **val;
    struct Node *next;
    struct Node *prev;
};
struct Node *head;
struct Node *tail;



char *output_literal[] = {"mysh> ",
                          "Usage: mysh [batch-file]\n",
                          "Error: Cannot open file ",
                          "Redirection misformatted.\n",
                          "unalias: Incorrect number of arguments.\n",
                          "alias: Too dangerous to alias that.\n",
                          ": Command not found.\n"};

char **split_line(char *text, int model) { // caller should call free()
    char **argv = malloc(MAX_TOKEN_NUM * sizeof(char *));
    char *token;
    int arg_index = 0;
    token = strtok(text, " \n\t");
    while (token != NULL && arg_index < MAX_TOKEN_NUM) {
        argv[arg_index] = malloc(MAX_TOKEN_NUM * sizeof(char));
        strcpy(argv[arg_index++], token);
        token = strtok(NULL, " \n\t");
    }
    argv[arg_index] = NULL;
    for(int i = 0; i < arg_index; ++i){
        if(strstr(argv[i], ">") != NULL && strlen(argv[i]) != 1){// it contains attached >, e.g. hello>file.txt
            int offset = 0;
            int len = strlen(argv[i]);
            int p = 0; // index of > character
            while(argv[i][p] != '>'){
                p++;
            }
            offset = (p == 0 || p == len - 1) ? 1 : 2;

            for(int j = arg_index - 1 + offset; j > i; --j){   // move argv backwards
                if(argv[j] == NULL) argv[j] = malloc(MAX_TOKEN_NUM * sizeof(char));
                if(j > i + offset){
                    strcpy(argv[j], argv[j - offset]);
                }

            }

            char temp[MAX_TOKEN_NUM];
            strcpy(temp, argv[i]);
            if(p == 0){
                memset(argv[i + 1], '\0', MAX_TOKEN_NUM * sizeof(char));
                strncpy(argv[i + 1], temp + 1, len - 1);
                strcpy(argv[i], ">");
            }else if(p == len - 1){
                memset(argv[i], '\0', MAX_TOKEN_NUM * sizeof(char));
                strncpy(argv[i], temp, len - 1);
                strcpy(argv[i + 1], ">");
            }else{
                memset(argv[i], '\0', MAX_TOKEN_NUM * sizeof(char));
                strncpy(argv[i], temp, p);
                memset(argv[i + 2], '\0', MAX_TOKEN_NUM * sizeof(char));
                strncpy(argv[i + 2], temp + p + 1, len - 1 - p);
                strcpy(argv[i + 1], ">");
            }
        }
    }



    return argv;
}
char **redirection_valid_check(int *rd_flag, char *text) { // -1 bad redirection arg, 1 valid redirection arg, 0 non-redirection
    int rd_cnt = 0;
    char **argv = split_line(text, 1); // cut all arg
    for (int i = 0; argv[i] != NULL; ++i) {
        if (strcmp(argv[i], ">") == 0) {
            rd_cnt++;
            if (i == 0 || rd_cnt > 1 || argv[i + 1] == NULL ||
                argv[i + 2] != NULL) { // begin with > || more than one > command || end with > || > to file1 and file2
                *rd_flag = -1;
                return NULL;
            }

        }
    }
    *rd_flag = rd_cnt;
    return argv;
}
void print_promote(int output_id, int _fd) {
    write(_fd, output_literal[output_id], strlen(output_literal[output_id]));
}
void print_alias(char *_key, int _fd) { // if key == NULL, print all alias. else print specific alias
    struct Node *node = head->next;
    while (node != tail) {
        char *key = node->key;
        if (_key == NULL || strcmp(key, _key) == 0) {
            write(_fd, key, strlen(key));
            char **val = node->val;
            for (int i = 0; val[i] != NULL; ++i) {
                write(_fd, " ", strlen(" "));
                write(_fd, val[i], strlen(val[i]));
            }
            write(_fd, "\n", strlen("\n"));
        }
        node = node->next;
    }
}
void set_output(int *rd_ret, char ***child_argv, char **output_filename, char *text) {
    *child_argv = redirection_valid_check(rd_ret, text);
    if (*rd_ret == -1) {
        print_promote(3, STDERR_FILENO);
        return;
    }
    if (*rd_ret == 1) {
        int i = 0;
        while (strcmp((*child_argv)[i], ">") != 0) {
            i++;
        }
        *output_filename = (*child_argv)[i + 1];
        (*child_argv)[i] = NULL;
    }
}
int check_alias(char *text) { // return 1 when found alias request, 0 not found request,
    char *ret_alias = strstr(text, "alias");
    char *ret_unalias = strstr(text, "unalias");
    if (ret_alias && ret_unalias == NULL) { // found alias
        char **argv = split_line(text, 1);
        if (argv[1] == NULL) { // only typed "alias", display all stored alias
            print_alias(NULL, 1);
            return 1;
        }

        if (strcmp(argv[1], "alias") == 0 ||
            strcmp(argv[1], "unalias") == 0 ||
            strcmp(argv[1], "exit") == 0) { // check danger words: "alias, unalias and exit" as alias
            print_promote(5, 2);
            return 1;
        }

        struct Node *p = head->next; // update existed key-val
        while (p != NULL) {
            if (p->key != NULL && strcmp(p->key, argv[1]) == 0) {
                int i = 0;
                if(argv[2] != NULL){     // update, do not print
                    do {
                        strcpy(p->val[i], argv[i + 2]);
                        i++;
                    } while (argv[i + 2] != NULL);

                }else{
                    print_alias(p->key, 1); // not change, print key-val pair of alias
                }

                return 1;
            }
            p = p->next;
        }

        // create a new node
        char *key = (char *) malloc(MAX_TOKEN_NUM * sizeof(char));
        char **val = (char **) malloc(MAX_TOKEN_NUM * sizeof(char *));
        strcpy(key, argv[1]);
        int i = 0;
        do {
            val[i] = (char *) malloc(MAX_TOKEN_NUM * sizeof(char));
            strcpy(val[i], argv[i + 2]);
            i++;
        } while (argv[i + 2] != NULL);
        struct Node *node = (struct Node *) malloc(sizeof(struct Node));
        node->key = key;
        node->val = val;
        struct Node *prev_tail = tail->prev;
        prev_tail->next = node;
        node->prev = prev_tail;
        node->next = tail;
        tail->prev = node;
        return 1;
    }

    if (ret_unalias) {
        char **argv = split_line(text, 1);
        if ((argv[1] != NULL && argv[2] != NULL) || argv[1] == NULL) { // too much argv for "unalias" || empty arg
            print_promote(4, 1);
            return 1;
        }
        struct Node *p = head->next; // delete existed key-val
        while (p != NULL) {
            if (p->key != NULL && strcmp(p->key, argv[1]) == 0) {
                int i = 0;
                while (p->val[i] != NULL) {
                    free(p->val[i]);
                    i++;
                }
                free(p->key);
                p->prev->next = p->next;
                p->next->prev = p->prev;
                free(p);
                return 1;
            }
            p = p->next;
        }
    }

    return 0;
}
void command_expanding(char ***argv) {

    // search for possible alias
    char *key = *(argv)[0];
    char **val = NULL;
    struct Node *node = head->next;
    while (node != tail) {
        if (strcmp(node->key, key) == 0) {
            val = node->val;
        }
        node = node->next;
    }
    if (val == NULL) return;
    int offset = 0;
    while (val[offset] != NULL) {
        offset++;
    }
    int p = 0;
    while ((*argv)[p] != NULL) {
        p++;
    }
    p--;
    while (p > 0) { // move argv back of "offset" distance
        (*argv)[offset + p] = (char *) malloc(MAX_TOKEN_NUM * sizeof(char));
        strcpy((*argv)[offset + p], (*argv)[p]);
        p--;
    }
    for (int i = 0; i < offset; ++i) { // allocate alias to argv array
        (*argv)[i] = (char *) malloc(MAX_TOKEN_NUM * sizeof(char));
        strcpy((*argv)[i], val[i]);
    }

}

int main(int argc, char *argv[]) {

    head = (struct Node *) malloc(sizeof(struct Node));
    tail = (struct Node *) malloc(sizeof(struct Node));
    head->next = tail;
    tail->prev = head;
    char *file_path = NULL;

    if (argc == 2) {
        file_path = argv[1];
    }
    if (argc > 2) {
        print_promote(1, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    char text[MAX_INPUT_CHAR];

    FILE *file;

    if (file_path == NULL) {
        print_promote(0, 1);
        file = stdin;
    } else {
        file = fopen(file_path, "r");
        if (file == NULL) {
            print_promote(2, STDERR_FILENO);
            write(STDERR_FILENO, file_path, strlen(file_path));
            write(STDERR_FILENO, ".\n", strlen(".\n"));
            exit(1);
        }
    }

    while ((fgets(text, MAX_INPUT_CHAR, file)) != NULL) {

        if(file_path != NULL)
            write(1, text, strlen(text));
        if(strcmp(text, "exit\n") == 0) exit(0);
        int alias_ret = check_alias(text);
        if (alias_ret == 0) {
            int rd_ret;
            char *output_filename = NULL;
            char **child_argv = NULL;
            set_output(&rd_ret, &child_argv, &output_filename, text);

            if (rd_ret != -1) {
                command_expanding(&child_argv);
                pid_t child_pid = fork();
                if (child_pid == 0) { // child process
                    if (rd_ret == 1) { // redirection
                        fclose(stdout);
                        fopen(output_filename, "w");
                    }
                    execv(child_argv[0], child_argv);
                    write(STDERR_FILENO, child_argv[0], strlen(child_argv[0]));
                    print_promote(6, STDERR_FILENO);
                    _exit(1);
                } else if (child_pid < 0) {
                    // fork failed
                    // TODO
                } else { // parent process
                    waitpid(-1, 0, 0); // -1 wait for any child process
                }
                free(child_argv);
            }
        }
        if (file_path == NULL) { // next round promotion
            print_promote(0, 1);
        }
    }

    fclose(file);
    return 0;
}
