#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 10000

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortSerial(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSortSerial(arr, low, pi - 1);
        quickSortSerial(arr, pi + 1, high);
    }
}

void quickSortParallel(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

#pragma omp task
        quickSortParallel(arr, low, pi - 1);
#pragma omp task
        quickSortParallel(arr, pi + 1, high);
    }
}

void parallelQuickSort(int arr[], int low, int high) {
#pragma omp parallel
#pragma omp single nowait
    quickSortParallel(arr, low, high);
}

int main() {
    int arr[SIZE];
    FILE *file, *outputFile;
    file = fopen("number2.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    // Serial Quick Sort
    double serial_start = omp_get_wtime();
    quickSortSerial(arr, 0, SIZE - 1);
    double serial_end = omp_get_wtime();

    printf("Serial Quick Sort Time: %f seconds\n", serial_end - serial_start);

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
    file = fopen("number2.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    // Parallel Quick Sort
    double parallel_start = omp_get_wtime();
    parallelQuickSort(arr, 0, SIZE - 1);
    double parallel_end = omp_get_wtime();

    printf("Parallel Quick Sort Time: %f seconds\n", parallel_end - parallel_start);

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