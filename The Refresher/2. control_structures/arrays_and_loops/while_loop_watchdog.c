/*
  Use-case: Polling a sensor register until it signals ready,
            with a watchdog timeout to handle unresponsive hardware.
 
  Topics:
    1. while loop — iteration count unknown upfront
    2. Watchdog (timeout) pattern — mandatory in embedded code
 
 */

#include <stdio.h>
#include <stdint.h>

#define READY_SIGNAL  0xFF
#define MAX_TIMEOUT   10

int main(void) // void means the function takes no arguments and returns an int (0 by convention for success)
{
    /* Scenario 1: sensor becomes ready after 6 polls */
    uint8_t healthy[] = {0x00, 0x01, 0x00, 0x10, 0x01, 0x00, 0xFF};
    int idx = 0;

    uint8_t  data    = healthy[idx++];
    uint32_t timeout = MAX_TIMEOUT;

    printf("--- Scenario 1: healthy sensor ---\n");
    while (data != READY_SIGNAL && timeout > 0) {
        printf("  poll: 0x%02X  (not ready)\n", data);
        data = healthy[idx++];
        timeout--;
    }
    printf(timeout > 0 ? "  Ready: 0x%02X\n\n" : "  Timed out.\n\n", data); // ternary operator to print different messages based on whether we timed out or not. we will explore more of it later.

    /* Scenario 2: sensor never becomes ready — timeout fires */
    uint8_t dead[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    int dead_idx = 0;

    data    = dead[dead_idx++];
    timeout = 5;

    printf("--- Scenario 2: dead sensor ---\n");
    while (data != READY_SIGNAL && timeout > 0) {
        printf("  poll: 0x%02X  (not ready)\n", data);
        data = dead[dead_idx++];
        timeout--;
    }
    printf(timeout > 0 ? "  Ready: 0x%02X\n\n" : "  Timed out. Entering error state.\n\n", data);

    return 0;
}

/*

Compile: gcc -o while_loop_watchdog while_loop_watchdog.c
Run:     ./while_loop_watchdog

Test output:

--- Scenario 1: healthy sensor ---
  poll: 0x00  (not ready)
  poll: 0x01  (not ready)
  poll: 0x00  (not ready)
  poll: 0x10  (not ready)
  poll: 0x01  (not ready)
  poll: 0x00  (not ready)
  Ready: 0xFF

--- Scenario 2: dead sensor ---
  poll: 0x00  (not ready)
  poll: 0x00  (not ready)
  poll: 0x00  (not ready)
  poll: 0x00  (not ready)
  poll: 0x00  (not ready)
  Timed out. Entering error state.
*/
