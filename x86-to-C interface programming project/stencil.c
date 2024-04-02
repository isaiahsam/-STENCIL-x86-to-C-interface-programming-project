#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define N 10

void stencil_c(int n, double* X, double* Y) {
    for (int i = 3; i < n - 3; i++) {
        Y[i] = X[i - 3] + X[i - 2] + X[i - 1] + X[i] + X[i + 1] + X[i + 2] + X[i + 3];
    }
}

extern void asm1DStencil(int n, double* X, double* Y);

double get_execution_time(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    int i;
    clock_t start_c, end_c;
    double cpu_time_used_c;

    int lengths[] = { 1 << 20, 1 << 24, 1 << 28 }; // {2^20, 2^24, 2^27}
    int num_lengths = sizeof(lengths) / sizeof(lengths[0]);
    int sizes[] = { 20, 24, 28 };

    // Allocate memory for the largest size required
    double* X = (double*)malloc(lengths[num_lengths - 1] * sizeof(double));
    if (!X) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize vector X with monotonically increasing values
    for (i = 0; i < lengths[num_lengths - 1]; i++) {
        X[i] = i + 1; // Monotonically increasing values
    }

    // Display the first ten values of X
    printf("\nFirst ten values of X:");
    for (i = 0; i < 10; i++) {
        printf(" %.2lf", X[i]);
    }

    printf("\n\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    for (int j = 0; j < num_lengths; j++) {
        int n = lengths[j];
        double* Y = (double*)malloc(n * sizeof(double));

        printf("\nSize 2^%d \n", sizes[j]);

        for (i = 0; i < n; i++) {
            Y[i] = 0.0;
        }

        start_c = clock();
        stencil_c(n, X, Y);
        end_c = clock();
        cpu_time_used_c = get_execution_time(start_c, end_c);
        printf("\nTime taken by C implementation for vector length %d: %lf seconds", n, cpu_time_used_c);

        printf("\nFirst ten calculated values of vector Y (C implementation):\n");
        for (i = 3; i < N + 3 && i < n - 3; i++) { // Adjusted to show calculated values
            printf("%.2lf ", Y[i]);
        }

        // Reset Y for assembly test
        for (i = 0; i < n; i++) {
            Y[i] = 0.0;
        }

        // Call to asm1DStencil would go here, using the same pattern as above for timing and displaying values
        // Since we can't actually execute assembly, this part is commented out
        /*
        start_c = clock();
        asm1DStencil(n, X, Y);
        end_c = clock();
        cpu_time_used_c = get_execution_time(start_c, end_c);
        printf("\nTime taken by assembly implementation for vector length %d: %lf seconds", n, cpu_time_used_c);

        printf("\nFirst ten calculated values of vector Y (assembly implementation):\n");
        for (i = 3; i < N + 3 && i < n - 3; i++) {
            printf("%.2lf ", Y[i]);
        }
        */

        printf("\n\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

        free(Y);
    }

    free(X);

    return 0;
}
