#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

// Declaration of the assembly function for the 1D stencil operation.
extern void asm1DStencil(int n, double* X, double* Y);

// Gets the high-resolution performance counter value.
LARGE_INTEGER getCurrentTime() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return time;
}

// Calculates execution time in seconds using high-resolution timestamps.
double calculateExecutionTimeInSeconds(LARGE_INTEGER startTime, LARGE_INTEGER endTime) {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    return (double)(endTime.QuadPart - startTime.QuadPart) / (double)frequency.QuadPart;
}

// The C implementation of the 1D stencil operation.
void computeStencilC(int arraySize, double* inputArray, double* resultArray) {
    printf("Result of C implementation: ");
    int displayLimit = arraySize < 10 ? arraySize : 10; // Limiting the display to the first 10 elements.

    for (int i = 0; i < arraySize; ++i) {
        resultArray[i] = 0.0;
        for (int offset = 0; offset < 7; ++offset) { // Summing 7 consecutive elements.
            resultArray[i] += inputArray[i + offset];
        }
    }

    for (int i = 0; i < displayLimit; ++i) {
        printf("%.4f%s", resultArray[i], (i < displayLimit - 1) ? ", " : "\n");
    }
}

// Generates an array filled with random double precision numbers.
double* generateRandomArray(int size, unsigned int seed) {
    double* array = (double*)malloc(size * sizeof(double));
    if (!array) {
        fprintf(stderr, "Failed to allocate memory for the array.\n");
        exit(EXIT_FAILURE);
    }

    srand(seed); // Initialize random number generator.

    for (int i = 0; i < size; ++i) {
        array[i] = (rand() % 150) - 75 + ((double)rand() / RAND_MAX); // Generating numbers in the range [-75, 75].
    }

    return array;
}

int main() {
    int arraySize = 268435456; // Example size: 2^28

    printf("Creating random array with %d elements...\n", arraySize);
    double* inputArray = generateRandomArray(arraySize + 6, 12345); // Adjusting size for stencil operation.
    double* resultArray = (double*)malloc((arraySize) * sizeof(double));

    if (!resultArray) {
        fprintf(stderr, "Memory allocation for result array failed.\n");
        free(inputArray);
        exit(EXIT_FAILURE);
    }

    // Performing stencil computation using the C implementation.
    LARGE_INTEGER startTimeC = getCurrentTime();
    computeStencilC(arraySize, inputArray, resultArray);
    LARGE_INTEGER endTimeC = getCurrentTime();

    double executionTimeC = calculateExecutionTimeInSeconds(startTimeC, endTimeC);
    printf("Execution time (C): %lf seconds.\n", executionTimeC);

    // Resetting result array for assembly computation.
    memset(resultArray, 0, arraySize * sizeof(double));

    // Assembly implementation of stencil computation.
    LARGE_INTEGER startTimeASM = getCurrentTime();
    asm1DStencil(arraySize, inputArray, resultArray);
    LARGE_INTEGER endTimeASM = getCurrentTime();

    double executionTimeASM = calculateExecutionTimeInSeconds(startTimeASM, endTimeASM);
    printf("Execution time (Assembly): %lf seconds.\n", executionTimeASM);

    // Cleanup
    free(inputArray);
    free(resultArray);

    return 0;
}
