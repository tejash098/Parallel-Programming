#include <stdio.h>
#include <time.h>

// Function to perform odd-even transposition sort
void oddEvenSort(int arr[], int n) {
    int sorted = 0; // Flag to check if the array is sorted
    while (!sorted) {
        sorted = 1; // Assume the array is sorted initially
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                // Swap elements if they are in the wrong order
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                sorted = 0; // Set the flag to indicate that the array is not sorted
            }
        }
        
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                // Swap elements if they are in the wrong order
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                sorted = 0; // Set the flag to indicate that the array is not sorted
            }
        }
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
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

    clock_t start_time = clock();
    oddEvenSort(arr, n);
    clock_t end_time = clock();

    printf("Sorted array: ");
    printArray(arr, n);

    double execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", execution_time);

    return 0;
}
