#include <stdio.h>
#include <time.h>

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already in place, so no need to check them
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver program to test the implementation
int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    printArray(arr, n);

    // Measure the execution time of Bubble Sort
    clock_t start_time = clock();
    bubbleSort(arr, n);
    clock_t end_time = clock();

    printf("Sorted array: ");
    printArray(arr, n);

    // Calculate the execution time
    double execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", execution_time);

    return 0;
}
