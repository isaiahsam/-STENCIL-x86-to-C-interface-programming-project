#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define FIRST_TEN 10

void compute_stencil(int length, double* inputArray, double* outputArray) {
    for (int index = 3; index < length - 3; index++) {
        outputArray[index] = inputArray[index - 3] + inputArray[index - 2] + inputArray[index - 1] + inputArray[index] + inputArray[index + 1] + inputArray[index + 2] + inputArray[index + 3];
    }
}

extern void asm1DStencil(int length, double* inputArray, double* outputArray);

double calculate_duration(clock_t startTime, clock_t endTime) {
    return ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
}

int main() {
    int dataSizes[] = { 1 << 20, 1 << 24, 1 << 28 }; // {2^20, 2^24, 2^28}
    int totalSizes = sizeof(dataSizes) / sizeof(dataSizes[0]);
    int exponentSizes[] = { 20, 24, 28 };
    double* inputData = (double*)malloc(dataSizes[totalSizes - 1] * sizeof(double));
    if (!inputData) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    for (int counter = 0; counter < dataSizes[totalSizes - 1]; counter++) {
        inputData[counter] = counter + 1;
    }

    printf("\n===== Initial Values in inputData =====\n");
    for (int counter = 0; counter < FIRST_TEN; counter++) {
        printf(" inputData[%d] = %.2lf\n", counter, inputData[counter]);
    }

    printf("\n=============== Benchmarking Stencil Computations ===============\n");

    for (int idx = 0; idx < totalSizes; idx++) {
        int currentSize = dataSizes[idx];
        double* resultArrayC = (double*)malloc(currentSize * sizeof(double));
        double* resultArrayASM = (double*)malloc(currentSize * sizeof(double));
        if (!resultArrayC || !resultArrayASM) {
            fprintf(stderr, "Failed to allocate memory for result arrays\n");
            free(resultArrayC);
            free(resultArrayASM);
            continue; // Skip this iteration
        }

        printf("\n--> Analyzing Performance for Array Size 2^%d <--\n", exponentSizes[idx]);

        // C Version
        clock_t startComputeC = clock();
        compute_stencil(currentSize, inputData, resultArrayC);
        clock_t endComputeC = clock();
        double computationTimeC = calculate_duration(startComputeC, endComputeC);

        // Assembly Version
        clock_t startComputeASM = clock();
        asm1DStencil(currentSize, inputData, resultArrayASM);
        clock_t endComputeASM = clock();
        double computationTimeASM = calculate_duration(startComputeASM, endComputeASM);

        // Print C Function Output
        printf("\n--- First Ten Calculated Values in resultArray (C Function) ---\n");
        for (int counter = 3; counter < FIRST_TEN + 3 && counter < currentSize - 3; counter++) {
            printf(" resultArrayC[%d] = %.2lf\n", counter, resultArrayC[counter]);
        }
        printf("\nComputation Time (C Function) for Array Size %d: %lf seconds\n", currentSize, computationTimeC);

        // Print Assembly Function Output
        printf("\n--- First Ten Calculated Values in resultArray (Assembly Function) ---\n");
        for (int counter = 3; counter < FIRST_TEN + 3 && counter < currentSize - 3; counter++) {
            printf(" resultArrayASM[%d] = %.2lf\n", counter, resultArrayASM[counter]);
        }
        printf("\nComputation Time (Assembly Function) for Array Size %d: %lf seconds\n", currentSize, computationTimeASM);
        printf("\n=================================================================\n");

        free(resultArrayC);
        free(resultArrayASM);
    }

    free(inputData);

    return 0;
}
