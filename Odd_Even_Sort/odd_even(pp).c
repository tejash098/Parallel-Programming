#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 10000

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void oddEvenSortSerial(int arr[], int n) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;

        // Odd phase
        for (int i = 1; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                sorted = 0;
            }
        }

        // Even phase
        for (int i = 0; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                sorted = 0;
            }
        }
    }
}

void oddEvenSortParallel(int arr[], int n) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;

#pragma omp parallel for
        // Odd phase
        for (int i = 1; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                sorted = 0;
            }
        }

#pragma omp parallel for
        // Even phase
        for (int i = 0; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                sorted = 0;
            }
        }
    }
}

int main() {
    int arr[SIZE];
    FILE *file, *outputFile;
    file = fopen("numbers.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    // Serial Odd-Even Transposition Sort
    double serial_start = omp_get_wtime();
    oddEvenSortSerial(arr, SIZE);
    double serial_end = omp_get_wtime();

    printf("Serial Odd-Even Sort Time: %f seconds\n", serial_end - serial_start);

    // Save sorted array to a file
    outputFile = fopen("sorted_serial.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error creating output file\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    fclose(outputFile);

    // Reset the array
    file = fopen("numbers.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    // Parallel Odd-Even Transposition Sort
    double parallel_start = omp_get_wtime();
    oddEvenSortParallel(arr, SIZE);
    double parallel_end = omp_get_wtime();

    printf("Parallel Odd-Even Sort Time: %f seconds\n", parallel_end - parallel_start);

    // Save sorted array to a file
    outputFile = fopen("sorted_parallel.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error creating output file\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    fclose(outputFile);

    return 0;
}
