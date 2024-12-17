# math
Miscellaneous mathematical helper classes and functions

## Status
<!-- [![GitHub Super-Linter](https://github.com/Loic-Corenthy/math/workflows/CMake/badge.svg)](https://github.com/marketplace/actions/super-linter)
 -->
[![CMake](https://github.com/Loic-Corenthy/math/actions/workflows/cmake.yml/badge.svg)](https://github.com/Loic-Corenthy/math/actions/workflows/cmake.yml)

## Libraries
This repository contains multiple independent libraries:

* **algebra**
    - Vector
    - Matrix
    - Quaternion

Templated classes to accommodate with different types and sizes.

* **combinatorics**
    - Permutation generator function


* **large**

| **Benchmark Name**               | **Samples** | **Mean**  | **Std Dev** |
|----------------------------------|-------------|-----------|-------------|
| **Simd multiplication**          | 100         | 3.36515 s | 44.8839 ms  |
| **Multithreading multiplication**| 100         | 2.88052 s | 67.1787 ms  |

Simple benchmark measuring the time to multiply two matrices A and B (of float numbers) with the following dimensions:

- A = 1000 rows x 1200 cols
- B = 1200 rows x 1100 cols

The test was performed on a Intel(R) Core(TM) i9-9820X CPU.

(See `./large/tests/BenchMarkLargeMatrix.cpp` for more details)

