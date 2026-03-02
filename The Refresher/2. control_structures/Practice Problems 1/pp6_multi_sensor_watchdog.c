/*
Multi-Sensor Watchdog Logger

A data-acquisition board polls **4 sensors** in sequence. Each sensor is represented as a
`uint8_t` value. A sensor signals, it is ready when its register reads `0xFF`. Each sensor
has an independent timeout of **8 poll cycles**.

**Your task:**

- Define a 2D `uint8_t` array `poll_data[4][10]` to simulate 4 sensors' register history
  (each row is one sensor's poll sequence). Fill some rows so that `0xFF` appears before
  cycle 8, and at least one row that never reaches `0xFF` within 8 cycles.
- Use an outer `for` loop to iterate over sensors and an inner `while` loop (with a
  `uint32_t timeout` counter) to poll each sensor's data.
- When a sensor becomes ready, log: `"Sensor X ready at poll Y"`.
- When a sensor times out, log: `"Sensor X TIMEOUT — marking as failed"` and increment a
  `uint8_t failed_count`.
- After all sensors, print the total number of failed sensors using the correct fixed-width
  format specifier.
*/

#include<stdint.h>
#include<inttypes.h>
#include<stdio.h>

#define READY_SIGNAL 0xFF
#define SENSORS 4
#define READINGS 10
#define TIMEOUT 8

int main(){


  uint8_t poll_data[SENSORS][READINGS] = {
        {0x10, 0x20, 0x30, 0xFF, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90}, //SENSOR 0
        {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x08, 0x09, 0x0A}, //SENSOR 1
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA}, //SENSOR 2
        {0x00, 0x00, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0xFF}  //SENSOR 3
    };
    uint8_t failed_count = 0;

    for(size_t i = 0; i < SENSORS; i++){
      uint32_t timeout_counter = 0;
      int ready_signal = 0;
      while(timeout_counter < TIMEOUT ){
        if(poll_data[i][timeout_counter] == READY_SIGNAL){
          printf("Sensor %zu ready at poll %" PRIu32 "\n", i, timeout_counter);
          ready_signal = 1;
          break;
        }
        timeout_counter++;
      }
      if(ready_signal == 0){
        printf("Sensor %zu TIMEOUT - marking as failed\n", i);
        failed_count++;
      }
    }
    printf("Total Number of failed sensor: %" PRIu8 "\n", failed_count);
  
}


/*

Test With:
  gcc -Wall -Wextra .\pp6_multi_sensor_watchdog.c -o .\pp6_multi_sensor_watchdog
  .\pp6_multi_sensor_watchdog

Test Output:
  Sensor 0 ready at poll 3
  Sensor 1 ready at poll 6
  Sensor 2 TIMEOUT - marking as failed
  Sensor 3 TIMEOUT - marking as failed
  Total Number of failed sensor: 2

*/


