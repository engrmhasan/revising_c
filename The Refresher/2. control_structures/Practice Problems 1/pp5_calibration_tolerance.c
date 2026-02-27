/*
Sensor Calibration Tolerance Check
A calibration rig measures 8 sensors and stores readings as `float`. The nominal
target value is `5.00f` with an acceptable tolerance of `±0.05f`.

**Your task:**

- Store 8 readings in a `float` array (include some within tolerance and some outside):
  `{5.01f, 4.94f, 5.06f, 5.00f, 4.99f, 5.07f, 4.93f, 5.02f}`
- Define `TOLERANCE 0.05f` and `TARGET 5.00f` as macros.
- Iterate with a `for` loop. For each sensor, compute the deviation from `TARGET`.
- **Never use `==` to compare floats.** Instead, flag a sensor as out-of-tolerance
  when `deviation > TOLERANCE` (use the absolute value via a manual check: if negative, negate).
- Print a pass/fail report for each sensor and a final summary: how many passed, how many failed.

*/

#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
// #include<math.h> // for absolute value of difference

#define TARGET 5.00f
#define TOLERANCE 0.05f
#define TOTAL_READINGS 8

int main(){

    float readings[TOTAL_READINGS] = {5.01f, 4.94f, 5.06f, 5.00f, 4.99f, 5.07f, 4.93f, 5.02f};
    uint8_t passed = 0; // as passed/failed count is a single number we are assuming it can't go further than 8 bit size
    uint8_t failed = 0;

    for(size_t i = 0; i < TOTAL_READINGS; i++){
        float deviation = readings[i] - TARGET;
        if(deviation < 0) deviation = -deviation;

        // if(fabs((readings[i]) - TARGET)>TOLERANCE){ //could have used this if manual absolute checking was not a constraint given in the task
        if(deviation>TOLERANCE){
            printf("Sensor %zu with readings %.2f is failed\n", i, readings[i]);
            failed++;
        }
        else{
            printf("Sensor %zu with readings %.2f is passed\n", i, readings[i]);
            passed++;
        }
    }
    printf("Total Passed: %" PRIu8 "\nTotal Failed: %" PRIu8 "\n", passed, failed); // using PRIu8 so that it works on every machine.


}

/*

Test With
    gcc -Wall -Wextra .\pp5_calibration_tolerance.c -o .\pp5_calibration_tolerance
    .\pp5_calibration_tolerance

Test Output:
    Sensor 0 with readings 5.01 is passed
    Sensor 1 with readings 4.94 is failed
    Sensor 2 with readings 5.06 is failed
    Sensor 3 with readings 5.00 is passed
    Sensor 4 with readings 4.99 is passed
    Sensor 5 with readings 5.07 is failed
    Sensor 6 with readings 4.93 is failed
    Sensor 7 with readings 5.02 is passed
    Total Passed: 4
    Total Failed: 4

*/


