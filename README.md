# 1D Stencil Operation in C and x86-64 Assembly: Performance Analysis

Authors:
CUALES, Bianca Mari
PASCUAL, Isaiah Sam

This document presents a comparative analysis of the performance of a 1D Stencil operation when implemented in C and x86-64 Assembly languages. The stencil operation is defined as follows for any given input array `X` and output array `Y`:

Y[i] = X[i-3] + X[i-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3]


Where `i` is the index of the current element in the arrays `X` and `Y`.

## Initial Values for Benchmarking

The benchmarking process started with the following initial values in the input data array:

inputData[0] = 1.00
inputData[1] = 2.00
...
inputData[9] = 10.00


## Benchmarking Stencil Computations

Performance of the stencil computations was analyzed for array sizes \(2^{20}\), \(2^{24}\), and \(2^{28}\). For each size, the first ten calculated values in the result array were recorded for both C and Assembly functions, alongside their computation times.

### Performance for Array Size \(2^{20}\) (1,048,576 Elements)

- **C Function Results**:
  - Calculated values in `resultArrayC`: 28.00 to 91.00 (indices 3 to 12).
  - Computation time: 0.005000 seconds.
- **Assembly Function Results**:
  - Calculated values in `resultArrayASM`: Identical to C function.
  - Computation time: 0.002000 seconds.

### Performance for Array Size \(2^{24}\) (16,777,216 Elements)

- **C Function**: Computation time increased to 0.078000 seconds.
- **Assembly Function**: Computation time was 0.028000 seconds.

### Performance for Array Size \(2^{28}\) (268,435,456 Elements)

- **C Function**: Computation time significantly increased to 1.427000 seconds.
- **Assembly Function**: Computation time was 0.559000 seconds.

## Analysis of Results

The benchmarking exercise highlights several key insights:

- Both C and Assembly implementations produced identical results across all tests, ensuring functional consistency.
- Assembly implementations consistently offered better performance compared to C, especially as the size of the data set increased.
- The efficiency and scalability of Assembly code were particularly notable for large data sets, underscoring its potential advantages in performance-critical applications.

This analysis demonstrates the effectiveness of low-level programming for optimizing computational tasks, particularly those involving large-scale data processing.

