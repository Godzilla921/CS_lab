/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
//bit-level
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~((~(x&(~y)))&(~((~x)&y)));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {  //从x中取出第n个字节
  return ((x&(0xFF<<(n<<3)))>>(n<<3))&0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {  
  // 若n为0 直接返回x 否则返回移动后的值
  int t=~1+1;  // -1
  int flag=!n+t;
  return (~flag&x)|(((x>>n)&((0x1<<(32+(~n+1)))+t))&flag);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int m1=0x11|(0x11<<8);
  int mask = m1|(m1<<16);  // mask=0x11111111
  int s=x&mask;            // 
  s+=x>>1&mask;
  s+=x>>2&mask;
  s+=x>>3&mask;            // 4位一组，每一个十六进制数记录了本组中出现的1的个数
  s=s+(s>>16);             // 对s进行一次合并
  mask=0xf|(0xf<<8);
  s=(s&mask)+((s>>4)&mask);
  return (s+(s>>8))&0x3f;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int t =!(x^0x0)+(~1)+1;  // x=0 时 t=0x0  x!=0时 t=~0x0;
  return (t&y)|((~t)&z);
}
//two's complement
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int move=32+(~n+1);  // 32-n
  return !(x^((x<<move)>>move)); 
}
/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) {
  int flag=((x>>31)&0x1)+(~1+1);  //判断是正数还是负数 x>=0 flag=0xffffffff,x<0 flag=0x00000000;
  return ((flag&x)|((~flag)&(x+(1<<n)+(~1+1))))>>n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
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
  int n = 0;
  int sign=x>>31; //判断x为正数还是负数 若为负数sign为0xffffffff 若为非负数sign为 0x0
  // 若x为负数，则对x取反，找到第一个1的位置
  x=(sign&(~x))|((~sign)&x);
  n += ((!!(x&((~0x0)<<(n+16)))) << 4);  //判断高16位是否有1 有的话n+16
  n += ((!!(x&((~0x0)<<(n+8)))) << 3);   //判断高八位是否有1 有的话n+8
  n += ((!!(x&((~0x0)<<(n+4)))) << 2);   //判断高4位是否有1  有的话n+4
  n += ((!!(x&((~0x0)<<(n+2)))) << 1);   //判断高2位是否有1  有的话n+2
  n += (!!(x&((~0x0)<<(n+1))));          //判断高1位是否有1  有的话n+1
  n += (!!(x&((~0x0)<<(n))));            //判断低1位是否为1  有的话n+1
  return n+1;                            //最后加上一位符号位
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // // y-x>0  注意例外 当y=0x7fffffff x=0x80000000时 ~x+1=0x80000000 y+(~x+1)<0 (y<x?)
  // return (!((y+(~x+1))>>31)&0x1)|((x>>31)&(!(y>>31)));  
  int k=y+(~x+1);     // 得到y-x
  int t=(k>>31)&1;    // 得到y-x 的符号
  int s1=(x>>31)&1;   // 记录x 的符号
  int s2=(y>>31)&1;   // 记录y 的符号            抛去去x为正数，y为负数的情况
  return (s1&(!s2))|((s1|(!s2))&(!t)); // x为负数,y为非负数，直接返回1； x为负数或y为非负数并且x<=y
}
/*
 * intLog2 - return floor(log base 2 of x), where x > 0
 *   Example: intLog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int intLog2(int x) {
  // x 一定为正数，需要找到首位1的下标（从右向左数）
  // 现在开始去寻找首位1
  int n = 0;
  n += ((!!(x&((~0x0)<<(n+16)))) << 4);  //判断高16位是否有1 有的话n+16
  n += ((!!(x&((~0x0)<<(n+8)))) << 3);   //判断高八位是否有1 有的话n+8
  n += ((!!(x&((~0x0)<<(n+4)))) << 2);   //判断高4位是否有1  有的话n+4
  n += ((!!(x&((~0x0)<<(n+2)))) << 1);   //判断高2位是否有1  有的话n+2
  n += (!!(x&((~0x0)<<(n+1))));          //判断高1位是否有1  有的话n+1
  n += (!!(x&((~0x0)<<(n))));            
  return n+(~1+1);                            //最后减去一位
}
//float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  if(!((uf&0x7f800000)^0x7f800000)&&(uf&0x007fffff)){ //NaN exp=256且frac!=0
    return uf;
  }
  return uf&0x7fffffff; //将最高位变为0即可
}
/* 
 * floatScale1d2 - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale1d2(unsigned uf) {
  unsigned sign=uf&0x80000000;     // 取出符号位
  unsigned exp=uf&0x7f800000;      // 取出阶码
  unsigned frac=uf&0x007fffff;     // 取出小数，不带1
  if(!(exp^0x7f800000)){ //NaN&无穷都返回自身
    return uf;
  }
  if(!exp){  // 等于0 或者无穷小时 直接将小数右移 再加上符号位即可
    // 还要考虑 溢出时的摄入问题
    if(!((frac&0x3)^0x3)){  // 若最低两位为11 需要进1(即向偶数摄入)
      frac=frac+1;
    }
    return sign|(frac>>1);
  }
  // 规格化  将阶码减一即可
  exp=((exp>>23)+(~1+1))<<23;
  if(!exp){ // 若阶码减一后0
    if(!((frac&0x3)^0x3)){  // 若最低两位为11 需要进1(即向偶数摄入)
        frac=frac+1;
      }
    frac=(frac|0x00800000)>>1; // 考虑移除后的舍人问题
  }
  return sign|exp|frac;
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
  unsigned sign=!!(uf&0x80000000)+(~1+1);   // 取出符号位 若为负数，sign位 0x0，若为正数 sign为0xffffffff
  unsigned exp=(uf&0x7f800000)>>23;         // 得到阶码
  unsigned frac=(uf&0x007fffff)|0x00800000; // 取出小数部分 并补上1
  // 注意 负数最可可以取到0x80000000
   // Nan infinite 或 左移溢出 即左移31位及以上 或为最小的负数0x80000000u
  if((!(exp^0xff))||(!((exp+(~158+1))>>31))){   // exp=255 或 exp>=157 
    return 0x80000000u;
  }
  if(!exp||((exp+(~127+1))>>31)){  // 阶码为0 或阶码小于127(exp-127<0) 直接返回0
    return 0;
  }
  exp+=~127+1;
  // 此时   0<=exp<=30 ,若exp <23 右移，exp>23 左移 exp=23不移动
  frac<<=7;// 先将frac左移7位
  frac>>=(30+(~exp+1)); // 再将frac右移30-exp位
  return (sign&frac)|((~sign)&(~frac+1));  // 若uf为负数，对其取反，正数保持不变
}
