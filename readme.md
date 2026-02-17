# C Programming

---

## Table of Contents

1. [What is C?](#what-is-c)
2. [Why Learn C?](#why-learn-c)
3. [Where C is Used](#where-c-is-used)
4. [Setting Up our Environment](#setting-up-our-environment-to-start-with-C-language)
5. [our First C Program](#our-first-c-program)
6. [How a C Program is Structured](#how-a-c-program-is-structured)
7. [Core Language Concepts](#core-language-concepts)
8. [How C Works Internally](#how-c-works-internally)
9. [Memory: The Heart of C](#memory-the-heart-of-c)
10. [Learn the Complex Words Here](#learn-the-complex-words-here)
11. [A Note on Patience](#a-note-on-patience)
12. [What to Learn Next](#what-to-learn-next)

---

## What is C?

C is a general-purpose programming language created by Dennis Ritchie at Bell Labs between 1969 and 1973. It was designed to write the **Unix operating system**, and it succeeded. Today, over fifty years later, C remains one of the most widely used languages on the planet.

C sits close to the hardware. It gives us direct control over memory, processor instructions, and system resources without the overhead of higher-level abstractions. This makes it fast, small, and portable across almost every computing platform that exists.

If we are completely new to programming, C will teach us how computers actually work, not just how to use a programming environment that hides the details from us.

---

## Why Learn C?

**Let's understand computers at a deeper level:** Higher-level languages like Python or JavaScript manage memory, data types, and execution flow for us. C does not. When we write C, we decide where data lives, how long it lives, and how it is accessed. we understand computers at a deeper level. Higher-level languages like Python or JavaScript manage memory, data types, and execution flow for us; they make the decisions silently, behind the scenes, C does not. When we write C, we are the one deciding where data lives, how long it lives, and how it is accessed. Nothing happens without our explicit instruction, which means we see exactly what the machine is doing and why. That understanding transfers to every other language we ever learn.

**Performance is unmatched for systems work:** C compiles directly to machine code with minimal overhead. When a program needs to be fast and small, C is almost always the first choice.

**The ecosystem is enormous:** **The Linux kernel, Python interpreter, SQLite, Redis, Nginx, and the majority of embedded firmware** in the world are all written in C. Reading and contributing to these evolutionary projects requires knowing C.

**It is a prerequisite for C++:** C++ is built on top of C. Learning C first means we understand what C++ is doing underneath its abstractions.

**It sharpens our thinking:** C has no garbage collector, no safety net for array boundaries, and no exceptions by default. we must think carefully and precisely. That discipline makes us a better programmer in any language.

---

## Where C is Used

**Operating Systems:** The **Linux kernel** is written almost entirely in C. So are the cores of **macOS, Windows**, and every **real-time operating system (RTOS)** used in industry.

**Embedded Systems and Firmware:** Microcontrollers in cars, medical devices, industrial machines, home appliances, and aerospace systems run C firmware. C is the dominant language in this space because it compiles to small, efficient binaries and gives direct hardware access.

**Compilers and Interpreters:** The **CPython interpreter** (the standard Python runtime) is written in C. GCC, Clang, and most other compilers are written in C or C++.

**Databases:** **SQLite, PostgreSQL's core**, and many other database engines are implemented in C for performance and portability.

**Networking and Security:** **OpenSSL**, the library that secures the majority of internet traffic, is written in C. Network drivers, packet processors, and firewall engines are written in C.

**Scientific and High-Performance Computing:** Numerical libraries like **BLAS and LAPACK**, which underpin **NumPy and MATLAB**, are written in **C and Fortran**. When performance matters at scale, C is in the loop.

**Game Engines and Graphics:** Low-level rendering pipelines, physics engines, and audio processing often use C for the performance-critical core.

**Academic Research:** Algorithms research, systems research, and computer architecture research all rely on C because it allows precise control over performance and memory behavior.

---

## Setting Up our Environment to start with C language

we need two things: a C compiler and a text editor.

**On Linux:**

GCC is almost certainly already installed. Check with:

```
gcc --version
```

If not, install it:

```
sudo apt install gcc        # Debian / Ubuntu
sudo dnf install gcc        # Fedora / RHEL
```

**On macOS:**

Install Xcode Command Line Tools, which includes the Clang compiler:

```
xcode-select --install
```

**On Windows:**

Install [MinGW-w64](https://www.mingw-w64.org/) or use the Windows Subsystem for Linux (WSL), which gives us a full Linux environment inside Windows.

**Text Editor:**

Any plain-text editor works. We will use Visual Studio Code. It is a good choice because it has syntax highlighting, error indicators, and a built-in terminal. For working on servers or in terminals, Vim or Nano are standard options.

**We do not need an IDE to write C**. A text editor and a terminal are sufficient and often preferred.

---

## our First C Program

Create a file called `hello.c` and write this inside it:

```c
#include <stdio.h>

int main(void) {
    printf("Hello, world.\n");
    return 0;
}
```

Now compile it:

```
gcc hello.c -o hello
```

This produces an executable file called `hello`. Run it:

```
./hello
```

Output:

```
Hello, world.
```

That is a complete C program. Every piece of it has a specific purpose, and understanding each piece is the foundation of everything that follows.

---

## How a C Program is Structured

### Preprocessor Directives

```c
#include <stdio.h>
```

Lines that begin with `#` are [preprocessor directives](#preprocessor). They run before [compilation](#compilation). `#include <stdio.h>` tells the preprocessor to paste the contents of the standard input/output header file into our program. That header declares functions like `printf` so the compiler knows they exist.


### The main Function

```c
int main(void) {
    ...
    return 0;
}
```

Every C program must have exactly one `main` function. This is the entry point. When the operating system runs our program, it calls `main`. The `int` before `main` means the function returns an integer. Returning `0` signals success to the operating system. Returning any other value signals an error.

### Statements and Semicolons

```c
printf("Hello, world.\n");
```

Each statement ends with a semicolon. A statement is one instruction. The `\n` inside the string is an escape sequence meaning newline, which moves the terminal cursor to the next line.

### Curly Braces Define Blocks

```c
{
    ...
}
```

Curly braces group statements into a block. The block following `main` contains everything the function does. Blocks are also used with loops, conditionals, and other structures.

---

## Core Language Concepts

### Variables and Data Types

Before we can use a value in C, we must declare a variable and tell the compiler what type of data it will hold.

C has a small set of primitive types. The most common ones are `int`, `float`, `double`, `char`, and `long`. The type determines how much memory is reserved and how the bits are interpreted.

### Input and Output


`printf` writes formatted text to the terminal. `scanf` reads formatted input from the terminal. The `%d` is a format specifier meaning a decimal integer. The `&` before `number` in `scanf` gives the function the memory address of the variable so it can write a value there directly. This is our first encounter with pointers, even if it does not look like one yet.

### Loops

The `for` loop has three parts: initialization (`int i = 0`), the condition that keeps it running (`i < 5`), and the update after each iteration (`i++`).

### Functions

Functions take parameters and return a value. Breaking code into functions makes programs easier to read, test, and reuse.

### Arrays

An array stores multiple values of the same type in contiguous memory. Indexing starts at zero.

---

## How C Works Internally

Understanding what happens between writing code and running a program is important in C because we are working close to the machine.

### Step 1: Preprocessing

The compiler first runs the preprocessor. It **handles all `#include` and `#define` directives**, expanding them into raw C source code. we never see this intermediate output normally, but it exists.

### Step 2: Compilation

The compiler **translates our C source code into assembly language**, which is a human-readable representation of machine instructions specific to our CPU architecture.

### Step 3: Assembly

An assembler converts the assembly code into **object code:** binary machine instructions stored in an object file (`.o` on Linux, `.obj` on Windows). This file contains machine code but is *not yet executable* because it may reference functions defined elsewhere.

### Step 4: Linking

The linker takes our **object files and any libraries** they depend on and **combines them into a single executable file**. It resolves all references so that calls to functions like `printf` point to the actual machine code for those functions.

When we run `gcc hello.c -o hello`, all four steps happen automatically in sequence.

### What the CPU Actually Does

The resulting executable is a sequence of machine instructions loaded into RAM. The CPU fetches each instruction from memory(RAM-->memory, from now on we will call RAM as memory), decodes it, executes it, and moves to the next one. Variables live in memory. Function calls push data onto the call stack in memory. The CPU has registers, which are small, extremely fast storage locations used during computation.

C gives us a model of programming that maps directly onto this: variables correspond to memory locations, function calls correspond to stack operations, and arithmetic corresponds to CPU instructions.

---

## Memory: The Heart of C

Memory is where C differs most dramatically from languages like Python or Java.

### The Stack

When a function is called, space for its local variables are automatically allocated on the stack. When the function returns, that space is automatically freed. Stack memory is fast and managed for us, but it is limited in size and tied to the lifetime of the function.

### The Heap

The heap is a large pool of memory we can request at runtime using `malloc` and release using `free`.

If we forget to call `free`, the memory is never returned to the system while the program is running. This is a memory leak. In long-running programs, memory leaks cause the program to consume more and more RAM until the system runs out.

### Pointers

A pointer is a variable that stores a memory address rather than a value directly.

Pointers are the most powerful and most dangerous feature of C. They allow us to build complex data structures like linked lists and trees, to pass large amounts of data efficiently, and to interact with hardware directly. They also allow us to corrupt memory in ways that are difficult to debug if we use them incorrectly. Understanding pointers takes time and practice. That is normal.

---


## Learn the Complex Words Here

### Preprocessor

Before the compiler ever reads our code, a separate tool called the preprocessor makes a first pass through it. Think of it as a find-and-replace step that prepares our source file for actual compilation.

Every line starting with `#` is an instruction to the preprocessor, not to the compiler. The two we will encounter most often are `#include` and `#define`.

`#include` takes an entire file and pastes it into ours at that exact line. When we write `#include <stdio.h>`, the preprocessor locates the `stdio.h` file on our system and inserts its contents before handing our code to the compiler. That file contains declarations telling the compiler what functions like `printf` and `scanf` look like, what arguments they take, and what they return. Without it, the compiler would see a call to `printf` and have no idea what it is.

`#define` creates a named constant or a macro. For example, `#define MAX 100` means every place the preprocessor sees `MAX` in our code, it replaces it with `100` before compilation begins. No memory is used, no variable is created; it is purely a text substitution.

The preprocessor output is still plain C source code. we never need to look at it directly, but knowing it exists explains why `#include` feels like copy-pasting and why preprocessor errors look different from compiler errors.

---

### Compilation

Compilation is the process of translating our C source code into machine code that our CPU can execute directly.

When we run `gcc hello.c -o hello`, GCC performs four steps in sequence, though it handles them all automatically. First, the preprocessor runs. Then the compiler translates our cleaned-up C code into assembly language, which is a low-level, human-readable representation of CPU instructions. An assembler then converts that into an object file containing raw binary machine instructions. Finally, the linker combines our object file with any libraries it depends on and produces the final executable.

The key thing to understand as a beginner is that the C we write is not what the CPU runs. our source code is a set of instructions written for humans to read and write. The compiler's job is to understand our intent and produce the equivalent sequence of binary instructions that the CPU actually executes. A good compiler does this translation extremely efficiently, which is a large part of why C programs are so fast.

When compilation fails, the compiler tells us the file name, the line number, and a description of the problem. Reading those messages carefully and literally is the most important debugging skill we will develop early on.

---


## A Note on Patience

C will frustrate us. Segmentation faults, memory errors, and cryptic compiler messages are part of the process. Every experienced C programmer has spent hours hunting a bug caused by an off-by-one error in a pointer or a forgotten `free`. These experiences are not signs that we are doing it wrong. They are how we learn to think carefully, read error messages precisely, and develop an intuition for how programs behave in memory.

The time we invest in C pays compound interest across every system, language, and problem we encounter afterward.

---

# Happy C Learning

## What to Learn Next

Once we are comfortable with the basics above, there is a clear path forward.

**Strings in C.** Strings are arrays of `char` terminated by a null byte. The standard library has functions for working with them: `strlen`, `strcpy`, `strcat`, `strcmp`.

**Structs.** A struct groups related variables of different types under a single name. It is the foundation of data modeling in C.

**File I/O.** Reading from and writing to files using `fopen`, `fread`, `fwrite`, `fprintf`, and `fclose`.

**Dynamic data structures.** Build linked lists, stacks, queues, and trees using structs and pointers. This is where our pointer knowledge becomes essential.

**Makefiles.** Real C projects have multiple source files. A Makefile automates compilation and is the standard build tool for C projects.

**Debugging with GDB.** The GNU Debugger lets us step through a program line by line, inspect variable values, and find exactly where something goes wrong.

**The C Standard Library.** Explore `string.h`, `math.h`, `stdlib.h`, `time.h`, and `errno.h`. The standard library solves many common problems without requiring external dependencies.

---
We will be following this doc to master this tech evolution over the time. The doc will be updated as days passed. Find the doc link here: https://docs.google.com/document/d/1A1GsRsRRwOoXu-9jQyioJnlh7uUdqrablBZ9PniGvF4/edit?usp=sharing
---
## Recommended Resources

- **The C Programming Language** by Brian Kernighan and Dennis Ritchie. Written by the people who created C. Concise, precise, and still the best single reference for the language.
- **CS50 by Harvard** (available free on edX). A well-structured introductory course that teaches C as its primary language for the first half.
- **Beej's Guide to C Programming** (free online at beej.us). Practical and readable, with good coverage of memory and pointers.
- **man pages.** On any Linux or macOS system, run `man printf` or `man malloc` to read the official documentation for any standard function. This habit pays dividends for the rest of our career.

---
