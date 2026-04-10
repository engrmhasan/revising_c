/*

Multi-Zone Alarm Escalation State Machine (Complex)

A plant safety system monitors **3 zones**, each with **3 sensors** (`int grid[3][3]`).
The system defines three alarm levels:

| Level    | Condition                                      |
|----------|------------------------------------------------|
| NORMAL   | All sensors in zone below `35`                 |
| WARNING  | One or more sensors in zone between `35–49`    |
| CRITICAL | One or more sensors in zone at `50` or above   |

**Your task:**

- Define the thresholds as macros: `WARN_THRESH 35`, `CRIT_THRESH 50`.
- Provide **two different sensor snapshots** (two separate 2D array initialisations):
  one where some zones are in WARNING, and one where at least one zone is CRITICAL.
- Write a function-like block (or simply inline logic) using nested `for` loops and
  `if`/`else if`/`else` to determine each zone's alarm level from the highest reading in that zone.
- Use a `do-while` loop to cycle through both snapshots, printing a full zone status report
  per snapshot, until all snapshots have been processed.
- Track how many zones are CRITICAL across both snapshots and print that count at the end.

*/


#include<stdio.h>
#define SNAPSHOTS 2
#define ZONES 3
#define SENSORS 3
#define WARN_THRESH 35
#define CRIT_THRESH 50
#define MIN_LEVEL 1
#define MAX_LEVEL 3

void read_status(int arr[][SENSORS], size_t zone_reports[]){  
  for(int i=0; i<ZONES; i++){
    
    zone_reports[i] = 1;

    for(int j=0; j<SENSORS; j++){
      size_t level = MIN_LEVEL;
      if (arr[i][j] >= CRIT_THRESH) level = MAX_LEVEL;
      else if(arr[i][j] >= WARN_THRESH) level = 2;

      if(level>zone_reports[i]) zone_reports[i] = level;
      if(level == MAX_LEVEL) break;
    }
  }
}


int main(){

    int grid0[ZONES][SENSORS] = {
        {52, 20, 38},
        {40, 10, 11},
        {10, 20, 30}
    };

    int grid1[ZONES][SENSORS] = {
        {30, 38, 35},
        {49, 39, 48},
        {50, 52, 55}
    };
    
    int (*grids[])[SENSORS] = {grid0, grid1};
    int count_critical = 0;
    int read_snapshots = 0;
    do{
      size_t reports[ZONES];
      
      // read_status(read_snapshots == 0 ? grid0 : grid1, reports);
      read_status(grids[read_snapshots], reports);
      for(int i=0; i<20; i++) printf("*");
      printf(" Snapshot %d reading ", read_snapshots);
      for(int i=0; i<20; i++) printf("*");
      printf("\n");
      
      for(size_t i =0; i<ZONES; i++ ){
        if(reports[i] == 1){
          printf("Zone %zu condition is NORMAL\n",i);
        }
        else if(reports[i] == 2){
          printf("Zone %zu condition is WARNING\n",i);
        }
        else{
          printf("Zone %zu condition is CRITICAL\n",i);
          count_critical++;
        }
      }

      read_snapshots++;
    }while(read_snapshots < SNAPSHOTS);

    printf("\nThere are %d zones that are critical in across snapshot. Immediate action must be taken now.\n", count_critical);
    
}



/*
Test With :  gcc -Wall -Wextra .\pp9_zone_alarm_escalation.c -o .\pp9_zone_alarm_escalation
             .\pp9_zone_alarm_escalation

Output: 
******************** Snapshot 0 reading ********************
Zone 0 condition is CRITICAL
Zone 1 condition is WARNING
Zone 2 condition is NORMAL
******************** Snapshot 1 reading ********************
Zone 0 condition is WARNING
Zone 1 condition is WARNING
Zone 2 condition is CRITICAL

There are 2 zones that are critical in across snapshot. Immediate action must be taken now.

*/