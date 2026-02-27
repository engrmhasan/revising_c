/*
A vending machine operator must select a maintenance mode before servicing the unit.
Valid modes are:

| Input | Mode         |
|-------|--------------|
| 1     | Restock      |
| 2     | Diagnostics  |
| 3     | Deep Clean   |
| 4     | Power Off    |

**Your task:**

- Use a `do-while` loop to keep prompting for a mode until a valid one is entered.
- Simulate inputs from a pre-filled `int responses[]` array (include at least two invalid
  values before a valid one, e.g., `{0, 7, 3}`).
- For each invalid input print `"Invalid mode: X. Enter 1-4."`.
- Once a valid mode is accepted, print the active mode name using a **chain of ternary operators**.
*/
#include<stdio.h>
#include <stdbool.h>

int main(){
    int responses[] = {0, 8, 9 ,2, 7, 6, 7, 1, 5, 6, 3, 8, 5, 6, 4};
    size_t idx = 0;
    int mode;
    bool flag = true;
    // printf("Size of Responses array %zu\n\n", sizeof(responses)/4); // each value is of 4 bytes

    do{
        mode = responses[idx++];

        if (idx >= sizeof(responses) / sizeof(responses[0])){ // need this watchdog to exit loop if there are no valid input found to prevent infinite loop
            printf("All Values of the responses has been checked. No valid mode found. Exiting loop...");
            flag = false;
            break;
        }

        if(mode < 1 || mode > 4) printf("Input %d: Invalid mode\n", mode);
        else printf("Input %d: Valid Mode\n", mode);

    }while(mode < 1 || mode > 4);

    if(flag == true) printf("Mode activated: %s\n", mode == 1 ? "Restock" : // if there are no valid inputs then show only all inavlid mode. because No active mode is found
         mode == 2 ? "Diagnostics" : mode == 3 ? "Deep Clean" : "Power Off" );
}


/*

Test With
    gcc -Wall -Wextra .\pp4_vending_machine_mode.c -o pp4_vending_machine_mode
    .\pp4_vending_machine_mode

Test Output:
    Size of Responses array 15

    Input 0: Invalid mode
    Input 8: Invalid mode
    Input 9: Invalid mode
    Input 2: Valid Mode
    Mode activated: Diagnostics
*/


