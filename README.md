# math
Miscellaneous mathematical helper classes and functions

## Status
<!-- [![GitHub Super-Linter](https://github.com/Loic-Corenthy/math/workflows/CMake/badge.svg)](https://github.com/marketplace/actions/super-linter)
 -->
[![CMake](https://github.com/Loic-Corenthy/math/actions/workflows/cmake.yml/badge.svg)](https://github.com/Loic-Corenthy/math/actions/workflows/cmake.yml)

## Libraries
This repository contains multiple independent libraries:

### algebra

- `Vector`
- `Matrix`
- `Quaternion`

Templated classes to accommodate with different types and sizes.

- `MultiplicationLarge`

3 functions to accelerate the multiplication of "large" matrices using multithreading and/or SIMD:

    - multiply_concurrently
    - multiply_simd
    - multiply_concurrently_simd

#### Benchmark
Simple benchmark measuring the time to multiply two matrices A and B (of float numbers) with the following dimensions:

- A = 1000 rows x 1000 cols
- B = 1000 rows x 1000 cols

| **Benchmark Name**               | **Samples** | **Mean**  | **Std Dev** |
|----------------------------------|-------------|-----------|-------------|
| **Simd**                         | 100         | 3.36515 s | 44.8839 ms  |
| **Multithreading**               | 100         | 2.88052 s | 67.1787 ms  |
| **Multithreading and simd**      | 100         | 2.88052 s | 67.1787 ms  |

Benchmark performed on a Intel(R) Core(TM) i9-9820X CPU.

(See `./large/tests/BenchMarkLargeMatrix.cpp` for more details)

### combinatorics

- Permutation generator function

