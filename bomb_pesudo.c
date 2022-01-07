// rip is to find the global value
// rax return value
#include <stdio.h>

int main(){
    int a = 0; // rbx, callee-saved
    int x = 1; // rdi, 1st arg
    int y[5] = {1, 2, 3, 4, 5}; // rsi, 2nd arg
    
    if(x != 1){
        // jump to main + 0x16
        a = y[0];
        if(x != 2){
            // jump
        }else{
            x = y[1];
            y[0] = 0x4022b4;
            
        }
    }else{
        FILE * in_file  = fopen("name_of_file", "r"); // infile <- stdin
        initialize_bomb();
        
        // not finished

    }
}

void initialize_bomb(){
    
}
