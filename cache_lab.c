#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 100

typedef struct
{
    int valid; // 1 is valid
    int tag;
    int *block;
    int lru_stamp; // time stamp of LRU stratgy
} Line;

typedef struct
{
    int S;
    int E;
    int B;
    Line ***lines;
} Cache;

int main(int argc, char *argv[]) {
//  The following trivial example program uses getopt() to handle two program options: -n, with no as‐sociated value; and -t val, which expects an associated value.

    char * help_string = "Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile> \n"
                         "-h: Optional help flag that prints usage info\n"
                         "-v: Optional verbose flag that displays trace info\n"
                         "-s <s>: Number of set index bits (S = 2^s is the number of sets)\n"
                         "-E <E>: Associativity (number of lines per set)\n"
                         "-b <b>: Number of block bits (B = 2^b is the block size)\n"
                         "-t <tracefile>: Name of the valgrind trace to replay\n";

    int v_flag, s_val, E_val, b_val, opt;
    char * t_val; // name of trace file
    
    v_flag = 0;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt){
        case 'h':
            printf("%s", help_string);
            break;
        case 'v':
            v_flag = 1;
            break;
        case 's':
            s_val = atoi(optarg);
            break;
        case 'E':
            E_val = atoi(optarg);
            break;
        case 'b':
            b_val = atoi(optarg);
            break;
        case 't':
            t_val = optarg;
        default: /* '?' */
            fprintf(stderr, help_string,
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    FILE * file;
    file = fopen(strcat("traces/", t_val), "r");
    if(file == NULL){
        perror("Error opening file");
        return(-1);
    }

    char * input[MAX_SIZE];
    while(fgets(input, MAX_SIZE, file) != NULL){
        char cache_opt;
        unsigned int addr;
        int opt_size;
        for(int i = 0; input[i] != NULL && input[i] != '\n' ; ++i){
            char ch = input[i];
            int read_size_flag;
            read_size_flag = 0;
            if(ch == 'I'){

            }else if(ch == 'L'){

            }else if(ch == 'S'){

            }else if(ch == 'M'){

            }else if(ch == ','){

            }else if(ch == ' '){
                read_size_flag = 1;
            }else{
                if(read_size_flag == 1){
                    opt_size = (int)ch;
                }else{
                    
                }
            }
        }
        

    }




    if (optind >= argc)
    {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }
    printf("name argument = %s\n", argv[optind]);
    /* Other code omitted */
    exit(EXIT_SUCCESS);

    printSummary(0, 0, 0);
    return 0;
}
