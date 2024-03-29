# Notes on _Computer System: A Programmer's Perspetive_

Author: Kunka Akiyama

Create : 28 Nov 2021

Update: 30 Oct 2022

## C Language (recorded the my most confusing part)

### Some Conception

* `&` operator, referencing, get address
* `*` operator, deferencing. retrive value by address
* call by value, see code below, it change nothing!
* `structA a`, `a.b` reference to member of struct object
* `structA * a` `a->b`, reference to a member of struct, via a pointer pointing to a struct object, equals to `(*a).b`


```c
int main()
{
    int a = 10, b = 20;
    swapx(a, b);
    return 0;
}
void swapx(int x, int y)
{
    int t;
    t = x;
    x = y;
    y = t;
}
```

* Call by reference(fake), which also means "pass value of address to the function", this will swap the value a and b in `main()` However, this is not a real "reference", C implement this by copy the value of pointer in function entrance, and deference them when need.

```c
int main()
{
    int a = 10, b = 20;
    swapx(&a, &b);
    return 0;
}

void swapx(int* x, int* y)
{
    int t;
    t = *x;
    *x = *y;
    *y = t;
}
```

* `function(int * p)`, here "p" is a "pointer" type, which is "int *" in syntax. p stores an value of address. (Note this is not dereferencing operation!, it's a type)

### C++ content, comparing to C

* `int &x`, a reference type in C++, if `int & x = y;`, we will think x is exactly the same of y

* A real "call by reference in C++"

```cpp
//---------C++ Call by Reference-----------------------------//
unsigned long x = 4;
void func1(unsigned long& val) {
     val = 5;            
}
func1(x);

//---------C Call by referecen(copy pointer value in fact)----//
void func2(unsigned long* val) {
     *val = 5;
}
func2(&x);
```

* Rule of Thumb:

Use pointers if you want to do pointer arithmetic with them (e.g. incrementing the pointer address to step through an array) or if you ever have to pass a NULL-pointer.

Use references otherwise.


## Computer Network

### Basic of Network

* Type1: Host(Adapter) -> Hub(1Mbps) -> Bridge(1Gbps) = LAN

* Type2 : Host + Host = LAN -> Router + Router = WAN

Internet Protocol will define:

* Naming Scheme
* Delivery Mechanism

Data Transformation from Host A to Host B

LAN1 Frame Header: to router

Frame include internet Header: to Host B

Router fetch internet Header,  then create a new LAN2 Frame Header, to Host B, forward it to LAN2 adapter2

LAN2 adapter forward it to host B, then protocol software strips off the two headers, send it to server's address

### The Global IP Intenet

IP Protocol: unreliable, from host to host

UDP(Unreliable Datagram Protocol): extended IP, from process to process

#### Internet Properties:

* The set of hosts is mapped to a set of 32-bit *IP addresses.*
* The set of IP addresses is mapped to a set of identifiers called *Internet domain names.*
* A process on one Internet host can communicate with a process on any other Internet host over a *connection*.

#### IPv4 vs Ipv6

* The original Internet protocol, with its 32-bit addresses, is known as Internet Protocol Version 4 (IPv4).
* Internet Protocol Version 6 (IPv6), that uses 128-bit addresses and that was intended as the successor to IPv4.

#### IP address presented:

```
0x8002c2f2 = 128.2.194.242 (dotted-decimal representation)
```

ICANN (Internet Corporation for Assigned Names and Numbers) maintain the first-level domain names

Their DNS Database define millions of host-entries, mappping from domain names to IP addresses.

```
localhost -> *loopback address* 127.0.0.1:

multiple domain name -> same IP address
```

In the most general case, multiple domain names are mapped to the same set of multiple IP addresses:

```shell
linux> *nslookup www.twitter.com* 
 Address: 199.16.156.6
 Address: 199.16.156.70
 Address: 199.16.156.102 Address: 199.16.156.230
```

### Internet Connections

A *socket* is an end point of a connection

* Web servers typically use port 80, and email servers use port 25. 

* Web service is http, and the well-known name for email is smtp.

* The mapping between well-known names and well-known ports is contained in a file called /etc/services.

This pair of socket addresses is known as a *socket pair* and is denoted by the tuple

```
(*cliaddr*:*cliport*, *servaddr*:*servport*)
```

### The Sockets Interface

* A set of functions in conjuction with Unix I/O functions
* Implemented by UCB

```c
  /* IP socket address structure */
  struct sockaddr_in  {
    uint16_t        sin_family;  /* Protocol family (always AF_INET) */
    uint16_t        sin_port;    /* Port number in network byte order */
    struct in_addr  sin_addr;    /* IP address in network byte order */
    unsigned char   sin_zero[8]; /* Pad to sizeof(struct sockaddr) */
};
/* Generic socket address structure (for connect, bind, and accept) */
struct sockaddr {
        uint16_t  sa_family;    /* Protocol family */
        char      sa_data[14];  /* Address data  */
    };

```

### Create Socket Descriptor

```c
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain, int type, int protocol);

clientfd = Socket(AF_INET, SOCK_STREAM, 0);

```

This end point socket in client side is not opened yet.

### Call Connect Function

```c
#include <sys/socket.h>
int connect(int clientfd, const struct sockaddr *addr,
            socklen_t addrlen);
```

Establish an Internet connection with server

 resulting connection is characterized by the socket pair

```c
 (x:y, addr.sin_addr:addr.sin_port)
// x is client IP, y is ephemeral port
```

### Call bind/listen/accept Function

These socket functions are used by **servers** to establish connections with clients.

```c
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr,
         socklen_t addrlen);
// The bind function asks the kernel to associate the server’s socket address in addr with the socket descriptor sockfd.
int listen(int sockfd, int backlog);
// 
int accept(int listenfd, struct sockaddr *addr, int *addrlen);
```

#### *socket* *address*:

* TCP/IP creates the *socket* *address* as an identifier that is unique throughout all Internet networks
* TCP/IP concatenates the Internet address of the local host interface with the port number to devise the Internet socket address.

#### *file descriptor:* 

* a unique identifier for a file or other input/output resource, such as a pipe or network socket. 
* Typically have non-negative integer values, with negative values being reserved to indicate "no value" or error conditions

## Linking

### Kinds of Object Files

* Relocatable File (.o), Generate by Compilers + Assembler

* Executable Object File (a.out file), by Linkers, can be copied into memory and execute
* Shared Object File (.so file), can be loaded into memory and linked dynamically

### Kinds of Symbol Types

* Global Symbol: defined by module m, correspond to nonstatic function and variable defined by module m
* External Symbol: defined by other module, correspond to nonstatic function and variable outside
* Local Symbol: static C function and static variable, cannot be referecened by other module

### Resolve Duplicate Symbol Names

* Strong symbol: functions and initialized global
* Weak symbol: Uninitialized global variables

### Rules of Compiler

* No multiple Strong
* Pick 1 Strong among weak
* Randomly pick 1 weak from all weak

## Memory Hierachy

### Cache Hit

Program need object data `d` from level `k + 1`, the cache at level `k` happen to hold this data

### Cache Miss

Program need object data `d` from level `k + 1`, the cache at level `k`  does not hold this data

* Process of overwriting an existing block is called __replacing__ or __evicting__
* The behavior of __evicting__ would be governed by __cache replacement policy__

Empty cache is also called __cold cache__, the miss is called __compulsory miss__ or __cold miss__

### Restrictive Placement Policy

For example, element in level k + 1 use  `index mod 4`  to place to level k

But __conflict miss__ would happen, if you constantly access to index 0 and index 8

If cache capacity < __working set__,(e.g. a loop use 2 virarble but cache can only contain 1) then performance will be damaged, called __capacity misses__

### Cache Management

Software and Hardware both can manage cache

* Registers: by compiler
* L1, L2, L3 Caches, managed by hardware logic on CPU
* DRAM main memory: serves as "cache" for disks, by OS + address hardware on CPU
* AFS, serves as local disk cache, by AFS client process on local machine

### Cache Memory Access Time

* L1 cache : 4 clock cycles
* L2 cache: 10 clock cycles
* L3 cache: 50 clock cycles

### Cache Organization

(S, E, B, m)

M = 2 ^ m, M unique address represent by m bits,

S = 2 ^ s, number of sets

B = 2 ^ b, bytes one block can represent

Each block contains 

* tag, t = m - s - b, 2 b
* valid bit
* b bits of information

C(capacity) = S * E * B

### Why Cache use middle-bits to index?

By doing that, cache can contain contigous data in the memory, ultilize the benefit of spatial locality!

### Locality

* Temporal Locatlity: repeatly reference the same variable
* Spatial Locality: sequentially fetch the nearby elements
* Loops: have good temporal, spatial and instruction fetches

### Reference Pattern

* Stride-1 reference pattern: To visit each element of a vector sequentially
* Stride-k reference pattern: To visit every kth elemtn of a contiguous vector
* Stride increases, spatial locality decreases

## Program Optimization

### Methods

* Avoid stupid operation
* Unrolling Loop + Prallel Calculation
* Predict Branching

## Machine Level Programming

### Variable - Size Stack Frames

`%rbp` original value will first stored by the callee by:

```assembly
pushq %rbp
```

Then `%rbp` will store the value `%rsp`, because the size of stack is uncertain

```assembly
movq %rsp, %rbp
```

After the function the done, the last two things are:

Set `%rsp` point to where store the `%rbp`value

```assembly
movq %rbp, %rsp
```

Then pop the value back to `%rbp`, but notice that the `%rsp` will also increase 8 by `popq`operation

```assembly
popq %rbp
```

Finally `%rsp`point at the `return address`, `ret`will make the `rip`point to this address and return to the `caller`address

### Buffer Overflow Attack

#### Attack Methods:

1. Example in`gets()`, input more chars than it can hold, then overwrite the `return address`
2. Using `nop sled` to make the `program counter` jump to many "nop" instruction, and finally excutate attacker's code `nop` is short for "no operation". 

#### Agaisnt Buffer Overflow Attack Methods:

1. Randomlization to the programm starting address (and other part)
2. Mark portions of code in memory from input only "readable" but not "excutable"
3. Set a `canary` as checker beyond called function

### Memory Model on x86-64 Machine : Byte-Orientated

* 1 address location store 1 byte of data

* 8 bytes in the same line

### Segmentation fault

Segmentation fault is a specific kind of error caused by accessing memory that “does not belong to you.”

A common way to get a segfault is to dereference a null pointer:

```cpp
int *p = NULL;
*p = 1;
```

### Little-Endianness

* x86-64 architechture uses little-endianness, while TCP/IP network use big-endianness

* little-endianness refers to the byte ordering where the least significant byte is stored first.

For example, 0x12345678 store in memory with little-endianness is:

```assembly
78 56 34 12
```

Another example, to store an array

```c
int a[] = {0x12345678, 0x9abcdef0};
```

```assembly
0x00: 78 56 34 12
0x04: f0 de bc 9a
```

Why Little-endianess is good for computer:

```c
// In the case of 64 bit compilers, long long is the same size as long. They are both 8 bytes.
unsigned long long x = 0x0000000000000042;
unsigned long long * x_p = &x;
unsigned int * y_p = (unsigned int *)x_p;
unsigned int y = *y_p;
printf("y = %#.8x\n", y); // prints in hex with '0x' and with all leading zeros
```

Assume `y` and `x` all points to `0x00` in adress

```
0x00: 42 00 00 00
0x04: 00 00 00 00
```

We get exactly what you would expect to get: `y = 0x00000042`, even we do a "pointer down cast"

### Programm Encoding

```````shell
linux> gcc -0g -o p p1.c p2.c
```````

1. C *Preprocesssor* expand Macro, add code from file that concluded by source file with `#include`, generate `p1.i` `p2.i`
2. *Compiler* generate assembly file `p1.s`, `p2.s`
3. *Assembler* convert them to object file `p1.o` ` p2.o`, which is binary
4. *Linker* merge the two file, along with code of function (e.g. printf) to the executable file "p" as sepcifed with `-o p`

### GCC command option

* -S: compile, then stop
* -c: compile and assemble
* -Og, -O1, O2: Compile and optimized code with level g, 1, 2...

### objdump Usage

Command:

```shell
objdump -d ctarget > asm_ctarget.txt
```

to disassmble binary file and store the result to txt file

### Instruction Convention on Registers

* 1-2 Bytes Operation, leave other bits unchanged
* 4 Bytes Operation, set upper bits to zero

### Registers Convention

In the assembly syntax accepted by `gcc`, register names are always prefixed with `%`. All of these registers are 64 bits wide.

The register file is as follows:

| Register   | Purpose                                | Saved across calls |
| ---------- | :------------------------------------- | ------------------ |
| `%rax`     | temp register; return value            | No                 |
| `%rbx`     | callee-saved                           | Yes                |
| `%rcx`     | used to pass 4th argument to functions | No                 |
| `%rdx`     | used to pass 3rd argument to functions | No                 |
| `%rsp`     | stack pointer                          | Yes                |
| `%rbp`     | callee-saved; base pointer             | Yes                |
| `%rsi`     | used to pass 2nd argument to functions | No                 |
| `%rdi`     | used to pass 1st argument to functions | No                 |
| `%r8`      | used to pass 5th argument to functions | No                 |
| `%r9`      | used to pass 6th argument to functions | No                 |
| `%r10-r11` | temporary                              | No                 |
| `%r12-r15` | callee-saved registers                 | Yes                |

For the code generation phase of the project you will not be performing register allocation. You should use %r10 and %r11 for temporary values that you load from the stack.

### Caller-saved and Callee-saved

> **Caller-saved registers** (AKA **volatile** registers, or **call-clobbered**) are used to hold temporary quantities that need not be preserved across calls.

For that reason, it is the caller's responsibility to push these registers onto the stack or copy them somewhere else *if* it wants to restore this value after a procedure call.

It's normal to let a `call` destroy temporary values in these registers, though.

> **Callee-saved registers** (AKA **non-volatile** registers, or **call-preserved**) are used to hold long-lived values that should be preserved across calls.

When the caller makes a procedure call, it can expect that those registers will hold the same value after the callee returns, making it the responsibility of the callee to save them and restore them before returning to the caller. Or to not touch them.

## Floating Point

Floating Point IEEE Expression: $$V = (-1)^S M 2 ^E$$

S: Sign, determine whether it's positive or negative

M: Significand, also called Mantissa, $M \neq frac$

E:  Exponent, weights value by power of 2, $E \neq exp$

$$Bias = 2^{(k-1)} - 1$$, K is number of exponent bits

* Single precision:127
* Double precision: 1023

### Denormalized Numbers

$ M = 0.xxxx$

$$ E = 1 - Bias$$

Denormalized Numbers are designed to represent the values who are very close to 0

### Normalized Numbers

$ M = 1.xxxx$

 $$E = Exp - Bias$$

### Sepcial Values

Condition: 

$Exp = 1111..11$

#### Infinity

$Frac = 000..00$

#### Not-a-Number(NaN)

$Frac \neq 000..00$

### Decimal Rounding

* Toward Zero
* Round Down($-\infty$)
* Round Up($+\infty$) 
* Nearest Even (default by IEEE, **Statistically Wise**)

*E.g. 1.4 -> 1, 1.6 -> 2, 1.5 ->2(nearest even for 1.5 is 2), 2.5 -> 2*

### Binary Rounding

* "Even" whe last significant bit = 0
* "Half Way" when bits to right is 100..s

E.g. 10.00|101 -> 10.01 10.00|011 -> 10.00

### Mutiplication

* S:  s1 ^ s2
* M: M1 * M2
* E: E1 + E2

### Addition

Basic Idea: get binary points lined up

### Casting

C guarantees Two Levels

```````````c
double // double precision, 53 bits in frac
float  // single precision, 23 bits in frac
```````````

#### double/float -> int:

Truncates and rounding

#### int -> double

Exact conversion, since int has 32-bits <= 53 of double's precision bits

#### int -> float

**Will round!** 32 bits > 23 of float single precision



## Integer

### Bit Operation

When shifting an unsigned value, the `>>` operator in C is a logical shift. When shifting a signed value, the `>>` operator is an arithmetic shift
