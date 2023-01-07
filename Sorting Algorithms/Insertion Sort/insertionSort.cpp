#include <iostream>

/* insertion sort */
void insertionSort(int arr[], int size) {
    int i, temp, j = 0;

    /* loop through array */
    for (i = 0; i < size - 1; i++) {
        /* keep swapping the left with right while arr[j - 1] > arr[j] */
        j = i + 1;
        while (j > 0 && arr[j - 1] > arr[j]) {
            /* swap */
            temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
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
    insertionSort(arr, size);

    std::cout << std::endl;
    std::cout << "Sorted array: ";
    printArray(arr, size);
    std::cout << std::endl;

    return 0;
}
