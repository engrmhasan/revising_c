#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {

    printf("INT_MIN = %d\n", INT_MIN);
    printf("INT_MAX = %d\n", INT_MAX);

    printf("LONG_MIN = %ld\n", LONG_MIN);
    printf("LONG_MAX = %ld\n", LONG_MAX);

    printf("SHRT_MIN = %d\n", SHRT_MIN);
    printf("SHRT_MAX = %d\n", SHRT_MAX);

    printf("CHAR_MIN = %d\n", CHAR_MIN);
    printf("CHAR_MAX = %d\n", CHAR_MAX);

    printf("FLT_MIN = %e\n", FLT_MIN);
    printf("FLT_MAX = %e\n", FLT_MAX);

    printf("DBL_MIN = %e\n", DBL_MIN);
    printf("DBL_MAX = %e\n", DBL_MAX);

    return 0;
}


/*
Test output (example on a typical Windows MinGW-w64 environment):
INT_MIN = -2147483648
INT_MAX = 2147483647
LONG_MIN = -2147483648
LONG_MAX = 2147483647
SHRT_MIN = -32768
SHRT_MAX = 32767
CHAR_MIN = -128
CHAR_MAX = 127
FLT_MIN = 1.175494e-38
FLT_MAX = 3.402823e+38
DBL_MIN = 2.225074e-308
DBL_MAX = 1.797693e+308

*/
