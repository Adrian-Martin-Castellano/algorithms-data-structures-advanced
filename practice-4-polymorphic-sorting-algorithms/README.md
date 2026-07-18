# Polymorphic Sorting Algorithms Implementation in C++

**Course:** Advanced Algorithms and Data Structures (2nd Year)  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** April 2025  

## Overview

This project implements a polymorphic benchmarking framework to analyze, execute, and trace various classic sorting algorithms. The architecture abstracts the strategies via a common base interface, allowing the sorting of sequences of elements (specifically National Identity Numbers, or **NIFs**) using different initialization modes and complexity scales.

The framework supports multiple algorithmic families, ranging from quadratic insertion strategies to advanced divide-and-conquer and logarithmic heap structures.

## Architecture & Sorting Methods

The software design leverages standard Object-Oriented Design (OOD) practices with C++ Class Templates to guarantee clean decoupling between the data storage layout and the sorting process execution:

1. **`Sequence` Architecture:**
   * `Sequence`: A pure virtual template interface defining safe element access operators.
   * `StaticSequence`: A fixed-size bounded sequential array wrapper handles explicit memory boundaries with out-of-bounds safety guards.

2. **`SortMethod` Polymorphic Hierarchy:**
   * `Insertion`: The classic straight insertion mechanism ($O(n^2)$ worst-case).
   * `Sacudida` (ShakerSort): Bidirectional cocktail shaker sort optimization over traditional bubble strategies.
   * `QuickSort`: Divide-and-conquer partitioning using a calculated central element pivot.
   * `HeapSort`: Maximum binary heap-tree sort extraction strategy utilizing a deterministic down-heap execution function (`Baja`).
   * `ShellSort`: Diminishing increment gap sorting controlled via an adjustable contraction parameter factor ($\alpha$).

## Getting Started

### Prerequisites
A modern C++ compiler supporting at least **C++17** or above (e.g., `g++` or `clang++`).

### Compilation
Build the main runner executable by invoking the configuration `Makefile` located within the root directory:

```bash
make
```

To clean up object files and temporary build artifacts:

```bash
make clean
```

## Usage & CLI Arguments

The program runs via a command-line interface (CLI) that requires parameters to customize the sequence sizing, structural values, data initialization, and visualization traces.

### Command Parameters

| Parameter | Required | Description | Possible Values |
| :--- | :--- | :--- | :--- |
| `-size <num>` | **Yes** | Total number of elements/NIFs inside the sequence. | `Positive Integer` |
| `-ord <method>` | **Yes** | Sorting algorithm strategy selection. | `insertion`, `shakesort`, `quicksort`, `heapsort`, `shellsort` |
| `-init <mode>` | **Yes** | Data source strategy to populate the sequence. | `manual`, `random`, `file` |
| `<filename>` | **Conditional** | Required immediate string value *only* if `-init file` is specified. | `Path to a valid text file` |
| `-trace <y/n>` | No | Activates execution inspection step-by-step state logs. | `y`, `n` (Default: `n`) |
| `-alfa <val>` | No | Fractional coefficient grid step multiplier for `shellsort`. | `Float value between 0.0 and 1.0` (Default: `0.5`) |

---

### Execution Examples

#### 1. Traceable Quadratic Sorting
Sorting a sequence of 10 elements using **Insertion Sort** with interactive console typing (`manual`) and real-time execution trace feedback enabled:

```bash
./main-sort -size 10 -ord insertion -init manual -trace y
```


#### 2. Mass Benchmark ShellSort
Sorting 5000 pseudo-randomly generated Nif records using ShellSort with custom gap contraction factor ($\alpha = 0.45$):

```bash
./main-sort -size 5000 -ord shellsort -init random -alfa 0.45
```

#### 3. Logarithmic File Read Sorting
Sorting keys imported from an external text dataset via QuickSort without printing intermediate debug state logs:

```bash
./main-sort -size 150 -ord quicksort -init file data.txt -trace n
```