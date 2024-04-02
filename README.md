# 1D Stencil Operation in C and x86-64 Assembly: Performance Analysis

Authors:
CUALES, Bianca Mari
PASCUAL, Isaiah Sam

This README details the comparative performance analysis of a 1D stencil operation implemented in both C and x86-64 Assembly. The stencil operation updates each element in an output array based on itself and its neighbors in the input array.

## Comparative Execution Time and Performance Analysis

The execution times for the stencil operation in both C and Assembly across different modes and data sizes are detailed below. The analysis focuses on the execution time differences and the performance efficiency of each kernel.

### Debug Mode

- For Array Size `2^20`:
  - C Function: 0.005000 seconds
  - Assembly Function: 0.002000 seconds

- For Array Size `2^24`:
  - C Function: 0.092000 seconds
  - Assembly Function: 0.032000 seconds

- For Array Size `2^28`:
  - C Function: 1.749000 seconds
  - Assembly Function: 0.619000 seconds

### Release Mode

*Similar analysis with execution times in Release Mode goes here...*

#### Performance Analysis

The Assembly implementation showcases superior performance over the C implementation across all tested array sizes. This is particularly noticeable in larger data sets (e.g., `2^28`), where the execution time for Assembly is significantly less than that for C. This suggests that low-level optimizations in Assembly can lead to substantial performance improvements, especially in compute-intensive applications like the stencil operation.

## Program Output with Correctness Check

### C Implementation

- **Screenshot Placeholder for C Output**

  ![C Program Output](link-to-screenshot-c.png)

### x86-64 Assembly Implementation

- **Screenshot Placeholder for Assembly Output**

  ![Initial Values](link-to-screenshot.png)

### Observations

Both implementations produce identical output, confirming the correctness of the stencil computation across different programming languages and optimization levels. The detailed outputs, alongside the computation times, further validate the efficiency and accuracy of the implemented stencil logic.

## Conclusion

The analysis underscores the effectiveness of Assembly language for performance-critical operations, offering a deeper insight into how low-level programming can be leveraged to optimize computational tasks. Despite the complexity of Assembly language, its use in applications requiring intensive data processing can significantly enhance performance, making it a valuable skill set in system programming and performance optimization.
