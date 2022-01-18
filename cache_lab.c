#include "cachelab.h"


typedef struct {
    int valid; // 1 is valid
    int tag;
    int * block;
    int lru_stamp; // time stamp of LRU stratgy
} Line;

typedef struct {
    int S;
    int E;
    int B;
    Line *** lines;
} Cache;



int main()
{   
    
    printSummary(0, 0, 0);
    return 0;
}
