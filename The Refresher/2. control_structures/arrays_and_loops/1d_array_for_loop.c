/*
  Use-case: Finding the min, max, and average of 5 PCB temperature sensors.
 
  Topics:
    1. 1D array declaration and initialisation
    2. Carrying array size as a macro
    3. size_t as the correct loop index type
    4. Single-pass min / max / average
 
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define SENSOR_COUNT 5

int main(void)
{
    int readings[SENSOR_COUNT] = {23, 35, 41, 38, 19};

    /* print all readings */
    size_t i;
    for (i = 0; i < SENSOR_COUNT; i++) {
        printf("Sensor[%zu] = %d C\n", i, readings[i]);
    }

    /* single-pass min / max / sum */
    int min = readings[0];
    int max = readings[0];
    int sum = 0;

    for (i = 0; i < SENSOR_COUNT; i++) {
        if (readings[i] < min) min = readings[i];
        if (readings[i] > max) max = readings[i];
        sum += readings[i];
    }

    printf("\nMin: %d C\n",  min);
    printf("Max: %d C\n",  max);
    printf("Avg: %d C\n",  sum / (int)SENSOR_COUNT); //tye conversion to int is needed here because otherwise we will get a warning about implicit conversion from double to int, 
    return 0;
}

/*
 Compile: gcc -o 1d_array_for_loop 1d_array_for_loop.c
 Run:     ./1d_array_for_loop

Test output:

Sensor[0] = 23 C
Sensor[1] = 35 C
Sensor[2] = 41 C
Sensor[3] = 38 C
Sensor[4] = 19 C

Min: 19 C
Max: 41 C
Avg: 23 C
*/