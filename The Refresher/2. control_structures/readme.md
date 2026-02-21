# Control Structures and Introduction to Operators

---

## Picking Up From Where We Left Off

In our last session, we built a solid understanding of how data is actually represented inside a machine. We covered primitive types and how much memory each one occupies, how signed integers use Two's complement to represent negative numbers, how IEEE 754 encodes floating point numbers with a sign, exponent, and mantissa, and why that leads to precision loss. We also looked at size_t, and the fixed-width types from stdint.h like uint32_t that give us guarantees across platforms.

That foundation matters because everything we do today, looping, branching, switching, operating on bits, all of it ultimately works on those raw data representations. When we write a loop counter, we are choosing a data type. When we write a condition, we are comparing bit patterns. Keep that mental model active.

---

## Part 1: Control Structures

Control structures determine the order in which a program executes. Without them, every program would just run top to bottom, once, and stop. They give us repetition and decision-making.



### 1.1 Arrays

Before loops make full sense, we need to talk about arrays, because loops and arrays are almost always paired together in engineering systems.

**An array is a contiguous block of memory that holds a fixed number of elements of the same type. The word contiguous is the important word. Every element sits right next to the previous one in memory with no gaps.**

```
int temperatures[5] = {23, 25, 19, 30, 28};
```

What the machine actually does here is **reserve 5 x 4 bytes = 20 bytes of memory in one unbroken stretch**. The **name `temperatures`** is not a variable in the traditional sense. It is **a label** that refers to the **address** of the very **first element**.

```
Memory:
Address 1000: 23
Address 1004: 25
Address 1008: 19
Address 1012: 30
Address 1016: 28
```

When we write `temperatures[2]`, the machine computes:
```
base_address + (index x sizeof(type))
= 1000 + (2 x 4)
= 1008
```

This is called pointer arithmetic and it happens implicitly every time we use an index. This is also why arrays in C are zero-indexed. **Index 0 means an offset of zero bytes from the base**.


**The engineering-critical detail most people ignore: arrays do not know their own size.**
If we declare `int temperatures[5]` and then access `temperatures[7]`, the compiler will not stop us. The machine will go to address 1000 + (7 x 4) = 1028, which is memory that belongs to something else entirely. **This is called an out-of-bounds access** and it is one of the most common sources of bugs and security vulnerabilities in C programs. In embedded systems, this can silently corrupt adjacent variables, making the bug extremely hard to find.

The correct discipline is to always carry the size alongside the array, either as a separate variable or as a macro constant.

```
#define TEMP_COUNT 5
int temperatures[TEMP_COUNT];
```
We store the array size as a macro or variable because C does not track or check an array’s length, so loops and functions must use that size to know the correct boundary.
Using the stored size as the loop limit avoids hard-coded values and ensures we only access indices from `0` to `size - 1`, preventing out-of-bounds undefined behavior.


**Multidimensional Arrays (Row-Major Order in C)**

In C, a 2D array is stored as a single continuous (flat) block of memory in **row-major order**, meaning each row is stored completely before the next row begins.

Example:

```
int matrix[3][4] = { // matrix[row][col] is at offset: (row * 4 + col) * sizeof(int), here 4 is the size of data type(int) in byte
    {1, 2, 3, 4}, //row 0
    {5, 6, 7, 8}, //row 1
    {9,10,11,12}  //row 2
};
```

Since an `int` is 4 bytes, the total size is:

3 × 4 × 4 bytes = **48 bytes**

In memory, it is stored linearly like this:

```
1 2 3 4 5 6 7 8 9 10 11 12
```

So `matrix[1][2]` (which is `7`) is accessed by skipping:

1 full row (4 integers) + 2 integers into the next row
= (1 × 4 + 2) = 6 positions from the start.

Main idea:
A multidimensional array in C is not stored as separate rows, it is one contiguous block of memory laid out row by row.


In embedded systems and DSP (Digital Signal Processing) work, knowing this layout matters for cache performance. Iterating row by row is much faster than iterating column by column because the CPU prefetches sequential memory. This is a real, measurable performance difference.



###Here is the expanded version of your text. I have kept every word of your original content and added **[Clarification]** blocks and a summary table to make the "Engineering Techniques" and the "Infinite Loop Trap" easier to visualize.

---

### 1.2 Loops

Loops give us repetition. There are three forms in C, and while they are interchangeable in theory, each one carries a different intention that experienced engineers read at a glance.

#### The for Loop

The for loop is used when we know, or can express, the number of iterations before the loop begins.

```
for (initialization; condition; update) {
    // body
}

```

```
for (int i = 0; i < 5; i++) {
    printf("%d\n", temperatures[i]);
}

```

The three parts of the for loop header communicate intent very clearly:

* **Initialization (`int i = 0`):** We start at 0.
* **Condition (`i < 5`):** We run while `i` is less than 5.
* **Update (`i++`):** We step forward by 1 each time.

**Engineering technique most people skip: the loop variable type matters.**

In many engineering systems, loop variables are declared as `uint32_t` or `size_t` rather than `int`. This matters because:

* If the loop count comes from an unsigned type (like an array size), comparing `int` to `unsigned int` can cause subtle bugs due to implicit type conversion.

If you compare a negative `int` to an `unsigned int`, the computer "re-interprets" the negative number as a massive positive number (often over 4 billion). This causes your `i < count` check to fail unexpectedly.

* `size_t` is the correct type for indexing arrays because it matches the platform's pointer size and is what `sizeof` returns.

Think of `size_t` as a "custom-fit" box. On a 32-bit computer, it's 32 bits wide; on a 64-bit computer, it's 64 bits wide. Using it ensures your loop can count every possible item your specific computer is capable of holding in its memory.

```
size_t i;
for (i = 0; i < TEMP_COUNT; i++) {
    // correct and portable
}

```

---

### The "Counting Down" Trap

There is a classic trap with unsigned loop variables when counting down:

```
// DANGEROUS: infinite loop
for (uint32_t i = 5; i >= 0; i--) {
    // when i reaches 0 and decrements, it wraps to 4294967295
    // because unsigned integers cannot be negative
}

```

Since a `uint32_t` is "unsigned," it is physically impossible for it to be less than 0. When the computer tries to do `0 - 1`, the number "wraps around" to the highest possible value (like an odometer on a car flipping from 0000 to 9999). Because `4,294,967,295` is still "greater than or equal to 0," the loop never stops.

This is a real and common mistake in embedded systems. The fix is to restructure the condition:

```
for (uint32_t i = 5; i-- > 0; ) {
    // i-- evaluates to the old value, then decrements
    // when i was 1, old value is 1 (truthy), i becomes 0, loop runs
    // when i was 0, old value is 0 (falsy), loop exits, i wraps but we never use it
}

```

#### How the "Condition" acts as an "Update"

In this specific engineering trick, the **Condition** is doing two jobs at once.

| Step | What happens in `i-- > 0` | Value of `i` inside the `{ body }` |
| --- | --- | --- |
| **Start** | `i` is **5**. | — |
| **Turn 1** | Is `5 > 0`? **Yes**. (Then `i` becomes **4**) | `i` is **4** |
| **Turn 2** | Is `4 > 0`? **Yes**. (Then `i` becomes **3**) | `i` is **3** |
| **Turn 3** | Is `3 > 0`? **Yes**. (Then `i` becomes **2**) | `i` is **2** |
| **Turn 4** | Is `2 > 0`? **Yes**. (Then `i` becomes **1**) | `i` is **1** |
| **Turn 5** | Is `1 > 0`? **Yes**. (Then `i` becomes **0**) | `i` is **0** |
| **Exit** | Is `0 > 0`? **No**. (Loop stops) | — |

#### Why the last slot is empty

The last slot in a `for` loop header is optional. Engineers leave it empty in this case because the "Update" (the subtraction) already happened during the "Condition" check.

Adding an `i--` in that third slot would be like taking two steps for every one check at the door. You'd finish faster, but you'd skip half the people in line!


#### The while Loop

The while loop is used when the number of iterations is not known in advance. We keep looping as long as a condition remains true.

```
while (condition) {
    // body
}
```

```
int data = read_sensor();
while (data != READY_SIGNAL) {
    data = read_sensor();
}
```

This pattern appears constantly in embedded systems: polling a peripheral until it signals that it is ready. The condition is checked before the body executes, so if the condition is false from the start, the body never runs.

**The engineering discipline here is to always have a guaranteed exit.** A hardware register might never become ready due to a fault. A well-engineered system adds a timeout:

```
uint32_t timeout = 10000;
while (data != READY_SIGNAL && timeout > 0) {
    data = read_sensor();
    timeout--;
}

if (timeout == 0) {
    handle_error();
}
```

This is called a watchdog pattern and it is non-negotiable in production embedded code.



#### The do-while Loop

The do-while loop guarantees that the body executes at least once before the condition is checked.

```
do {
    // body
} while (condition);
```

```
int choice;
do {
    printf("Enter a valid option (1-3): ");
    scanf("%d", &choice);
} while (choice < 1 || choice > 3);
```

The practical use case is anywhere we need to perform an action before we can evaluate whether to continue. Reading user input, initializing a buffer, attempting a connection once before deciding to retry.

In embedded systems, do-while appears in a specific idiom used in macros. We will revisit this when we cover macros in depth, but briefly:

```
#define SAFE_INIT(x) do { init(x); verify(x); } while(0)
```

The `do { } while(0)` wrapper allows a multi-statement macro to behave correctly inside an `if` statement without requiring braces. This is a genuine engineering technique that most beginners never encounter until they break something without it.



### 1.3 Conditional Logic

#### The if-else Chain

The if-else structure is the most fundamental decision mechanism.

```
if (temperature > 100) {
    trigger_overheat_alarm();
} else if (temperature > 80) {
    increase_fan_speed();
} else {
    maintain_current_state();
}
```

The machine evaluates conditions top to bottom and stops at the first true one. This has a performance implication: the most likely condition should appear first when performance is critical. In real-time embedded systems, this is not a micro-optimization. It is a design consideration.

**Engineering detail most people miss: conditions are evaluated lazily (short-circuit evaluation).**

In a logical AND expression, if the first operand is false, the second is never evaluated. In a logical OR expression, if the first operand is true, the second is never evaluated.

```
if (ptr != NULL && ptr->value > 0) {
    // safe: if ptr is NULL, the second condition never evaluates
    // so we never dereference a null pointer
}
```

This is not just a convenience. In embedded systems, the second operand might involve reading a hardware register, triggering a hardware transaction, or calling a function with side effects. Short-circuit evaluation means the order of operands is a deliberate design choice, not just style.



#### The switch Statement

The switch statement tests a single integer expression against multiple constant values.

```
switch (state) {
    case STATE_IDLE:
        handle_idle();
        break;
    case STATE_RUNNING:
        handle_running();
        break;
    case STATE_ERROR:
        handle_error();
        break;
    default:
        handle_unknown();
        break;
}
```

**Why switch can be more efficient than if-else chains**

When a compiler sees a switch statement over a contiguous or near-contiguous range of integers, it can generate a jump table. **A jump table is an array of addresses**. The CPU takes the value being switched on, uses it as an index into this table, and jumps directly to the right address. This means the cost of reaching any case is the same regardless of how many cases there are. It is O(1) dispatch.

An if-else chain on the other hand checks each condition sequentially. If the matching case is the last one, every previous condition was evaluated. This is O(n) in the worst case.

In state machine implementations, which are the backbone of most embedded firmware, switch statements over an enum are the standard approach precisely because of this jump table behavior.

When the compiler sees a `switch` statement over an `enum` like this:

```
typedef enum {
    STATE_IDLE    = 0,
    STATE_INIT    = 1,
    STATE_RUNNING = 2,
    STATE_ERROR   = 3
} SystemState;

SystemState current_state = STATE_IDLE;

switch (current_state) {
    case STATE_IDLE:
        ...
    case STATE_INIT:
        ...
    case STATE_RUNNING:
        ...
    case STATE_ERROR:
        ...
}
```

it notices something important:

* The values are integers.
* They start at 0.
* They increase by 1.
* They form a small, continuous range (0 to 3).

Because of this, instead of generating a chain of comparisons, the compiler can create a jump table.

A jump table is simply an array of function addresses, where each index corresponds to a case value. Conceptually, it looks like this:

```
index 0 → address of handle_idle
index 1 → address of handle_init
index 2 → address of handle_running
index 3 → address of handle_error
```

Then the generated logic becomes:

1. Check if the value is within range (0–3).
2. Use the value directly as an index into the table.
3. Jump to the address stored at that index.

So instead of checking:

```
if state == 0
else if state == 1
else if state == 2
else if state == 3
```

the CPU performs one indexed lookup and jumps directly to the correct block.

That is what “the compiler will likely generate a jump table here” means: it transforms the `switch` into a constant-time indexed jump instead of a sequence of comparisons.

This is why `switch` statements over enums are commonly used in embedded state machines — they map very naturally to efficient jump tables when the values are contiguous.



**The break statement and intentional fall-through**

Every case needs a break unless we deliberately want fall-through. Fall-through means execution continues into the next case without re-checking.

```
switch (error_code) {
    case ERR_TIMEOUT:
    case ERR_NO_RESPONSE:
        // both cases share this handler (fall-through is intentional)
        reset_communication();
        break;
    case ERR_HARDWARE:
        shutdown_safely();
        break;
}
```

Forgetting a break accidentally is one of the most common C bugs. Good practice is to mark intentional fall-through with a comment so it is clear to anyone reading the code that the omission was deliberate.

**The default case**

Always include a default case. In safety-critical systems, a switch over a state enum with no default case means that if a bit-flip or memory corruption produces an invalid state value, the machine silently does nothing. **A well-written default case logs an error, triggers an assertion, or brings the system into a known safe state**.



## Part 2: Introduction to Operators


### The Core Idea: What Is a Bitwise Operator, Really?

Before memorizing any operator, understand this one thing:

Every value stored in our computer is just a sequence of 1s and 0s. A bitwise operator does not care about the number. It looks at each individual bit position and makes a decision there.

Think of it like a row of light switches. Each switch is either ON (1) or OFF (0). A bitwise operator takes two rows of switches and produces a third row based on a simple rule applied to each column independently.

```
Value A:   1  0  1  1  0  1  0  0
Value B:   1  1  0  1  0  0  1  0
           -  -  -  -  -  -  -  -
           Column by column, apply the rule
```

That mental image will carry us through every bitwise operator.

---

### Bitwise AND ( & )

**The Rule:** The result bit is 1 only when BOTH input bits are 1. If either is 0, the result is 0.

```
0 AND 0 = 0
0 AND 1 = 0
1 AND 0 = 0
1 AND 1 = 1       <-- only this case gives 1
```

**A plain English analogy:** Two people must both say YES for the answer to be YES. One NO from either person and the answer is NO.

**Now a real example:**

Imagine a vending machine controller. It has an 8-bit status byte where each bit reports something different:

```
Bit 7: Door open
Bit 6: Out of stock
Bit 5: Payment received
Bit 4: Item dispensing
Bit 3: Temperature OK
Bit 2: Power stable
Bit 1: Motor running
Bit 0: Ready
```

Someone wants to buy something from this vending machine and the vending machine system us this byte: `0b10100101`

We want to check one specific question: has payment been received? That is bit 5.

We do not want the other bits confusing our answer. So we create a mask, which is just a number where only the bit(bit 5) we care about is set to 1 and everything else is 0:

```
Status byte:  1  0  1  0  0  1  0  1
Our mask:     0  0  1  0  0  0  0  0     (only bit 5 is 1)
              -  -  -  -  -  -  -  -
AND result:   0  0  1  0  0  0  0  0     (nonzero, so YES payment received)
```

In code:

```
uint8_t status = 0b10100101;
uint8_t payment_mask = (1 << 5);   // creates 0b00100000

if (status & payment_mask) {
    dispense_item();
}
```

The `(1 << 5)` simply means "take the number 1 and shift it 5 positions to the left," which places a single 1 in bit position 5.In binary, this turns 00000001 into 00100000.

**What AND is used for: isolating (reading) specific bits.**

---

### Bitwise OR ( | )

**The Rule:** The result bit is 1 when EITHER input bit is 1. Both must be 0 to produce 0.

```
0 OR 0 = 0       <-- only this case gives 0
0 OR 1 = 1
1 OR 0 = 1
1 OR 1 = 1
```

**Plain English analogy:** Two people vote. If even one says YES, the answer is YES. Only if both say NO is the answer NO.

**Real example:**

Same vending machine. We want to turn ON the "item dispensing" indicator (bit 4) without touching any other bit in the status register. We cannot just write a new value to the whole register because that would overwrite the other bits that hardware is currently managing.

```
Current status:  1  0  1  0  0  1  0  1
Our mask:        0  0  0  1  0  0  0  0     (only bit 4 is 1)
                 -  -  -  -  -  -  -  -
OR result:       1  0  1  1  0  1  0  1     (bit 4 is now 1, nothing else changed)
```

In code:

```
status |= (1 << 4);    // set bit 4, leave all others unchanged
```

**What OR is used for: turning ON (setting) specific bits.**

---

### Bitwise XOR ( ^ )

**The Rule:** The result bit is 1 when the two input bits are DIFFERENT. If they are the same, the result is 0.

```
0 XOR 0 = 0     (same, so 0)
0 XOR 1 = 1     (different, so 1)
1 XOR 0 = 1     (different, so 1)
1 XOR 1 = 0     (same, so 0)
```

**Plain English analogy:** Two people must disagree for the answer to be YES. If they both agree (both YES or both NO), the answer is NO.

**Real example:**

We have a row of 8 LEDs on a panel, each controlled by one bit. We want to toggle (flip) some of them, meaning if an LED is ON we turn it OFF, and if it is OFF we turn it ON. This is a toggle, not a set or clear.

```
uint8_t led_state = 0b11001010;

// We want to toggle LEDs at bit positions 3, 2, 1
uint8_t toggle_mask = 0b00001110;

led_state ^= toggle_mask;
```

```
Before:          1  1  0  0  1  0  1  0
Toggle mask:     0  0  0  0  1  1  1  0
                 -  -  -  -  -  -  -  -
After:           1  1  0  0  0  1  0  0     (bits 3,2,1 flipped, rest unchanged)
```

XOR has a fascinating mathematical property that has a direct practical use:

```
Any value XOR'd with itself always equals zero:   A ^ A = 0
Any value XOR'd with zero stays the same:         A ^ 0 = A
```

This allows us to swap two variables without needing a third temporary variable:
```
int a = 100; int b = 103; 
a = a ^ b; // a now holds the combined bit pattern 
b = a ^ b; // extracts original a into b 
a = a ^ b; // extracts original b into a
```

We start with:

```
a = 100
b = 103
```

**Convert to binary**

```
100 = 01100100
103 = 01100111
```

So initially:

```
a = 01100100
b = 01100111
```

---

**Step 1: `a = a ^ b`**

```
   01100100   (a = 100)
^  01100111   (b = 103)
-------------
   00000011   (result = 3)
```

Now:

```
a = 00000011  (3)
b = 01100111  (103)
```

Notice how only the last two bits differ, so XOR gives `00000011`.

---

**Step 2: `b = a ^ b`**

Now:

```
   00000011   (a = 3)
^  01100111   (b = 103)
-------------
   01100100   (100)
```

Now:

```
a = 00000011  (3)
b = 01100100  (100)
```

The original value of `a` (100) has now moved into `b`.

---

**Step 3: `a = a ^ b`**

```
   00000011   (a = 3)
^  01100100   (b = 100)
-------------
   01100111   (103)
```

Now:

```
a = 01100111  (103)
b = 01100100  (100)
```

Values successfully swapped!

---

#### Why This Works

Because XOR has two key properties:

1. **A ^ A = 0**
2. **A ^ 0 = A**

After step 1, `a` holds `original_a ^ original_b`.

Step 2 cancels out `original_b`, leaving `original_a`.

Step 3 cancels out `original_a`, leaving `original_b`.

Each step “undoes” part of the previous XOR using the self-canceling property.



While modern compilers handle swapping efficiently anyway, this technique appears in performance-critical code and is a useful concept to understand.

**What XOR is used for: toggling specific bits.**

---

### Bitwise NOT ( ~ )

**The Rule:** Inverts every single bit. Every 1 becomes 0, every 0 becomes 1.

```
NOT 00001000  =  11110111
```

**Real example:**

We want to turn OFF (clear) bit 3 in our status register without touching anything else. We cannot use AND with a mask that has 0 in position 3 directly, because writing it manually for a 32-bit register would be tedious and error-prone.

Instead we do this:

```
status &= ~(1 << 3);
```

Step by step:

```
1 << 3 creates:      0  0  0  0  1  0  0  0
NOT of that:         1  1  1  1  0  1  1  1
AND with status:     0  0  0  0  0  0  0  0   //keeps all bits, forces bit 3 to 0
```

The NOT gives us a mask that has 1 everywhere except the bit we want to clear. AND-ing with that preserves all other bits and forces our target bit to 0.

**What NOT is used for: creating inverted masks for clearing specific bits.**

---

### Shift Operators ( << and >> )

These move all the bits in a value to the left or right by a specified number of positions. Bits that fall off the edge are lost, and the vacated positions are filled with 0.

**Left Shift: <<**

```
Value:         0  0  0  0  0  1  0  1     (decimal 5)
After << 2:    0  0  0  1  0  1  0  0     (decimal 20)
```

Each left shift by 1 position is identical to multiplying by 2. Shifting left by 2 multiplies by 4. Shifting left by n multiplies by 2 to the power of n.

```
uint32_t x = 5;
x = x << 2;    // x is now 20 (5 * 4)
```

**Right Shift: >>**

```
Value:         0  0  0  1  0  1  0  0     (decimal 20)
After >> 2:    0  0  0  0  0  1  0  1     (decimal 5)
```

Each right shift by 1 is identical to integer division by 2.

```
uint32_t x = 20;
x = x >> 2;    // x is now 5 (20 / 4)
```

**Where shifts become essential in real engineering:**

In many communication protocols like UART, SPI, I2C, and in hardware registers, we need to pack multiple values into a single integer and later extract them back out. Here is a concrete scenario.

Suppose we are writing a function that builds a motor control command. The 16-bit command word is laid out as:

```
Bit 15:12 = Motor ID (which of 16 motors)
Bit 11:8  = Speed setting (0 to 15)
Bit 7:0   = Direction and flags
```

Packing:

```
uint8_t motor_id = 3;
uint8_t speed    = 7;
uint8_t flags    = 0b00100101;

uint16_t command = ((uint16_t)motor_id << 12) | ((uint16_t)speed << 8) | flags;
```

```
motor_id << 12:    0011  0000  0000  0000
speed    << 8:     0000  0111  0000  0000
flags:             0000  0000  0010  0101
OR together:       0011  0111  0010  0101
```

Extracting back:

```
uint8_t extracted_id    = (command >> 12) & 0x0F;   // shift down then mask 4 bits
uint8_t extracted_speed = (command >> 8)  & 0x0F;   // shift down then mask 4 bits
uint8_t extracted_flags =  command        & 0xFF;   // mask lowest 8 bits
```

This is exactly how every communication protocol frame, every hardware register, and every compact binary format works. Understanding shifts makes all of that readable.

**One rule to never break:** Always shift unsigned types. Shifting signed types, especially negative values, produces implementation-defined or undefined behavior in C. Whenever shifting matters for bit patterns, use `uint8_t`, `uint16_t`, `uint32_t`.

---

### Logical Operators vs Bitwise Operators

This distinction causes real bugs in production code, so we are going to be very precise about it.

**Bitwise operators** work on individual bits. The output is an integer that can be any value.

**Logical operators** (`&&`, `||`, `!`) do not care about individual bits at all. They treat any nonzero value as TRUE and zero as FALSE. The output is always either 0 or 1.

Here is the exact scenario where confusing them creates a bug:

```
uint8_t status = 0b00000100;   // only bit 2 is set, value is decimal 4
```

We want to check if bit 2 is set. The correct mask for bit 2 is `0x04` (which is also `0b00000100`, decimal 4).

```
// CORRECT approach
if (status & 0x04) {
    // this evaluates to 0b00000100 which is 4, which is nonzero, so TRUE
    // correctly enters the block
}

// WRONG approach
if (status && 0x04) {
    // this asks: "is status nonzero AND is 0x04 nonzero?"
    // status is 4 (nonzero = TRUE), 0x04 is 4 (nonzero = TRUE)
    // so this is TRUE... which seems fine here
}
```

Now watch what happens when the status register changes to `0b00001000` (bit 3 is set, bit 2 is NOT set):

```
uint8_t status = 0b00001000;   // bit 2 is NOT set

// CORRECT approach
if (status & 0x04) {
    // 0b00001000 AND 0b00000100 = 0b00000000 = 0, which is FALSE
    // correctly does NOT enter the block
}

// WRONG approach
if (status && 0x04) {
    // status is 8 (nonzero = TRUE), 0x04 is 4 (nonzero = TRUE)
    // result is TRUE, but bit 2 is NOT actually set
    // we enter the block when we should not. This is the bug.
}
```

The logical `&&` operator only asks "is this value nonzero," not "is this specific bit set." In a system with a hardware register that has multiple bits active simultaneously, using `&&` instead of `&` will produce behavior that appears correct in simple tests but fails in deployment.

---

### The Four Bitwise Operations Summarized as a Reference

```
To READ a specific bit:    value & mask          (AND with mask)
To SET a specific bit:     value |= (1 << n)     (OR with shifted 1)
To CLEAR a specific bit:   value &= ~(1 << n)    (AND with inverted mask)
To TOGGLE a specific bit:  value ^= (1 << n)     (XOR with shifted 1)
```

These four lines are the complete toolkit for working with any hardware register, protocol byte, or packed integer. We will use them constantly from this point forward.

---

## Where We Are and Where We Are Going

Today we covered the full landscape of control structures: arrays and their memory model, the three loop forms and when to use each, conditional logic including short-circuit evaluation, and the switch statement including jump table optimization and its role in state machines. We then opened the chapter on operators with a thorough look at bitwise operations, the engineering patterns built around them, and the critical distinction between logical and bitwise operators.

Next session we will complete the operators chapter with the ternary operator, operator precedence and associativity, and we will go through some combined engineering exercises that bring loops, conditions, and bitwise operations together the way they actually appear in real systems.

