/*
  Use-case: Reporting average floor temperature across a 3-floor building,
            4 sensors per floor.
 
  Topics:
    1. 2D array declaration and row-major memory layout
    2. Nested for loops, outer = row, inner = column
    3. Per-row aggregation
 
 */

#include <stdio.h>

#define FLOORS   3
#define SENSORS  4

int main(void)
{
    /* stored in row-major order: all of floor 0, then floor 1, then floor 2 */
    int grid[FLOORS][SENSORS] = {
        {21, 23, 20, 22}, //floor 0
        {30, 35, 33, 31}, //floor 1
        {18, 17, 19, 20}  //floor 2
    };

    size_t f, s;

    printf("           S0   S1   S2   S3   Avg\n");
    for (f = 0; f < FLOORS; f++) {
        int sum = 0;
        printf("Floor %zu: ", f);
        for (s = 0; s < SENSORS; s++) {
            printf("%4d ", grid[f][s]);
            sum += grid[f][s];
        }
        printf("  %d C\n", sum / (int)SENSORS);
    }

    return 0;
}

/*

Compile: gcc -o 2d_array_nested_loops 2d_array_nested_loops.c
Run:     ./2d_array_nested_loops


Test output:

           S0   S1   S2   S3   Avg
Floor 0:   21   23   20   22   21 C
Floor 1:   30   35   33   31   32 C
Floor 2:   18   17   19   20   18 C
*/