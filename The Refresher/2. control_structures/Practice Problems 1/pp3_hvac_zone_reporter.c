/*

A building has **3 zones**, each monitored by **4 sensors**. Readings are stored in a
`int grid[3][4]` (2D array, row = zone, column = sensor).

**Your task:**

- Populate the array with these readings:
  - Zone 0: `{20, 22, 21, 23}`
  - Zone 1: `{31, 29, 33, 30}`
  - Zone 2: `{18, 17, 19, 16}`
- Use nested `for` loops to print a formatted table showing all readings and the
  integer average temperature per zone.
- After the table, identify and print which zone has the **highest average**.
- Define macros `ZONES` and `SENSORS_PER_ZONE`.

*/

#include<stdio.h>

#define ZONES 3
#define SENSORS_PER_ZONE 4

int main(){
    int grid[ZONES][SENSORS_PER_ZONE] = {
        {20, 22, 21, 23},
        {31, 29, 33, 30},
        {18, 17, 19, 16}
    };
    int total_temp;
    int max_avg = -999;
    int avg_reading; // no need to initialize, because whatever data this variable holds will automatically updated with the calculation.
    size_t max_avg_zone; // it has to be size_t, because we are initializing loops with size_t variable.
    //So storing size_t value to a variable should also be size_t

    printf("\t");
    for(size_t s=1; s <= SENSORS_PER_ZONE; s++){
        printf("SENSOR %zu\t", s);
    }
    printf("AVERAGE READING\n");

    for(size_t i = 0; i < ZONES; i++){
        printf("Zone %zu: ",i);
        total_temp = 0;

        for(size_t j = 0; j < SENSORS_PER_ZONE; j++){
            total_temp = total_temp + grid[i][j];
            printf("   %d\t\t", grid[i][j]);
        }

        avg_reading = total_temp/SENSORS_PER_ZONE; //update avg_reading variable only,
        //so each time the loop runs a new variable of the same name will not be declared.
        printf("\t%d\n", avg_reading);

        if(avg_reading > max_avg){
            max_avg = avg_reading;
            max_avg_zone = i;
        }
    }

    printf("\nMaximum Average is %d at ZONE %zu\n", max_avg, max_avg_zone);

}


/*

Test With:

    gcc -Wall -Wextra pp3_hvac_zone_reporter.c -o pp3_hvac_zone_reporter
    .\pp3_hvac_zone_reporter

Test Output:

        SENSOR 1        SENSOR 2        SENSOR 3        SENSOR 4        AVERAGE READING
Zone 0:    20              22              21              23                   21
Zone 1:    31              29              33              30                   30
Zone 2:    18              17              19              16                   17

Maximum Average is 30 at ZONE 1

*/