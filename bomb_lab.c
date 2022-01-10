// rip is to find the global value

#include <stdio.h>

int main(){
    return 0;
}

void phase_1(int x, int y){
    // call string_not_equal    
}

int string_not_equal(char * x, char * y){
    return *x == *y ? 0 : 1;
}

int string_length(char* x){
    // rdx 3 arg
    // rdi 1 arg
    // rax return
    char * arg3 = x;
    char * res;
    do{
        arg3 = arg3 + 1;
        char * res = arg3 - x;
    }while(*arg3 == '0');
    return (int)(*res);
}

void read_six_numbers(int* a, int* b){
    // stack pointer + 0x18

    int* c = b;
    int* d = b + 0x4;
    int* r = b + 0x14;
    // store b + 0x14 at stack pointer + 0x8
    r = b + 0x10;
    // store b + 0x10 at stack pointer 
    int * r9 = b + 0xc;
    int * r8 = b + 0x8;
    b = 0x4025c3; // line 814
    r = 0x0;
    scanf("%d", &r);
    if(r > 5){
        return r;
    }else{
        explode_bomb();
    }

}

void phase_2(){
    // store pointer with space x28
    read_six_numbers();
    int * a; // rbp
    int * b; // rbx
    int * p = 0;
    if(p != 1){ //
        explode_bomb();
    }
    b = p + 0x4;
    a = p + 0x18;
    int *res = b - 0x4;
}

void phase_3(){
    char * p;
    
    char * arg4 = p + 0xc;
    char * arg3 = p + 0x8;
    char * arg2 = 0x4025cf; // format string is "%d %d"
    char r = 0x0;
    r = sscanf(arg1, "%d, %d");
    if(r <= 1){
        explode_bomb();
    }
    if(p + 0x8 > 0x7){
        explode_bomb();
    }
    r = p + 0x8;
    // jump to 0x402470 + 8 * &r
    // after I learnt how to use gdb
    // one acceptable answer is input 1, 311

}

void phase_4(){
    char * p;
    char * arg1;
    int r;
    char * arg4 = p + 0xc;
    char * arg3 = p + 0x8;
    char * arg2 = 0x4025cf; // format string is "%d %d"
    r = sscanf(arg1, "%d, %d");
    if(r != 2){
        explode_bomb();
    }
    if(*arg3 > 0xe){
        
    }
    * arg3 = 0xe;
    * arg2 = 0x0;
    * arg1 = p + 0x8;
    *r = func4();// first_input, 0, 0xe
    if(*r != 0){
        explode_bomb(); 
    }
    if(* arg4 != 0){
        explode_bomb(); 
    }
    return;
}


void func4(){
    char * arg1;
    char * arg4;
    char * arg3;
    char * arg2;
    char * r = *arg3 - *arg2; // 14
    *arg4 = *r;               // 
    *arg4 >>= 31;
    *r += *arg4;
    *r /= 2;    // 7
    *arg4 = *r + *arg2; // 7
    if(*arg4 <= *arg1){ // input >= 7
        *r = 0x0;
        if(*arg4 < *arg1){ 
            *arg2 = *arg4 - 0x1; // 7 - 1
            *r = func4(); // first_input, 6, 14
            r = 2 * r + 1;
        }
    }else{
        arg3 = arg4 - 1;  // first_input, 0, 7
        *r = func4();
        *r *= 2;
    }
    return *r;
}

void phase_5(){
    char * a;
    char * arg1;
    a = arg1;
    char * r = scanf();
    if(r != 6){
         explode_bomb();
    }
    * r = 0;
    char * arg4 = * (*arg1 + *r ); // *arg4 = *arg1
    char * arg3 = * arg4; // left only 1 byte
    // accept an array in a length of 6
    // make the last 1 byte as offest, to get an another array of flyers
    // 
}

void phase_6(){
    read_six_numbers();
    // check if these numbers are duplicated
    // check all number must be in 1 to 6
    
    
}

// see the node structure, construct a linked list
// make them decreasing

0x6032d0 <node1>:       0x000000010000014c      0x00000000006032e0
0x6032e0 <node2>:       0x00000002000000a8      0x00000000006032f0
0x6032f0 <node3>:       0x000000030000039c      0x0000000000603300
0x603300 <node4>:       0x00000004000002b3      0x0000000000603310
0x603310 <node5>:       0x00000005000001dd      0x0000000000603320
0x603320 <node6>:       0x00000006000001bb      0x0000000000000000

// final answer
Border relations with Canada have never been better.
1 2 4 8 16 32
1 311
7 0
ionefg
4 3 2 1 6 5
