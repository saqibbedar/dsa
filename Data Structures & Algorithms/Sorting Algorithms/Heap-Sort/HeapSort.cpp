#include <iostream>

template <typename T>
void ReHeapDown(T arr[], int first, int last){
    int left = (2 * first) + 1;
    int right = (2 * first) + 2;
    int max = left;

    if(left > last){
        return;
    } else {
        if(right <= last && arr[right] > arr[left]){
            max = right;
        }
        if(arr[max] <= arr[first]){
            return;
        }

        std::swap(arr[first], arr[max]);
        ReHeapDown(arr, max, last);
    }


}

template <typename T>
void heap_sort(T arr[], int n){
    // heapify
    for (int i = n / 2 - 1; i >= 0; --i) {
        ReHeapDown(arr, i, n - 1);
    }

    // sorting
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        ReHeapDown(arr, 0, i - 1);
    }
}

int main(){

    int arr[5] = {5, 3, 29, 17, 11};
    heap_sort(arr, 5);

    for(int x: arr){
        std::cout << x << " ";
    }

    return 0;
}