/*
@authors:
        Cuales, Bianca Mari
        Pascual, Isaiah Sam
@section:
        S11

Write the kernel in (1) C program .  The kernel is to perform 1-D stencil of vector X place the result in vector Y.
Input: Scalar variable n (integer) contains the length of the vector;  Vectors X and Y are both double-precision float.
Process:  Y [i] = X[i-3] + X[i-2] + X[i-1] + X[i]
Example: X-> 1,2,3,4,5,6,7,8; output: Y-> 28, 35
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// Function to perform the 1-D stencil operation
void stencil_1d(int n, double* X, double* Y) {
    for (int i = 3; i < n; ++i) {
        Y[i - 3] = X[i - 3] + X[i - 2] + X[i - 1] + X[i] + X[i + 1] + X[i + 2] + X[i + 3];
    }
}

// Function to display the first ten elements of a vector
void display_first_ten(const char* name, int n, double* vector) {
    printf("First ten elements of vector %s: ", name);
    for (int i = 0; i < n && i < 10; ++i) {
        printf("%.2f ", vector[i]);
    }
    printf("\n");
}

extern void asmStencil();

int main() {
    int n = 1 << 20; // Example size lang but this is  2^20
    double* X, * Y;

    // Dynamically allocate memory for X and Y
    X = (double*)malloc(n * sizeof(double));
    Y = (double*)malloc((n - 3) * sizeof(double)); // Y will have n-3 elements based on the stencil operation

    // Initialize X with some values
    for (int i = 0; i < n; ++i) {
        X[i] = (double)i + 1;
    }

    // Display the first ten elements of X before the stencil operation
    display_first_ten("X", n, X);

    // just to time the kernel for recording purposes

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    // 1-D stencil operation
    stencil_1d(n, X, Y);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken (seconds): %f\n", cpu_time_used);

    // Display the first ten elements of Y after the stencil operation
    display_first_ten("Y", n - 3, Y);

    // Free allocated memory
    free(X);
    free(Y);

    return 0;
}
