
/*

A conveyor belt counts parts as they pass a sensor. The count is stored in an `unsigned int`
that starts at `0` and increments by `1` each cycle.

**Your task:**

- Use a `while` loop to simulate the belt running until the count reaches a batch limit of `500`.
- Every `100` parts, print a progress report: `"Batch progress: X / 500 parts"`.
- After the loop, print the final count and confirm the batch is complete.
- Add a guard: if the count is already at `UINT_MAX` before incrementing, print an overflow
  warning and `break` out of the loop instead of incrementing. Include `<limits.h>`.

*/

#include<stdio.h>
#include<limits.h>

#define BATCH_LIMIT 500

int main(){
    unsigned int count = 0;
    while(count <= BATCH_LIMIT){
        if (count == UINT_MAX){
            printf("WARNING: count overflows the maximum unsigned limit. Exiting loop.......\n");
            break;
        }
        if((count %100 == 0) && (count>0)) printf("Batch Progress: %u / 500 parts\n", count);

        count++;
    }
    if (count >= BATCH_LIMIT) printf("Batch Scanning is Complete\n");
}

/*

Run With:
    gcc -Wall -Wextra pp2_conveyor_belt_part_counter.c -o pp2_conveyor_belt_part_counter
    .\pp2_conveyor_belt_part_counter

Test Output:
    Batch Progress: 100 / 500 parts
    Batch Progress: 200 / 500 parts
    Batch Progress: 300 / 500 parts
    Batch Progress: 400 / 500 parts
    Batch Progress: 500 / 500 parts
    Batch Scanning is Complete

*/

