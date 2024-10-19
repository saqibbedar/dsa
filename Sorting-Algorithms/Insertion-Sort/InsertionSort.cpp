#include <iostream>

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {  // Start from the second element
        int current = arr[i];
        int j = i - 1;  // Start comparing with the previous element
        // Shift elements of arr[0..i-1] that are greater than current
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;  // Place current in the correct position
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl; 
}

int main() {
    const int SIZE = 5;
    int arr[SIZE] = {5, 4, 3, 2, 1};
    insertion_sort(arr, SIZE);
    printArray(arr, SIZE);
    
    return 0;
}
