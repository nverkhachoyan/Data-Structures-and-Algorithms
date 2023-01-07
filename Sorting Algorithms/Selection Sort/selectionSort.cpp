#include <iostream>

/* selection sort */
void selectionSort(int arr[], int size) {
    int currMinimum, temp;

    for (size_t i = 0; i < size; i++) {
        currMinimum = i;
        /* look for the minimum in the unsoerted list */
        for (size_t j = i + 1; j < size; j++) {
            if (arr[j] < arr[currMinimum]) {
                currMinimum = j;
            }
        }
        /* swap elements */
        temp = arr[i];
        arr[i] = arr[currMinimum];
        arr[currMinimum] = temp;
    }
}

// prints the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ",";
    }
}

int main() {
    int arr[5] = {5, 1, 2, 6, 9};
    int size = sizeof arr / sizeof arr[0];

    std::cout << "Unsorted array: ";
    printArray(arr, size);

    // sort the array
    selectionSort(arr, size);

    std::cout << std::endl;
    std::cout << "Sorted array: ";
    printArray(arr, size);
    std::cout << std::endl;

    return 0;
}
