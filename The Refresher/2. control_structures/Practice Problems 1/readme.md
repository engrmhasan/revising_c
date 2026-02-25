# Practice Problems 1 — Control Structures & Arrays

These problems are designed to test the skills built across the topics covered so far:
primitive data types, signed/unsigned integers, floating-point precision, fixed-width types
(`stdint.h`), type limits (`limits.h`), 1D arrays, 2D arrays, `for` loops, `while` loops,
`do-while` loops, watchdog/timeout patterns, macros, `size_t`, and the ternary operator.

Problems are ordered from straightforward industrial logic to complex embedded-system scenarios.

---

## Problem 1 — Temperature Threshold Alert (Simple)

A factory floor has **6 temperature sensors** spread across a production line.
Each reading is stored in a 1D array of `int`.

**Your task:**

- Define a macro `SENSOR_COUNT` for the number of sensors and `ALARM_TEMP` for the threshold (set it to `40`).
- Iterate over the array with a `for` loop using `size_t` as the index type.
- Print each sensor index and its reading.
- After the loop, print a warning line for every sensor that **equals or exceeds** `ALARM_TEMP`.
- If no sensor breached the threshold, print `"All sensors nominal."`.

**Sample readings:** `{28, 35, 41, 39, 40, 22}`

**Expected skills tested:** 1D array, `for` loop, `size_t`, macros, `if`/`else`, comparison operators.

---

## Problem 2 — Conveyor Belt Part Counter (Simple)

A conveyor belt counts parts as they pass a sensor. The count is stored in an `unsigned int`
that starts at `0` and increments by `1` each cycle.

**Your task:**

- Use a `while` loop to simulate the belt running until the count reaches a batch limit of `500`.
- Every `100` parts, print a progress report: `"Batch progress: X / 500 parts"`.
- After the loop, print the final count and confirm the batch is complete.
- Add a guard: if the count is already at `UINT_MAX` before incrementing, print an overflow
  warning and `break` out of the loop instead of incrementing. Include `<limits.h>`.

**Expected skills tested:** `while` loop, `unsigned int`, overflow awareness, `UINT_MAX`, modulo operator, `break`.

---

## Problem 3 — HVAC Multi-Zone Average Reporter (Simple–Medium)

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

**Expected skills tested:** 2D array, nested `for` loops, row-major layout, per-row aggregation, macros.

---

## Problem 4 — Vending Machine Mode Selector (Simple–Medium)

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

**Expected skills tested:** `do-while`, input validation, ternary operator, array-driven simulation.

---

## Problem 5 — Sensor Calibration Tolerance Check (Medium)

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

**Expected skills tested:** `float` array, epsilon/tolerance comparison, floating-point precision
awareness, `for` loop, `size_t`, macros.

---

## Problem 6 — Multi-Sensor Watchdog Logger (Medium)

A data-acquisition board polls **4 sensors** in sequence. Each sensor is represented as a
`uint8_t` value. A sensor signals it is ready when its register reads `0xFF`. Each sensor
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

**Expected skills tested:** `uint8_t`, `uint32_t`, fixed-width types, watchdog timeout pattern,
nested loop structures (`for` + `while`), `size_t`.

---

## Problem 7 — Production Grid: Column-Wise Defect Analysis (Medium–Complex)

A factory inspection system monitors a **4-row × 6-column** grid of assembly stations.
Each cell holds an `int` representing the number of defects detected in the last shift.

**Your task:**

- Declare `int grid[4][6]` and populate it with realistic values (mix of zeros and small
  positive integers, e.g., some zeros and values up to `12`).
- Define `ROWS 4` and `COLS 6` as macros.
- Use nested `for` loops to:
  1. Print the full grid as a formatted table.
  2. Compute the **total defects per row** (print alongside each row).
  3. Compute the **maximum defect count per column** across all rows (requires a separate
     pass: iterate columns in the outer loop, rows in the inner loop — note the contrast
     with row-major traversal performance).
- Print a column summary line: `"Col X max defects: N"`.
- Identify and print which column has the **overall highest maximum**.

**Expected skills tested:** 2D array, nested loops, row-major vs column-major traversal awareness,
per-row and per-column aggregation, macros.

---

## Problem 8 — Circular Sensor Buffer with Rolling Average (Medium–Complex)

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

**Expected skills tested:** `int32_t`, `size_t`, modulo wrapping, 1D array, `for` loop,
fixed-width types, circular buffer logic.

---

## Problem 9 — Multi-Zone Alarm Escalation State Machine (Complex)

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

**Expected skills tested:** 2D array, nested loops, `if`/`else if`/`else`, macros, `do-while`,
multi-snapshot iteration, per-zone state logic.

---

## Problem 10 — UART Packet Frame Validator (Complex — Embedded)

A microcontroller receives data packets over UART. Each packet is a `uint8_t` array with
the following fixed structure:

```
[ START_BYTE | LENGTH | DATA_0 | DATA_1 | ... | DATA_N | END_BYTE ]
```

- `START_BYTE` = `0xAA`
- `LENGTH` = number of `DATA` bytes that follow (1–8, inclusive)
- `DATA` bytes = `LENGTH` arbitrary `uint8_t` values
- `END_BYTE` = `0x55`
- Total packet length = `LENGTH + 3` bytes

**Your task:**

- Define `START_BYTE`, `END_BYTE`, `MAX_DATA_LEN`, and `MAX_TIMEOUT` as macros.
- Prepare **three test packets** as `uint8_t` arrays:
  1. A valid packet with `LENGTH = 4` and 4 data bytes.
  2. A corrupt packet where the `END_BYTE` is wrong.
  3. A truncated packet that runs out of bytes before `END_BYTE` (simulate with a shorter array).
- For each packet, use a `while` loop with a `uint32_t timeout` counter to walk through
  the bytes one at a time and validate:
  - Byte 0 must equal `START_BYTE`; if not, log `"FRAME ERROR: bad start byte"` and abort.
  - Byte 1 is `LENGTH`; if `LENGTH < 1` or `LENGTH > MAX_DATA_LEN`, log `"FRAME ERROR: invalid length"` and abort.
  - Consume `LENGTH` data bytes, storing them in a `uint8_t data_buf[8]`.
  - The next byte must equal `END_BYTE`; if not, log `"FRAME ERROR: bad end byte"`.
  - If the timeout counter reaches zero before `END_BYTE` is found, log `"FRAME ERROR: timeout"`.
  - On success, log `"PACKET OK — LENGTH: N"` and print all data bytes in hex.
- After all three packets, print a summary: packets valid / packets failed.

**Expected skills tested:** `uint8_t`, `uint32_t`, fixed-width types, `while` loop, watchdog
timeout pattern, `size_t`, macros, byte-level indexing, multi-packet loop, structured
error reporting.

---

 **Tip:** Attempt each problem in a new `.c` file. Compile with:
 ```
 gcc -Wall -Wextra -o problem_N problem_N.c
 ```
 Resolve every warning — clean compilation with `-Wall -Wextra` is part of the discipline.

#### Explanation of using -Wall -Wextra

In the world of C programming, the compiler is our first line of defense. By default, however, it is surprisingly "quiet." It will let us write dangerous code that might crash later without saying a word.

The flags `-Wall` and `-Wextra` are how we tell the compiler: **"Stop being polite and tell us everything that looks suspicious."**

---

##### 1. `-Wall` (Warning: All)

Despite the name, `-Wall` does not actually turn on *every* warning, but it activates the most important ones that indicate "logic smells."

* **Uninitialized Variables:** It warns us if we try to use a variable before giving it a value (which would result in random garbage data).
* **Unused Variables:** It tells us if we declared a variable but never used it, which helps us clean up "dead" code.
* **Missing Return Statements:** It catches us if we promised a function would return an `int` but we forgot to actually write `return`.
* **Sketchy Logic:** It warns us if we accidentally write `if (x = 5)` (which sets x to 5) instead of `if (x == 5)` (which compares them).

---

##### 2. `-Wextra` (Warning: Extra)

This turns on even more warnings that `-Wall` misses. These are often about "legal but dangerous" C patterns that we should avoid.

* **Comparison of Signed and Unsigned:** This is exactly what we discussed earlier! If we try to compare an `int` to a `size_t`, `-Wextra` is the flag that will shout at us.
* **Unused Parameters:** If our function receives data but the function body ignores it, this flag points it out.
* **Missing Initializers:** If we create a big struct or array but only fill half of it, it reminds us that the rest is currently empty.

---

##### 3. Why Engineers Insist on "Clean Compilation"

When we see the instruction *"Resolve every warning,"* it’s about **Professional Discipline**.

In complex engineering systems (like a car's braking system or a satellite), a single "ignored" warning about a signed/unsigned mismatch can lead to a catastrophic failure. By forcing ourselves to compile with `-Wall -Wextra` and fixing every warning, we are:

1. **Future-proofing:** Code that has warnings today often crashes tomorrow when we move it to a different computer.
2. **Reducing Bugs:** Many "weird" bugs are caught instantly by our compiler before we even run the program.
3. **Clarity:** A clean build tells our teammates, "We have audited this code and it is stable."

---

##### The "Golden Command"

Most professionals actually use three flags together:

```bash
gcc -Wall -Wextra -Werror -o program program.c

```

* **`-Werror`**: This is "Hard Mode." It tells the compiler to treat **Warnings as Errors**. If there is even one tiny warning, the compiler will refuse to create the program. This forces us to be 100% disciplined.

---

