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


