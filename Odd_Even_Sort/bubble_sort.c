/*Algorithm
bubbleSort(array)  
n = length(array)  
repeat  
  swapped = false  
  for i = 1 to n - 1  
         if array[i - 1] > array[i], then  
         swap(array[i - 1], array[i])  
         swapped = true  
         end if  
   end for  
   n = n - 1  
 until not swapped  
end bubbleSort  
*/
#include <stdio.h>
#define DATASET_SIZE 10000
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main() {
    FILE *file;
    int dataset[DATASET_SIZE];
    int i = 0;
    file = fopen("number2.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    while (fscanf(file, "%d", &dataset[i]) == 1) {
        i++;
    }
    fclose(file);
    bubbleSort(dataset, DATASET_SIZE);
    printf("Sorted numbers in decreasing order:\n");
    for (int j = 0; j < DATASET_SIZE; j++) {
        printf("%d\n", dataset[j]);
    }
    return 0;
}
