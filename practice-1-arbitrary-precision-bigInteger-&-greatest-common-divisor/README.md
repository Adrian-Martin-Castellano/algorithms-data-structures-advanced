# Assignment 1: Arbitrary Precision BigInteger & Greatest Common Divisor (GCD)

## Overview
This assignment implements a custom high-performance library for arbitrary-precision unsigned integers (`BigUnsigned`) and signed integers (`BigInteger`) in modern C++. It includes a recursive implementation of the Euclidean algorithm to calculate the Greatest Common Divisor (GCD) of extraordinarily large values without suffering from integer overflow.

## Performance Optimizations Implemented

*   **Schoolbook Multiplication ($O(N \cdot M)$)**: Replaced the slow, nested additive loop system with an optimized column-carry digit multiplication.
*   **Fast Division ($O(\text{bits}^2)$)**: Replaced successive subtractor loops with a binary Shift-and-Subtract algorithm, allowing division of numbers with hundreds of digits to run instantaneously.
*   **Undefined Behavior Fixes**: Corrected unsafe `reinterpret_cast` usage over transient string buffers by employing safe explicit string parsing.

## Compilation & Automation (Makefile)

The project includes a `Makefile` to compile, build, and clean the workspace easily.

### Compilation Flags Used Internally
The default build targets use the following structure:
*   `g++ -std=c++23` (Modern C++ standard)
*   Modular compilation rules (`%.o: %.cc`)

### Build Commands

*   **Compile the program:**
    ```bash
    make
    ```
    *This generates the executable named `mcd` in the root of the directory.*

*   **Clean object files and the executable:**
    ```bash
    make clean
    ```

## How to Run & Test

You can run the program interactively or redirect the inputs directly from the provided `ejemplos.txt` file.

### Interactive Execution
```bash
./mcd
```
Then input two large numbers sequentially when prompted.

### Automated Execution with Examples
```bash
./mcd < ejemplos.txt
```

### Author
* Adrián Martín Castellano
* Email: alu0101547619@ull.edu.es
* Universidad de La Laguna (ULL)