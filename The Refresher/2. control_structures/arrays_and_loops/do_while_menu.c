/*
  Use-case: Vending machine mode selection. Keep prompting until a valid
            operating mode is entered.
 
  Topics:
    1. do-while body runs at least once before the condition is checked
    2. When do-while fits over while (must act before we can test)
 
 */

#include <stdio.h>

int main(void)
{
    /* pre-stored responses: two invalid, then one valid */
    int responses[] = {0, 5, 2};
    int idx         = 0;
    int choice;

    printf("Modes: 1=Restock  2=Diagnostics  3=Power Off\n\n");

    /* body must run at least once. we need input before we can validate it */
    do {
        choice = responses[idx++]; // Iteration 1: choice = responses[0] = 0,  idx becomes 1
        if (choice < 1 || choice > 3)
            printf("Input %d: invalid.\n", choice);
        else
            printf("Input %d: accepted.\n", choice);
    } while (choice < 1 || choice > 3);

    printf("\nMode active: %s\n",
           choice == 1 ? "Restock" :
           choice == 2 ? "Diagnostics" : "Power Off");

    return 0;
}

/*
Compile: gcc -o do_while_menu do_while_menu.c
Run:     ./do_while_menu

Test output:

Modes: 1=Restock  2=Diagnostics  3=Power Off

Input 0: invalid.
Input 5: invalid.
Input 2: accepted.

Mode active: Diagnostics
*/
