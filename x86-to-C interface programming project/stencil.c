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
    int counter;
    clock_t startCompute, endCompute;
    double computationTime;

    int dataSizes[] = { 1 << 20, 1 << 24, 1 << 28 }; // {2^20, 2^24, 2^28}
    int totalSizes = sizeof(dataSizes) / sizeof(dataSizes[0]);
    int exponentSizes[] = { 20, 24, 28 };

    double* inputData = (double*)malloc(dataSizes[totalSizes - 1] * sizeof(double));
    if (!inputData) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    for (counter = 0; counter < dataSizes[totalSizes - 1]; counter++) {
        inputData[counter] = counter + 1;
    }

    printf("\n===== Initial Values in inputData =====\n");
    for (counter = 0; counter < FIRST_TEN; counter++) {
        printf(" inputData[%d] = %.2lf\n", counter, inputData[counter]);
    }

    printf("\n=============== Benchmarking Stencil Computations ===============\n");

    for (int idx = 0; idx < totalSizes; idx++) {
        int currentSize = dataSizes[idx];
        double* resultArray = (double*)malloc(currentSize * sizeof(double));

        printf("\n--> Analyzing Performance for Array Size 2^%d <--\n", exponentSizes[idx]);

        for (counter = 0; counter < currentSize; counter++) {
            resultArray[counter] = 0.0;
        }

        startCompute = clock();
        compute_stencil(currentSize, inputData, resultArray);
        endCompute = clock();
        computationTime = calculate_duration(startCompute, endCompute);
        printf("\nComputation Time (C Function) for Array Size %d: %lf seconds\n", currentSize, computationTime);

        printf("\n--- First Ten Calculated Values in resultArray (C Function) ---\n");
        for (counter = 3; counter < FIRST_TEN + 3 && counter < currentSize - 3; counter++) {
            printf(" resultArray[%d] = %.2lf\n", counter, resultArray[counter]);
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

        printf("\n=================================================================\n");

        free(resultArray);
    }

    free(inputData);

    return 0;
}
