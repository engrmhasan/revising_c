/*
primitive_types.c

Purpose:
- Demonstrate primitive C types (int, long, short, float, double, char).
- Print each variable's value and the result of sizeof(...) so we can see
    how many bytes each type occupies on the current platform.

Running process (example):
- Compile: `gcc primitive_types.c -o primitive_types.exe`
- Run: `./primitive_types.exe`

What we test and why:
- We assign example values to variables and print both the value and
    `sizeof(variable)` so the program documents its runtime behaviour.

*/


#include <stdio.h>
#include <stdint.h>

int main(void) {
        /* Integer types */
        int a = 10;
        long b = 100000L;
        short c = 5;

        /* Floating-point types */
        float d = 3.14f;
        double e = 3.141592653589793;

        /* Character type */
        char f = 'A';

        /* Print values and sizes */
        printf("int a = %d; size = %zu bytes\n", a, sizeof(a));
        printf("long b = %ld; size = %zu bytes\n", b, sizeof(b));
        printf("short c = %d; size = %zu bytes\n", c, sizeof(c));
        printf("float d = %f; size = %zu bytes\n", d, sizeof(d));
        printf("double e = %f; size = %zu bytes\n", e, sizeof(e));
        printf("char f = %c; size = %zu bytes\n", f, sizeof(f));

        /* Also print sizes for the types themselves */
        printf("\nType sizes (using types):\n");
        printf("sizeof(int) = %zu\n", sizeof(int));
        printf("sizeof(long) = %zu\n", sizeof(long));
        printf("sizeof(short) = %zu\n", sizeof(short));
        printf("sizeof(float) = %zu\n", sizeof(float));
        printf("sizeof(double) = %zu\n", sizeof(double));
        printf("sizeof(char) = %zu\n", sizeof(char));

        return 0;
}

/*
Test output (example on a typical Windows MinGW-w64 environment):
    int a = 10; size = 4 bytes
    long b = 100000; size = 4 bytes
    short c = 5; size = 2 bytes
    float d = 3.140000; size = 4 bytes
    double e = 3.141593; size = 8 bytes
    char f = A; size = 1 byte

`%zu` is a **format specifier** used in `printf`. It tells `printf` how to format the value being printed. Specifically:
* `%z` tells `printf` the value is of type `size_t` (the type returned by `sizeof`).
* `u` means the value should be printed as an **unsigned decimal number**.
* `sizeof(a)` returns a `size_t`, not an `int`.
* So `%zu` correctly prints the number of bytes `sizeof(a)` gives.
* Without `%zu`, the output could be wrong or unsafe on some systems.

Lessons learned:
- `sizeof` reports sizes that depend on the platform and ABI. For example,
    Windows (LLP64) typically has `long` = 4 bytes even on 64-bit, while
    many Unix-like systems (LP64) have `long` = 8 bytes on 64-bit.
- Use fixed-width integer types (`int32_t`, `int64_t`) from `stdint.h` when
    an exact size is required.
- Always `#include <stdio.h>` when using `printf`.
*/
