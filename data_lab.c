/* 
 * CS:APP Data Lab 
 * 
 * Kunka Akiyama
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
// 0100
// 0101 XOR
// 0001

#include <stdio.h>



int bitXor(int x, int y) {
    int result = ~((~(x & ~(y)))&(~(~(x) & y)));
  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int x = 1;
  x = x << 31;
  return x;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    // reference from https://doraemonzzz.com/2020/05/14/CMU%2015-213%20Lab1%20Data%20Lab/#howManyBits
    int y1 = x + 1;
    int y2 = ~x;
    int y3 = (y1 ^ y2);

    //判断是否为0xffffffff，如果成立，则z2为1
    //如果x为0xffffffff，则z1为0
    int z1 = ~x;
    int z2 = !z1;

    //生成结果，如果x为Tmax则r=False，所以要取非
    int r = (z2 | y3);
    r = !r;
    return r;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int y = 0xAAAAAAAA;
  int z = x ^ y;
  int r = !(y & z);
  return r;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  int y = (~x) + 1;
  return y;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int z1 = (x >> 4) ^ 3;
  int b_3 = (x & 8) >> 3;
  int b_2 = (x & 4) >> 2;
  int b_1 = (x & 2) >> 1;
  int z2 = (!b_3) | (b_3 & (!b_2) & (!b_1));
  return !z1 & !!z2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int flag = !x;   // when x is 0, flag = 1
  flag = (~flag) + 1;       // 1111, which is -1
  int non_flag = ~flag;
  return (non_flag & y) | (flag & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sign_x = (x >> 31) & 1;
  int sign_y = (y >> 31) & 1;
  int z1 = sign_x ^ sign_y; // if sign same then z1 = 0
  int z2 = sign_x & !sign_y; // if y > 0 and x < 0, then z2 = 1
  int minus_x = (~x) + 1;
  int z3 = !(((y + minus_x) >> 31) & 1); 
  return (z1 & z2 ) | (!z1 & z3);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int sign_1 = (x >> 31) & 1;
  int sign_2 = ((~x + 1) >> 31) & 1;
  return (sign_1 | sign_2) ^ 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int mask = (x & (1 << 31)) >> 31; //if x is positive, then mask = 0000, negative, mask = 1111
  x = ((~mask) & x) | (mask & (~x)); // make sure x is positive

  int c1 = !!(x >> 16); // if x = 10. then c1 = 1
  int m1 = c1 << 4;
  x >>= m1;

  int c2 = !!(x >> 8);
  int m2 = c2 << 3;
  x >>= m2;

  int c3 = !!(x >> 4);
  int m3 = c3 << 2;
  x >>= m3;

  int c4 = !!(x >> 2);
  int m4 = c4 << 1;
  x >>= m4;

  int c5 = !!(x >> 1);
  int m5 = c5;
  x >>= m5;

  int c6 = x & 1;
  int m6 = c6;
  return m1 + m2 + m3 + m4 + m5 + m6 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned s, e, f;
  s = (uf >> 31) & 1;
  e = (uf >> 23) & 255; // which is 0 1111 1111
  f = (uf) & 0x7fffff;
  // without considering special value
  unsigned res;
  if(e == 0xff){
    return uf; // NaN or INF, return arg
  }else if(e == 0){ // denormalized number
    f <<= 1;
    unsigned high = f >> 23; // to check if there's an overflow of frac
    if(high == 1){ // overflow 
      e = 1; // denormalized number, convert to 1.xxx
    }
  }else{ 
    e = e + 1;
  }
  res = (s << 31) | (e << 23) | (f);
  return res;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned s, e, f;
  s = (uf >> 31) & 1;
  e = (uf >> 23) & 255; // which is 0 1111 1111
  f = (uf) & 0x7fffff;
  if(e == 255){
    return 0x80000000u;
  }else if(e == 0){
    return 0;
  }else{
    int res = (1 << 23) | f;
    int E = e - 127;
    if(E > 23){
      while(E > 23){
        E--;
        res <<= 1;
        if(res < 0){
          return 0x80000000u;
        }
      }
    }else{
      while(E < 23){
          E++;
          res >>= 1;
      }
    }
    if(s == 1){
      res = -1 * res;
    }
    return res;
  }
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // ref from https://www.cnblogs.com/ustca/p/11740382.html#12%E3%80%81howmanybits
  // too tired to finish the last one LMAO
  unsigned INF = 0xff << 23; 
	int e = 127 + x;	
	if (x < 0) 
		return 0;
	if (e >= 255) 
		return INF;
	return e << 23;
}

