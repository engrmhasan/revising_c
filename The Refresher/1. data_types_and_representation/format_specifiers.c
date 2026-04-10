#include <stdio.h>
#include <stdint.h>   // For uint32_t, uint64_t
#include <inttypes.h> // For PRIu32, PRIu64

int main() {
    uint32_t small_val = 150;
    uint64_t large_val = 9000000000ULL; // Very large number

    // Standard way (Can be risky on different systems)
    printf("Standard small_val: %u\n", small_val);
    printf("Standard large_val: %lu\n\n", large_val);


    // Professional way (Guaranteed to work on any system)
    // The macro "PRIu32" literally turns into "u" or "lu" behind the scenes
    printf("Professional 32-bit: %" PRIu32 "\n", small_val);
    printf("Professional 64-bit: %" PRIu64 "\n", large_val);

    return 0;
}

/*
 Compile: gcc format_specifiers.c -o format_specifiers
 Run:     ./format_specifiers

Test output:
Standard small_val: 150
Standard large_val: 410065408

Professional 32-bit: 150
Professional 64-bit: 9000000000
*/

/*
The syntax %" PRIu32 " looks broken. Actually here is what is happening:

The compiler sees "Professional: %".

It looks up PRIu32 and sees it is defined as the letter "u".

The compiler sees the final "\n".

It stitches them all together into one string: "Professional: %u\n".

This prevents us from having to remember if a uint32_t is an unsigned int or an unsigned long on a specific chip.
The macro does the "remembering" for us.
*/
