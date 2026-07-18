# Advanced Algorithms and Data Structures (AEDA)

**BSc in Computer Engineering** (2nd Year)  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Academic Year:** 2024/2025  


## Course Overview

This repository contains the laboratory assignments developed for the **AEDA** course. All projects are written in **C++** applying strict Object-Oriented Programming (OOP) principles, polymorphism, and generic programming via Class Templates.

The core objective across these assignments is the design, implementation, and empirical evaluation (both time and space complexity analysis) of complex data structures and advanced search, hashing, and sorting algorithms.


## Repository Structure

The repository is structured into 4 independent standalone projects:

### [Practice 1: Towers of Hanoi & Complexity Analysis](./practice-1-arbitrary-precision-bigInteger-&-greatest-common-divisor/)
* **Objective:** Practical study of recursion mechanics and algorithmic complexity profiling using the classic Towers of Hanoi puzzle.
* **Key Components:** Experimental time-performance mapping ($O(2^n)$) and detailed execution trace logs tracking disk movements between pegs.

### [Practice 2: Linear Data Structures & AVL Simulator](./practice-2-precision-bigRational-&-template-specialization/)
* **Objective:** Implementation of foundational dynamic container wrappers (lists, queues, stacks) and behavioral modeling of self-balancing AVL binary search trees.
* **Key Components:** Abstract sequence definitions and polymorphic interfaces for structured sequential and hierarchical data storage.

### [Practice 3: Hashing Functions & Open/Closed Hash Tables](./practice-3-hashing-polymorphism/)
* **Objective:** Construction of a high-speed runtime search and storage engine using customizable CLI-driven hash tables.
* **Key Components:**
  * **Open Hashing:** Chaining resolution layout driven by dynamic containers (`DynamicSequence`).
  * **Closed Hashing:** Open addressing layout bound to rigid memory buckets (`StaticSequence`) supporting linear, quadratic, double-hashing, and deterministic pseudo-random re-hashing collision strategies.
  * **Domain Entity:** National Identity Numbers (`Nif`) used as primary lookup table database keys.

### [Practice 4: Polymorphic Sorting Algorithms Framework](./practice-4-polymorphic-sorting-algorithms/)
* **Objective:** Development of an empirical auditing framework to execute, benchmark, and trace the internal state machine flow of classic sorting routines.
* **Key Components:**
  * **Quadratic Algorithms:** Straight Insertion Sort ($O(n^2)$) and Bidirectional Cocktail Shaker Sort (`Sacudida`).
  * **Logarithmic Algorithms:** QuickSort (central pivot partitioning) and HeapSort (maximum binary heap-tree extraction utilizing down-heap sift functions).
  * **Advanced Strategies:** ShellSort adaptive diminishing increments governed by a custom gap contraction factor ($\alpha$).
  * **Initialization Modes:** Supports manual keyboard input typing, time-synchronized pseudo-random generation, and bulk dataset file imports.


## Getting Started & Compilation

### Prerequisites
A modern C++ compiler supporting at least the **C++17** standard or above (e.g., `g++` or `clang++`).

### Compiling Individual Practices
Each project directory contains an independent automated configuration `Makefile`. To build any particular lab, navigate into its source folder and execute:

```bash
make
```

To clean intermediate compiled binary objects and executable builds:

```bash
make clean
```