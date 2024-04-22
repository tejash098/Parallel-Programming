#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define DATASET_SIZE 10000

// Function to merge two halves of an array
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform parallel merge sort
void mergeSortParallel(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);
            #pragma omp section
            mergeSortParallel(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// Function to perform serial merge sort
void mergeSortSerial(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSortSerial(arr, l, m);
        mergeSortSerial(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Function to print an array
void printArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int dataset[DATASET_SIZE];
    int datasetCopy[DATASET_SIZE]; // Copy for serial merge sort

    // Read dataset from "numbers.txt"
    FILE *file = fopen("numbers.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < DATASET_SIZE; i++) {
        if (fscanf(file, "%d", &dataset[i]) != 1) {
            fprintf(stderr, "Error reading from file");
            return 1;
        }
        datasetCopy[i] = dataset[i]; // Copy for serial merge sort
    }

    fclose(file);

    // Parallel merge sort
    double start_time_parallel = omp_get_wtime();
    mergeSortParallel(dataset, 0, DATASET_SIZE - 1);
    double end_time_parallel = omp_get_wtime();

    // Serial merge sort
    double start_time_serial = omp_get_wtime();
    mergeSortSerial(datasetCopy, 0, DATASET_SIZE - 1);
    double end_time_serial = omp_get_wtime();

    // Verify if both serial and parallel implementations produce the same result
    for (int i = 0; i < DATASET_SIZE; i++) {
        if (dataset[i] != datasetCopy[i]) {
            printf("Error: Serial and Parallel implementations do not match.\n");
            break;
        }
    }

    // Print sorted data
    printf("\nSorted data using Parallel Merge Sort:\n");
    printArray(dataset, DATASET_SIZE);

    printf("\nParallel Merge Sort Execution Time: %f seconds\n", end_time_parallel - start_time_parallel);
    printf("Serial Merge Sort Execution Time: %f seconds\n", end_time_serial - start_time_serial);

    return 0;
}
