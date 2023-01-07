# Selection Sort

Selection sort is an algorithm for sorting an array of elements. It works by repeatedly finding the minimum element from the unsorted portion of the array and adding it to the sorted portion of the array.

To implement selection sort in C++, we can follow these steps:

1. Loop through the array, starting at the first element.
2. Find the minimum element in the unsorted portion of the array.
3. Swap the minimum element with the first element of the unsorted portion of the array.
4. Repeat this process until the entire array is sorted.

Here is some example code that demonstrates how to implement selection sort in C++:

```cpp
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
```

This implementation of selection sort has a time complexity of O(n^2), which makes it less efficient than some other sorting algorithms for large arrays. However, it is simple to understand and implement, and it can be a useful tool in certain situations.
