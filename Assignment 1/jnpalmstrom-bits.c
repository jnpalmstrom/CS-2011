/* 
 * CS:APP Data Lab 
 * 
 * Name: Jack Palmstrom
 * WPI Username: jnpalmstrom
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */


/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {

       /*
	* Initialize a mask with all odd bits turned on
	* Initialize a 16 bit word with all odd bits turned on
	* Return a 32 bit word with all odd bits turned on
	*/

       int mask = 0xAA;                    
       int word = (mask | mask << 8);
       return (word | (word << 16));       
}


/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {

  /*
   * Checks if x is equal to zero
   * To return 1, x must not cause an overflow
   * when x is added to itsef
   */

  return !((x + x) | !x);  
}
 


/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

  /*
   * Bitwise XOR is the bit invert of bitwise AND and bitwise NOR
   * Combines definition of bitwise XOR with De Morgan's Law
   *
   */
  
  return ((~(x & y) & (~(~x & ~y)))); 
}


/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {

    /* 
     * if x != 0, subtract 1 from 0xffffffff
     * if x = 0, subtract 1 from 1 => 0x00000000
     *
     */

    
  int cond = (~(!!x) + 1);

    /* 
     * if x != 0, mask out z
     * if x = 0, mask out y
     *
     */

  
  return (cond & y) | (~cond & z); 
}


/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {

    /* 
     * 
     *
     *
     */
  
  int m = x;
  int m1 = (m | m >> 1);
  int m2 = (m1 | m1 >> 2);
  int m4 = (m2 | m2 >> 4);
  int m8 = (m4 | m4 >> 8);
  int m16 = (m8 | m8 >> 16);

  return (m16 & ((~m16 >> 1) ^ (0x80 << 24)));  
}


/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

    /* 
     * The condition is x >= 0
     * if the condition fails. We add a bias of 2^n - 1 
     * to the number to round toward zero.
     */  
  
  int y =((x >> 31) & 1); // 
  int z = y << n;
  
  z = z + ((y << 31) >> 31); 
  return ((x + z) >> n);
}


/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {

    /* 
     * Move the most significant bit to the least signficant bit
     * and see if its zero or one
     *
     */

  return !(x >> 31); 
}


/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {

    /* 
     *
     *
     *
     */

  
  int min = 0x1 << 31;
  int sign = x >> 31;
  int doub = x + x;
  int over = (x ^ doub) >> 31;
  int sat2 = over & (sign ^ ~min);

  return (sat2) | (~over & doub);
}

/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {

  /* 
   * there are 2 conditions where x < y
   * condition 1: x is less than zero and y is greator or equal to zero 
   * condition 2: x and y are the same sign, but x minus y yields a negative value
   */
  
  int z = x + (~y + 1);             
  int cond1 = x & (~y);
  int cond2 = (~(x ^ y)) & z;

  return (cond1 | cond2) >> 31 & 1;
}

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

    /* 
     *
     *
     *
     */

  int i = x + (~0x2F);
  int j = 58 + ~x;

  return !((i | j) >> 31);
 
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x) {

    /* 
     *
     *
     *
     */
  
  int z = x & 0x3;
  x = x >> 2;

  return (x << 1) + x + ((z + z + z + ((x >> 0x1F) & 0x3)) >> 2); 
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {

    /* 
     *
     *
     *
     */
  
  int output = 0;

  int z = (!!(x >> 16)) << 31 >> 31;
  output += z & 16;
  x = x >> (z & 16);

  z = (!!(x >> 8)) << 31 >> 31;
  output += z & 8;
  x = x >> (z & 8);

  z = (!!(x >> 4)) << 31 >> 31;
  output += z & 4;
  x = x >> (z & 4);

  z = (!!(x >> 2)) << 31 >> 31;
  output += z & 2;
  x = x >> (z & 2);

  z = (!!(x >> 1)) << 31 >> 31;
  output += z & 1;
 
  return output;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {

    /* 
     *
     *
     *
     */
  
  int z = 0x000000FF << 23;
  int fraction = 0x7FFFFF & uf;

  if ((z & uf) == z && fraction)
    return uf;

  return uf ^ (1 << 31);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {

    /* 
     * Squish x into 23 bits, rounding following the rounding rules
     *
     *
     */
  
    unsigned sign,
             fraction,
             exp = 150,
             tempX,
             y = 2,
             top,
             bottom;
    
    if (x == 0) {
      return 0;
    }
    if (x == 0x80000000) {
      return 3472883712u;
    }
    
    sign = (x & 0x80000000);
    fraction = (sign) ? (-x) : (x);
    tempX = fraction;
    
    while (tempX & 0xFF000000) {
        
        tempX = (fraction + (y / 2)) / (y);
        y <<= 1;
        exp++;
    }
    
    while (tempX <= 0x007FFFFF) {
        tempX <<= 1;
        exp--;
    }
    
    if (fraction & 0xFF000000) {

        y = 1 << (exp - 150);
        tempX = fraction / y;
        bottom = fraction % y;
        top = y - bottom;

        if ((top < bottom) || ((top == bottom) & tempX))
            ++tempX;

        fraction = tempX;
	
    }
    else {
        while (fraction <= 0x007FFFFF)
            fraction <<= 1;
    }

    return (sign) | (exp << 23) | (fraction & 0x007FFFFF);
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {

  unsigned sign = uf >> 31 << 31;
  unsigned fraction = (uf << 9) >> 9;
  unsigned exponent = (((uf << 1) >> 24) << 23);


  if (exponent == 0x7F800000) {

    return uf;
  }
  else if (exponent == 0) {

    return ((uf << 1) | sign);
  }
  else {

    exponent = (exponent + (1 << 23));
  }

  return (sign | exponent | fraction);
}

