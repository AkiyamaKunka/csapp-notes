#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>

#define MAX_SIZE 100
#define TIME_STP 0x7fffffff // to be time_stamp of LRU

typedef struct
{
    int valid; // 1 is valid
    int tag;
    int * block;
    int lru_stamp; // time stamp of LRU stratgy
} Line;

typedef struct
{
    int S;
    int E;
    int B;
    Line *** lines;
} Cache_Type;

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

void init_cache(int s, int E, int b){
    cache->S = (1 << s);
    cache->E = E;
    cache->B = (1 << b);
}

void alloc_cache(){
    cache->lines = (Line *** )malloc(cache->S * sizeof(Line **));
    for(int i = 0; i < cache->S; ++i){
        cache->lines[i] = (Line **)malloc(cache->E * sizeof(Line *));
    }
    for(int i = 0; i < cache->S; ++i){
        for(int j = 0; j < cache->E; ++j){
            cache->lines[i][j] = (Line *)malloc(sizeof(Line));
        }
    }
    for(int i = 0; i < cache->S; ++i){
        for(int j = 0; j < cache->E; ++j){
            cache->lines[i][j]->valid = 0;
            cache->lines[i][j]->block = (int*)malloc(cache->B * sizeof(int*)); // it should divided by 4 theoretically, but this lab do not need block area
            cache->lines[i][j]->tag = 0;
            cache->lines[i][j]->lru_stamp = TIME_STP; // LRU init value
        }
    }
}

void access_cache(unsigned int addr, int size){
    cur_time -= 1;
    unsigned int tag = (addr >> (s_val + b_val));
    unsigned int set_index =(addr << (32 - s_val - b_val) >> (32 - s_val));
    unsigned int offset = (addr << (32 - b_val) >> (32 - b_val));
    int find_flag = 0;
    int capacity = 0;
    for(int j = 0; j < cache->E; ++j){
        if(cache->lines[set_index][j]->valid == 1){
            capacity += 1;
        }
        if(cache->lines[set_index][j]->valid == 1 && cache->lines[set_index][j]->tag == tag){ // hit
            if(v_flag == 1){
                printf(" hit");
            }
            cache->lines[set_index][j]->lru_stamp = cur_time;
            find_flag = 1;
            hit_cnt += 1;
        }
    }
    if(find_flag == 0){ // miss
        miss_cnt += 1;
        if(v_flag == 1){
            printf(" miss");
        }
        if(capacity != E_val){ // not full, store it at empty place
            for(int j = 0; j < cache->E; ++j){
                if(cache->lines[set_index][j]->valid == 0){
                    cache->lines[set_index][j]->valid = 1;
                    cache->lines[set_index][j]->tag = tag;
                    cache->lines[set_index][j]->lru_stamp = cur_time;
                    break;
                }
            }
        }else{ // full, evication
            if(v_flag == 1){  
                printf(" eviction");
            }
            evict_cnt += 1;
            int time_cmp = TIME_STP;
            int evict_pos = 0;
            for(int j = 0; j < cache->E; ++j){
                if(cache->lines[set_index][j]->lru_stamp){
                    time_cmp = cache->lines[set_index][j]->lru_stamp;
                    evict_pos = j;
                }
            }
            cache->lines[set_index][evict_pos]->tag = tag;
            cache->lines[set_index][evict_pos]->lru_stamp = cur_time;
        }
    }
    if(v_flag == 1){  
        printf("\n");
    }
}

    char * help_string = "Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile> \n"
                         "-h: Optional help flag that prints usage info\n"
                         "-v: Optional verbose flag that displays trace info\n"
                         "-s <s>: Number of set index bits (S = 2^s is the number of sets)\n"
                         "-E <E>: Associativity (number of lines per set)\n"
                         "-b <b>: Number of block bits (B = 2^b is the block size)\n"
                         "-t <tracefile>: Name of the valgrind trace to replay\n";

    int v_flag, s_val, E_val, b_val, opt;
    int hit_cnt;
    int miss_cnt;
    int evict_cnt;
    char * t_val; // name of trace file
    int cur_time;
    Cache_Type * cache;



int main(int argc, char *argv[]) {
//  The following trivial example program uses getopt() to handle two program options: -n, with no as‐sociated value; and -t val, which expects an associated value.
    hit_cnt = 0;
    miss_cnt = 0;
    evict_cnt = 0;
    v_flag = 0;
    cur_time = TIME_STP;
    while ((opt = getopt(argc, argv, "hvs:E:b:st:")) != -1) {
        //printf("We are in argument section, %c\n", opt);
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
            break;
        default: /* '?' */
            fprintf(stderr, "Error input\n",
                    argv[0]);
            printf("Error is , %c\n", opt);
            exit(EXIT_FAILURE);
        }
    }

    init_cache(s_val, E_val, b_val);
    alloc_cache();

    printf("We are out of argument section");
    FILE * file;
    file = fopen(t_val, "r");
    if(file == NULL){
        perror("Error opening file");
        return(-1);
    }

    char input[MAX_SIZE];
    while(fgets(input, MAX_SIZE, file) != NULL){
        char cache_opt;
        unsigned int addr;
        int opt_size;
        if(v_flag == 1){
            printf("%s", input);
        }
        for(int i = 0; input[i] && input[i] != '\n' ; ++i){
            char ch = input[i];
            int read_size_flag;
            read_size_flag = 0;
            if(ch == 'I'){
                cache_opt = 0;
            }else if(ch == 'L'){
                cache_opt = 1;
            }else if(ch == 'S'){
                cache_opt = 1;
            }else if(ch == 'M'){
                cache_opt = 2;
            }else if(ch == ','){
                continue;
            }else if(ch == ' '){
                read_size_flag = 1;
            }else{
                if(read_size_flag == 1){
                    opt_size = hex2int(ch);
                }else{
                    addr = addr * 16 + hex2int(ch);
                }
            }
        }
        int opt_tag = 32 - s_val - b_val;
        int 
        

        


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
