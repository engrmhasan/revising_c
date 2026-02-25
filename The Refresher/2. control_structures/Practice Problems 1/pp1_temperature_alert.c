/*
A factory floor has **6 temperature sensors** spread across a production line.
Each reading is stored in a 1D array of `int`.

**Your task:**

- Define a macro `SENSOR_COUNT` for the number of sensors and `ALARM_TEMP` for the threshold (set it to `40`).
- Iterate over the array with a `for` loop using `size_t` as the index type.
- Print each sensor index and its reading.
- After the loop, print a warning line for every sensor that **equals or exceeds** `ALARM_TEMP`.
- If no sensor breached the threshold, print `"All sensors nominal."`.

**Sample readings:** `{28, 35, 41, 39, 40, 22}`
*/


#include <stdio.h>
#define SENSOR_COUNT 6
#define ALARM_TEMP 40

int main(){
    int temperatures[SENSOR_COUNT] = {28, 35, 41, 39, 40, 22};
    size_t equal_or_exceed_count = 0; //using size_t here because we need to loop to the last index of the array. array size matters here.
    
    // problem says double pass: first print readings then on another pass warnings otherwise we just could do the single pass in the second for loop.

    for(size_t i = 0; i < SENSOR_COUNT; i++){
        printf("Sensor %zu reading is %i\n", i, temperatures[i]);
    }
    printf("\n\n");

    for (size_t i=0; i < SENSOR_COUNT; i++){ /*We use size_t for best practice because it automatically matches the computer's architecture (32-bit or 64-bit), ensuring our loop can safely index the largest possible array the system can hold.It prevents "overflow" bugs and compiler warnings that occur when we try to fit a potentially massive memory address into a fixed 32-bit uint32_t box.*/
        // printf("Hello\t");
        if (temperatures[i] >= ALARM_TEMP){
            equal_or_exceed_count++;
            printf("Warning: Sensor %zu reading is %i which exceeds the maximum temperature\n", i, temperatures[i]); // %zu is the size_t format specifier
        } 
        // else{
        //     printf("Sensor %zu reading is %i\n",i,temperatures[i]);
        // }
    }
    if(equal_or_exceed_count == 0) printf("All sensors nominal.\n");

}

/*
Run with
    gcc -Wall -Wextra pp1_temperature_alert.c -o pp1_temperature_alert
    .\pp1_temperature_alert

Test Output:
    Sensor 0 reading is 28
    Sensor 1 reading is 35
    Sensor 2 reading is 41
    Sensor 3 reading is 39
    Sensor 4 reading is 40
    Sensor 5 reading is 22


    Warning: Sensor 2 reading is 41 which exceeds the maximum temperature
    Warning: Sensor 4 reading is 40 which exceeds the maximum temperature
*/

