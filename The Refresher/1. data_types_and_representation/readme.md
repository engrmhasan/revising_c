# Data Types and Memory Usage in C

This document explores the memory usage, ranges, and behavior of various data types in C.

---

## Memory Usage of Basic Data Types

### Sizes of Data Types

- **`sizeof(int)` = 4**: An `int` takes 4 bytes of memory. It is used to store whole numbers (e.g., -10, 0, 25).
- **`sizeof(long)` = 4**: A `long` takes 4 bytes on this system. It stores larger whole numbers (size may vary by system).
- **`sizeof(short)` = 2**: A `short` takes 2 bytes of memory. It stores smaller-range whole numbers.
- **`sizeof(float)` = 4**: A `float` takes 4 bytes. It stores decimal (fractional) numbers with single precision.
- **`sizeof(double)` = 8**: A `double` takes 8 bytes. It stores decimal numbers with higher precision than `float`.
- **`sizeof(char)` = 1**: A `char` takes 1 byte. It stores a single character (like 'A', 'b', or '7').

Here are the **actual value ranges** for each type (typical 4-byte `int` and `long` on a 32-bit system):

* **int (4 bytes)**
  Signed: **−2,147,483,648 to 2,147,483,647**
  Unsigned: **0 to 4,294,967,295**

* **long (4 bytes)**
  Signed: **−2,147,483,648 to 2,147,483,647**
  Unsigned: **0 to 4,294,967,295**

* **short (2 bytes)**
  Signed: **−32,768 to 32,767**
  Unsigned: **0 to 65,535**

* **float (4 bytes)**
  Approx: **±1.2 × 10⁻³⁸ to ±3.4 × 10³⁸**
  Precision: about **6–7 decimal digits**

* **double (8 bytes)**
  Approx: **±2.2 × 10⁻³⁰⁸ to ±1.7 × 10³⁰⁸**
  Precision: about **15–16 decimal digits**

* **char (1 byte)**
  Signed: **−128 to 127**
  Unsigned: **0 to 255**


Those numbers are **real and standard ranges**, but they depend on the system and compiler.

They come from how binary numbers work in memory.

For example (4-byte signed int):

* 4 bytes = 32 bits
* Signed integers use 1 bit for sign, 31 bits for value
* Range = −2³¹ to (2³¹ − 1)
* = −2,147,483,648 to 2,147,483,647

Unsigned uses all bits for value:

* Range = 0 to (2³² − 1)
* = 0 to 4,294,967,295

The same math applies to `short` (16 bits), `char` (8 bits), etc.

For `float` and `double`, the ranges come from the IEEE 754 floating-point standard, which defines how decimal numbers are stored in binary.

Important:
C/C++ does NOT guarantee exact sizes for `int` and `long`.
Check your system’s actual limits using:

You check them by **printing the macros** defined in `<limits.h>` and `<float.h>`.

Here is a simple example program:

  ```c
  #include <stdio.h>
  #include <limits.h>
  #include <float.h>

  int main(void) {
      printf("INT_MIN = %d\n", INT_MIN);
      printf("INT_MAX = %d\n", INT_MAX);

      printf("LONG_MIN = %ld\n", LONG_MIN);
      printf("LONG_MAX = %ld\n", LONG_MAX);

      printf("SHRT_MIN = %d\n", SHRT_MIN);
      printf("SHRT_MAX = %d\n", SHRT_MAX);

      printf("CHAR_MIN = %d\n", CHAR_MIN);
      printf("CHAR_MAX = %d\n", CHAR_MAX);

      printf("FLT_MIN = %e\n", FLT_MIN);
      printf("FLT_MAX = %e\n", FLT_MAX);

      printf("DBL_MIN = %e\n", DBL_MIN);
      printf("DBL_MAX = %e\n", DBL_MAX);

      return 0;
  }
  ```

  Compile and run (example with `gcc`):

  ```powershell
  gcc -o check_limits check_limits.c
  ./check_limits
  ```

  Sample output from my system:

  ```
  INT_MIN = -2147483648
  INT_MAX = 2147483647
  LONG_MIN = -2147483648
  LONG_MAX = 2147483647
  SHRT_MIN = -32768
  SHRT_MAX = 32767
  CHAR_MIN = -128
  CHAR_MAX = 127
  FLT_MIN = 1.175494e-38
  FLT_MAX = 3.402823e+38
  DBL_MIN = 2.225074e-308
  DBL_MAX = 1.797693e+308
  ```

check data_types_advanced to know more...
