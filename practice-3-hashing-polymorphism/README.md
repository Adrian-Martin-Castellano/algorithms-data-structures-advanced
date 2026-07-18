# Open and Closed Hash Table Implementation in C++

**Course:** Advanced Algorithms and Data Structures (2nd Year)  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** March 2025  

## Overview

This project implements a customizable and highly polymorphic **Hash Table** data structure capable of operating under both **Open Hashing** (separate chaining using dynamic structures) and **Closed Hashing** (open addressing using bounded blocks/buckets). 

The primary domain entity used as keys for indexing and searching within the table is a National Identity Number (**NIF**). The architecture relies extensively on C++ Class Templates and Object-Oriented Design (OOD) to isolate dispersion policies, exploration strategies, and underlying memory storage layouts.

## Architecture & Design Patterns

The system is decomposed into highly decoupled components using polymorphic interfaces:

1. **`Sequence` Base Template Interface:** Represents a generic container block.
   * `DynamicSequence`: Unbounded vector wrapper tailored for Open Hashing.
   * `StaticSequence`: Bounded static-allocated array tailored for Closed Hashing slots.
2. **`DispersionFunction` Base Interface:** Pure virtual functor mapping a key to its base index.
   * `DispersionFunctionModule`: Standard division remainder operation (`key % size`).
   * `DispersionFunctionSum`: Modulo reduction of individual digits extraction sum.
   * `DispersionFunctionPseudorandom`: Deterministic pseudo-random seed generator.
3. **`ExplorationFunction` Base Interface:** Resolves open addressing collisions sequentially.
   * `ExplorationFunctionLineal`: Linear probe mapping.
   * `ExplorationFunctionCuadratic`: Quadratic step adjustments.
   * `ExplorationFunctionRedispersion`: Secondary pseudo-random re-hashing strategy.
   * `ExplorationFunctionDobleDispersion`: Double hashing collision handling.

## Getting Started

### Prerequisites
A modern C++ compiler supporting at least **C++17** or above (e.g., `g++` or `clang++`).

### Compilation
The program includes a automated build configuration using a `Makefile`. Run the following command inside the root folder:

```bash
make
```

To clean intermediate object binaries and build files, execute:

```bash
make clean
```

## Usage & CLI Arguments

The program runs via a command-line interface (CLI) that configures the hash table's structural parameters and policies at startup.

### Command Parameters

| Parameter | Required For | Description | Possible Values |
| :--- | :--- | :--- | :--- |
| `-ts <size>` | **All** | Hash table dimensions (total number of indices/slots). | `Positive Integer` |
| `-hash <type>` | **All** | Chosen collision architecture technique. | `open`, `close` |
| `-fd <policy>`| **All** | Main base dispersion algorithm code. | `mod`, `sum`, `random` |
| `-bs <size>` | `close` only | Storage boundary size limit per block bucket. | `Positive Integer` |
| `-fe <probe>` | `close` only | Hashing collision exploration function. | `lineal`, `cuadratica`, `doble`, `redispersion` |

### Execution Examples

#### 1. Open Hashing Setup (Separate Chaining)
Using a size of 11, with the digit-sum dispersion method:

```bash
./main-hash -ts 11 -hash open -fd sum
```

#### 2. Closed Hashing Setup (Open Addressing)
Using a size of 101, bucket limit size of 3, modulus dispersion, and quadratic collision resolution:

```bash
./main-hash -ts 101 -hash close -fd mod -bs 3 -fe cuadratica
```

## Interactive Console Menu

## 📑 Interactive Console Menu

Once initialized, the program launches an internal runtime loop shell supporting the following actions:

* **1 (Insert NIF):** Asks the user for an 8-digit identification number to construct a new `Nif` object and inserts it into the table.
* **2 (Search NIF):** Searches for an existing numerical identifier checking memory layouts according to initialization strategies.
* **3 (Exit):** Cleanly triggers class destructors, frees dynamically assigned heap blocks, and ends the process safely.