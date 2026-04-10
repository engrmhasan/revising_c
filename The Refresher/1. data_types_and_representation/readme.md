how many bytes each data type uses in memory.

* **sizeof(int) = 4**
  An `int` takes 4 bytes of memory. It is used to store whole numbers (e.g., -10, 0, 25).

* **sizeof(long) = 4**
  A `long` takes 4 bytes on this system. It stores larger whole numbers (size may vary by system).

* **sizeof(short) = 2**
  A `short` takes 2 bytes of memory. It stores smaller-range whole numbers.

* **sizeof(float) = 4**
  A `float` takes 4 bytes. It stores decimal (fractional) numbers with single precision.

* **sizeof(double) = 8**
  A `double` takes 8 bytes. It stores decimal numbers with higher precision than `float`.

* **sizeof(char) = 1**
  A `char` takes 1 byte. It stores a single character (like 'A', 'b', or '7').



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

---

### Advanced Exploration of Data Types

#### 1. Signed vs Unsigned Integers
- **Signed integers** can represent both negative and positive numbers.
  - Example: A signed 8-bit integer ranges from **-128 to 127**.
- **Unsigned integers** can only represent positive numbers.
  - Example: An unsigned 8-bit integer ranges from **0 to 255**.
- **Overflow behavior**:
  - Unsigned integers wrap around to 0 when exceeding their maximum value.
  - Signed integers wrap around to their minimum value when exceeding their maximum value.

#### 2. Floating Point Precision
- Floating-point numbers (e.g., `float` and `double`) cannot store most decimal numbers exactly.
  - Example: `0.1 + 0.2` does not equal exactly `0.3` due to approximation.
- **Precision differences**:
  - `float` has about **6–7 decimal digits** of precision.
  - `double` has about **15–16 decimal digits** of precision.
- **Best practices**:
  - Avoid checking if two floating-point numbers are exactly equal.
  - Instead, check if their difference is within a very small range.

#### 3. `size_t` and Fixed-Width Types
- **Fixed-width types** (from `stdint.h`) provide exact sizes:
  - `uint8_t`: Unsigned, 8 bits (0 to 255).
  - `int32_t`: Signed, 32 bits (-2,147,483,648 to 2,147,483,647).
  - `uint64_t`: Unsigned, 64 bits (0 to 18,446,744,073,709,551,615).
- **`size_t`**:
  - Used for sizes and counts, such as the result of `sizeof()`.
  - Always the right size for the platform.
- Example:
  - `sizeof("hello")` returns **6 bytes**, including the null terminator `\0`.



### Format Specifiers

| Specifier | Full Name | Data Type | Use Case | Example |
| --- | --- | --- | --- | --- |
| **`%d`** or **`%i`** | Signed Decimal | `int` | Standard whole numbers (positive/negative). | `-42`, `10` |
| **`%ld`** | Long Decimal | `long` | Large signed integers (32 or 64-bit). | `2147483647` |
| **`%lld`** | Long Long Dec | `long long` | Extremely large signed integers (64-bit). | `9e18...` |
| **`%u`** | Unsigned Decimal | `unsigned int` | Positive-only whole numbers. | `5000` |
| **`%f`** | Floating Point | `float` | Numbers with decimals (standard precision). | `3.1415` |
| **`%lf`** | Long Float | `double` | High-precision decimals (most common for math). | `2.7182818` |
| **`%e`** | Scientific | `float` / `double` | Exponential notation. | `1.23e+04` |
| **`%g`** | General | `float` / `double` | Uses `%f` or `%e`, whichever is shorter. | `123.4` |
| **`%%`** | Literal Percent | N/A | Prints a physical `%` symbol. | `100%` |
| **`%c`** | Character | `char` | A single letter, digit, or symbol. | `'A'`, `'!'` |
| **`%s`** | String | `char*` (Array) | A sequence of text/words. | `"Hello"` |
| **`%p`** | Pointer | `void*` | A memory address (shown in Hex). | `0x7ffc...` |
| **`%zu`** | Size Unsigned | `size_t` | **Array indexes** and `sizeof` results. | `1024` |
| **`%hd`** | Half Decimal | `short` | Small signed integers (16-bit). | `-32768` |
| **`%hu`** | Half Unsigned | `unsigned short` | Small positive integers (16-bit). | `65535` |
| **`%x`** | Hexadecimal | `int` / `uint32_t` | Base-16 (lowercase); used for memory/bits. | `0x2f` |
| **`%X`** | Hexadecimal | `int` / `uint32_t` | Base-16 (UPPERCASE). | `0x2F` |
| **`%o`** | Octal | `int` | Base-8 (rarely used today). | `0755` |

---

#### Special Engineering Types (`<inttypes.h>`)

When we use types like `uint32_t` or `uint64_t`, the standard specifiers (`%d`, `%u`) can sometimes be slightly wrong depending on the computer's architecture. To be **100% professional**, engineers use "Macros" for these types:

| Data Type | Correct Specifier Macro | What it actually looks like |
| --- | --- | --- |
| **`int32_t`** | `PRId32` | `printf("Temp: %" PRId32 "\n", my_var);` |
| **`uint32_t`** | `PRIu32` | `printf("Count: %" PRIu32 "\n", my_var);` |
| **`uint64_t`** | `PRIu64` | `printf("Total: %" PRIu64 "\n", my_var);` |

*check format_specifiers.c for example*
---

#### Pro-Tip: The "Width and Precision" Trick

We can add numbers between the `%` and the letter to format the layout. This is common in loops to keep columns aligned.

* **`%5d`**: Reserves 5 spaces for the number (right-aligned).
* **`%05d`**: Reserves 5 spaces and pads empty ones with **zeros** (e.g., `00042`).
* **`%.2f`**: Rounds a decimal to exactly **2 places** (e.g., `3.14`).

For more details, explore each c files.
