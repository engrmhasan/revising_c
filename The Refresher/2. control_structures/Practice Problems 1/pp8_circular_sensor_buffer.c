/*

Circular Sensor Buffer with Rolling Average (Medium–Complex)

An embedded data logger maintains a **fixed-size circular buffer** of the last `8` temperature
readings (stored as `int32_t`) from a pipeline sensor. New readings overwrite the oldest slot.

**Your task:**

- Declare `int32_t buffer[8]` initialised to all zeros and a `size_t head = 0` index.
- Simulate **12 incoming readings** arriving one at a time:
  `{15, 18, 22, 19, 25, 30, 28, 24, 21, 17, 13, 20}`
- For each new reading, write it into `buffer[head % 8]` and advance `head`.
- After every new reading, compute and print the **rolling average** of all values currently
  in the buffer (for the first 7 readings, only the filled slots count; from reading 8 onward,
  all 8 slots are valid).
- At the end, print the final buffer contents in slot order (0–7) and the final rolling average.

*/


#include<inttypes.h>
#include<stdio.h>
#define BUFFER_SIZE 8
#define READINGS 12

int main(){

  int32_t buffer[BUFFER_SIZE] = {0};
  size_t head = 0;
  int32_t readings[READINGS] = {15, 18, 22, 19, 25, 30, 28, 24, 21, 17, 13, 20};
  float rolling_average = 0; 

  for(size_t i = 0; i < READINGS; i++){
      buffer[head % BUFFER_SIZE] = readings[i];
      head++;

      // compute sum from BUFFER CONTENTS only — not reading history
      size_t filled = (head < BUFFER_SIZE) ? head : BUFFER_SIZE;
      int32_t sum = 0;
      for(size_t j = 0; j < filled; j++){
          sum += buffer[j];
      }
      rolling_average = (float)sum / (float)filled;
      printf("Reading %2zu | filled=%zu | Rolling Avg: %.2f\n", i+1, filled, rolling_average);
  }
  printf("Before Replace: ");
  for(size_t i = 0; i < BUFFER_SIZE; i++){
    printf(" %" PRId32 "\t", readings[i]);
  }

  printf("\nAfter Replace:  ");
  for(size_t i = 0; i < BUFFER_SIZE; i++){
    printf(" %" PRId32 "\t", buffer[i]);
  }

  printf("\nRolling Average: %.2f \n", rolling_average);


}


/*

Test With:
   gcc -Wall -Wextra .\pp8_circular_sensor_buffer.c
   ./a

Test Output:
  Reading  1 | filled=1 | Rolling Avg: 15.00
  Reading  2 | filled=2 | Rolling Avg: 16.50
  Reading  3 | filled=3 | Rolling Avg: 18.33
  Reading  4 | filled=4 | Rolling Avg: 18.50
  Reading  5 | filled=5 | Rolling Avg: 19.80
  Reading  6 | filled=6 | Rolling Avg: 21.50
  Reading  7 | filled=7 | Rolling Avg: 22.43
  Reading  8 | filled=8 | Rolling Avg: 22.62
  Reading  9 | filled=8 | Rolling Avg: 23.38
  Reading 10 | filled=8 | Rolling Avg: 23.25
  Reading 11 | filled=8 | Rolling Avg: 22.12
  Reading 12 | filled=8 | Rolling Avg: 22.25
  Before Replace:  15        18      22      19      25      30      28      24
  After Replace:   21        17      13      20      25      30      28      24
  Rolling Average: 22.25

*/