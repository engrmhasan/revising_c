/*

Production Grid: Column-Wise Defect Analysis (Medium–Complex)

A factory inspection system monitors a **4-row × 6-column** grid of assembly stations.
Each cell holds an `int` representing the number of defects detected in the last shift.

**Your task:**

- Declare `int grid[4][6]` and populate it with realistic values (mix of zeros and small
  positive integers, e.g., some zeros and values up to `12`).
- Define `ROWS 4` and `COLS 6` as macros.
- Use nested `for` loops to:
  1. Print the full grid as a formatted table.
  2. Compute the **total defects per row** (print alongside each row).
  3. Compute the **maximum defect count per column** across all rows (requires a separate
     pass: iterate columns in the outer loop, rows in the inner loop — note the contrast
     with row-major traversal performance).
- Print a column summary line: `"Col X max defects: N"`.
- Identify and print which column has the **overall highest maximum**.

*/

#include <stdio.h>

#define ROWS 4
#define COLS 6

int main() {

    int grid[ROWS][COLS] = {
        {0, 3, 5, 0, 7, 2},
        {4, 0, 1, 6, 0, 8},
        {2, 9, 0, 3, 5, 0},
        {7, 1, 4, 0, 6, 10}
    };

    printf("| %-10s |", "ROW");

    for(size_t i = 0; i < COLS; i++){
        printf(" COL-%zu |", i);
    }

    printf(" TOTAL |\n");

    for(size_t i = 0; i < ROWS; i++){
        int dfcts_per_row = 0;

        printf("| %-10zu |", i);

        for(size_t j = 0; j < COLS; j++){
            printf(" %5d |", grid[i][j]);
            dfcts_per_row += grid[i][j];
        }

        printf(" %5d |\n", dfcts_per_row);
    }




    return 0;
}




/*
Test With:

    gcc -Wall -Wextra pp7_grid_defect_analysis.c -o .\pp7_grid_defect_analysis
    .\pp7_grid_defect_analysis


Test Output:

    | ROW        | COL-0 | COL-1 | COL-2 | COL-3 | COL-4 | COL-5 | TOTAL |
    | 0          |     0 |     3 |     5 |     0 |     7 |     2 |    17 |
    | 1          |     4 |     0 |     1 |     6 |     0 |     8 |    19 |
    | 2          |     2 |     9 |     0 |     3 |     5 |     0 |    19 |
    | 3          |     7 |     1 |     4 |     0 |     6 |    10 |    28 |

*/
