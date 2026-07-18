# Assignment 2: Arbitrary Precision BigRational & Template Specialization

## Overview
This assignment extends the arbitrary-precision capabilities developed in the previous practical work by introducing C++ templates to handle bases in the range $2 \le \text{Base} \le 16$. The library implements signed arbitrary precision integers (`BigInteger<Base>`), unsigned integers (`BigUnsigned<Base>`), and fraction arithmetic via `BigRational<Base>`. 

A critical component of this assignment is the template specialization `BigUnsigned<2>`, which replaces digit vectors with an optimized boolean bit vector (`std::vector<bool>`) to handle binary mathematics natively.

## Key Features Implemented

*   **Template Architecture**: All numeric containers support variable compilation bases via `template <unsigned char Base>`.
*   **Sign Handling**: `BigInteger` wraps a `BigUnsigned` value and couples it with a distinct boolean flag for representing negative values.
*   **Fraction Simplification**: `BigRational` automates fraction reduction to its irreducible form utilizing an arbitrary-precision recursive Greatest Common Divisor (GCD) algorithm on the numerators and denominators.
*   **Base Specialization (`Base = 2`)**: Specialized implementation using a dense layout of booleans (`std::vector<bool>`) and raw bitwise simulation (`^`, `&&`, `||`) for high performance.
*   **Decimal Base Conversion**: Every class provides a `.convertirDecimal()` interface to translate values back to standard Base 10 (`BigRational<10>`) for uniform formatting and evaluation.

## Compilation & Automation (Makefile)

The workspace uses an automated dependency graph through a `Makefile`.

### Build Commands

*   **Compile the program:**
    ```bash
    make
    ```
    *This generates the executable binary named `mcd` in your root directory.*

*   **Clean build objects:**
    ```bash
    make clean
    ```

## How to Run & Test

The execution structure requires passing an input configuration file (which specifies the evaluation base, $N_1$, and $N_2$) and the destination location for results output.

### Command Format
```bash
./mcd <input_file> <output_file>
```

### Examples with Included Data
* Testing Base 10 fractions:
```bash
./mcd inputbase10.txt output.txt
```

* Testing Base 16 fractions:
```bash
./mcd inputbase16.txt output.txt
```

* Testing Base 8 fractions:
```bash
./mcd inputbase8.txt output.txt
```

### Author
* Adrián Martín Castellano
* Email: alu0101547619@ull.edu.es
* Universidad de La Laguna (ULL)