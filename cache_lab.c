#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
                         
    int h_flag, v_flag, s_val, E_val, b_val, t_val;
    h_flag = 0;
    v_flag = 0;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt){
        case 'h':
            h_flag = 1;
            break;

        case ''


        case 'n':
            flags = 1;
            break;
        case 't':
            nsecs = atoi(optarg);
            tfnd = 1;
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n",
           flags, tfnd, nsecs, optind);

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
