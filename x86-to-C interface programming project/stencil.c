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

void stencil_1d(int n, double* X, double* Y) {
    for (int i = 3; i < n; ++i) {
        Y[i - 3] = X[i - 3] + X[i - 2] + X[i - 1] + X[i] + X[i + 1] + X[i + 2] + X[i + 3];
    }
}

void display_first_ten(const char* name, int n, double* vector) {
    printf("First ten elements of vector %s: ", name);
    for (int i = 0; i < n && i < 10; ++i) {
        printf("%.2f ", vector[i]);
    }
    printf("\n");
}

void runStencilAndDisplay(int n) {
    double* X, * Y;

    X = (double*)malloc(n * sizeof(double));
    if (X == NULL) {
        fprintf(stderr, "Memory allocation for X failed.\n");
        exit(1);
    }

    Y = (double*)malloc((n - 3) * sizeof(double));
    if (Y == NULL) {
        fprintf(stderr, "Memory allocation for Y failed.\n");
        free(X);
        exit(1);
    }

    for (int i = 0; i < n; ++i) {
        X[i] = (double)i + 1;
    }

    display_first_ten("X", n, X);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    stencil_1d(n, X, Y);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for n=%d (seconds): %f\n", n, cpu_time_used);

    display_first_ten("Y", n - 3, Y);

    free(X);
    free(Y);
}

int main() {
    // Sizes to run
    int sizes[] = { 1 << 20, 1 << 24, 1 << 29 };
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        printf("Running for size 2^%d (%d elements):\n", 20 + i * 4, sizes[i]);
        runStencilAndDisplay(sizes[i]);
        printf("\n");
    }

    return 0;
}
