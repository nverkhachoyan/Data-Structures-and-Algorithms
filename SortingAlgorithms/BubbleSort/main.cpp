#include <iostream>

void bubbleSort(int arr[], int size);
void printArray(int arr[], int size);

int main() {
    int arr[5] = {5, 1, 2, 6, 9};
    int size = sizeof arr / sizeof arr[0];

    std::cout << "Unsorted array: ";
    printArray(arr, size);

    // sort the array
    bubbleSort(arr, size);

    std::cout << std::endl;
    std::cout << "Sorted array: ";
    printArray(arr, size);

    return 0;
}

void bubbleSort(int arr[], int size) {
    int temp = 0;

    for (int i = size; i > 0; i--) {
        for (int j = 1; j < i; j++) {
            if (arr[j - 1] > arr[j]) {
                temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ",";
    }
}