/*
 *
 * We already explored: int, char, float, double and their sizes.
 * Now we continue with the next topics, step by step.
 *
 * Topics today:
 *   1. Signed vs Unsigned integers
 *   2. Floating point precision (why 0.1 + 0.2 is not exactly 0.3)
 *   3. size_t and fixed-width types from stdint.h
 *
 * Compile: gcc -o data_types_advanced data_types_advanced.c
 * Run:     ./data_types_advanced
 */

#include <stdio.h>
#include <stdint.h>   // gives us uint8_t, int32_t, uint64_t, etc.
#include <stddef.h>   // gives us size_t and ptrdiff_t

int main(void)
{
    /* 
       PART 1 — Signed vs Unsigned integers
       
       "Signed" means the number can be negative or positive.
       "Unsigned" means the number is always 0 or positive.

       For an 8-bit number:
         signed   range: -128  to  127
         unsigned range:    0  to  255

       Same number of bits — just interpreted differently.
     */

    printf("--- Part 1: Signed vs Unsigned ---\n\n");

    int           signed_num   = -5;   // can be negative
    unsigned int  unsigned_num =  5;   // always positive

    printf("signed int   = %d\n", signed_num);
    printf("unsigned int = %u\n\n", unsigned_num);  // use %u for unsigned

    // What happens when we go past the limit?
    // This is called "overflow" — the number wraps around.
    unsigned char u = 255;   // max value for unsigned 8-bit
    printf("unsigned char starts at: %u\n", u);
    u = u + 1;               // goes past max — wraps to 0
    printf("after +1 it becomes:     %u  (wrapped around!)\n\n", u);

    signed char s = 127;     // max value for signed 8-bit
    printf("signed char starts at: %d\n", s);
    s = s + 1;               // goes past max — wraps to -128
    printf("after +1 it becomes:   %d  (wrapped around!)\n\n", s);

    printf("Tip: avoid mixing signed and unsigned in comparisons.\n\n");


    /* --------------------------------------------------------
       PART 2 — Floating point precision
       --------------------------------------------------------
       float and double cannot store most decimal numbers exactly.
       They store the closest possible approximation.

       This is why 0.1 + 0.2 does not equal exactly 0.3.
    -------------------------------------------------------- */

    printf("--- Part 2: Floating Point Precision ---\n\n");

    float a      = 0.1;
    float b      = 0.2;
    float result = a + b;

    float huge_amount = result*100000000;


    // Print with many decimal places so we can see what is really stored
    printf("0.1 + 0.2 = %.20f\n", result);
    printf("0.3       = %.20f\n\n", 0.3f);
    printf("They look the same but are stored slightly differently.\n");
    printf("checking if huge amount 0.3*100000000 shows 30000000 or 30000001 using float\n");
    printf("Huge amount = %.0f\n", huge_amount);
    printf("This is normal. it is how floating point works.\n\n");

    // double has more precision than float (more decimal digits)
    float  f = 0.1f;
    double d = 0.1;
    printf("0.1 as float:  %.20f\n", f);
    printf("0.1 as double: %.20lf\n\n", d);
    printf("double is more precise, but still not perfectly exact.\n\n");

    printf("Tip: never check if two floats are exactly equal.\n");
    printf("     Instead, check if their difference is very small.\n\n");

    printf("checking if huge amount 0.3*100000000 shows 30000000 or 30000001 using double\n");
    printf("Huge amount = %.0lf\n\n", 0.3*100000000);


    /* --------------------------------------------------------
       PART 3 — size_t and fixed-width types from stdint.h
       --------------------------------------------------------
       So far we used int, float, etc.
       But sometimes we need more control over the exact size.

       stdint.h gives us types with guaranteed sizes:
         uint8_t  — exactly 8 bits,  unsigned (0 to 255)
         int8_t   — exactly 8 bits,  signed  (-128 to 127)
         uint16_t — exactly 16 bits, unsigned
         int32_t  — exactly 32 bits, signed
         uint64_t — exactly 64 bits, unsigned

       size_t is used for sizes and counts (like the result of sizeof).
       It is always the right size for the platform we are on.
    -------------------------------------------------------- */

    printf("--- Part 3: size_t and Fixed-Width Types ---\n\n");

    uint8_t  small_number = 200;
    int32_t  big_number   = -1000000;
    uint64_t huge_number  = 18000000000ULL;

    printf("uint8_t  small_number = %u\n",   small_number);
    printf("int32_t  big_number   = %d\n",   big_number);
    printf("uint64_t huge_number  = %lu\n\n", huge_number);

    // Their sizes on this machine
    printf("sizeof(uint8_t)  = %zu byte\n",  sizeof(uint8_t));
    printf("sizeof(int32_t)  = %zu bytes\n", sizeof(int32_t));
    printf("sizeof(uint64_t) = %zu bytes\n\n", sizeof(uint64_t));

    // size_t — used for measuring sizes
    // sizeof() always returns a size_t value
    char name[] = "hello"; //here we can see the use of array as well as string literal but don't worry about it for now, we will cover it in the next section
    size_t length = sizeof(name);   // includes the '\0' at the end
    printf("sizeof(\"hello\") = %zu bytes  (use %%zu to print size_t)\n\n", length);

    printf("Tip: use size_t when working with sizes and array lengths.\n");
    printf("     use int32_t or uint32_t when you need an exact bit size.\n\n");

    return 0;
}

/*
Test output (example on a typical Windows MinGW-w64 environment):

--- Part 1: Signed vs Unsigned ---

signed int   = -5
unsigned int = 5

unsigned char starts at: 255
after +1 it becomes:     0  (wrapped around!)

signed char starts at: 127
after +1 it becomes:   -128  (wrapped around!)

Tip: avoid mixing signed and unsigned in comparisons.

--- Part 2: Floating Point Precision ---

0.1 + 0.2 = 0.30000001192092895508
0.3       = 0.30000001192092895508

They look the same but are stored slightly differently.
checking if huge amount 0.3*100000000 shows 30000000 or 30000001 using float
Huge amount = 30000002
This is normal. it is how floating point works.

0.1 as float:  0.10000000149011611938
0.1 as double: 0.10000000000000000555

double is more precise, but still not perfectly exact.

Tip: never check if two floats are exactly equal.
     Instead, check if their difference is very small.

checking if huge amount 0.3*100000000 shows 30000000 or 30000001 using double
Huge amount = 30000000

--- Part 3: size_t and Fixed-Width Types ---

uint8_t  small_number = 200
int32_t  big_number   = -1000000
uint64_t huge_number  = 820130816

sizeof(uint8_t)  = 1 byte
sizeof(int32_t)  = 4 bytes
sizeof(uint64_t) = 8 bytes

sizeof("hello") = 6 bytes  (use %zu to print size_t)

Tip: use size_t when working with sizes and array lengths.
     use int32_t or uint32_t when you need an exact bit size.

*/

