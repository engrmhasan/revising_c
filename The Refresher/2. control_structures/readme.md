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

