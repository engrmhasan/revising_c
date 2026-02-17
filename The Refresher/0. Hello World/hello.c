
/*
 hello.c

 Purpose:
 - Show the minimal structure of a C source file and a "Hello, World!" example.
 - Explain how C source -> compile -> run works and what you learn from running it.

*/

 #include <stdio.h>

int main(void) {
		/* Print a simple greeting to standard output */
		printf("Hello, World!\n");

		/* Return 0 to indicate success to the operating system */
		return 0;
}

/*
 File structure explained:
 - Preprocessor directives: `#include <...>` bring in declarations from headers.
 - (Optional) Global declarations and macros.
 - `main()` function: program entry point. Execution starts here.
 - Statements inside `main` perform program work (I/O, computation).
 - `return 0;` indicates successful program termination to the OS.

 How C builds and runs (conceptual):
 1. Preprocessing: `#include` and macros are expanded.
 2. Compilation: source (.c) -> object (.o) with machine code for each translation unit. Then goes through assembly and optimization steps.
 3. Linking: object files + libraries -> executable.
 4. Execution: OS loads executable and starts at `main()`.

 Compile & run (example commands):
 - With GCC (MSYS2 / MinGW-w64 / WSL):
	 gcc hello.c -o hello.exe
	 ./hello.exe


 What we gain by running this example:
 - Confirm toolchain works (compiler + linker).
 - See standard I/O (`printf`) in action.
 - Understand program entry and exit semantics.
 - Learn that compilers translate human-readable C into machine code.
*/


