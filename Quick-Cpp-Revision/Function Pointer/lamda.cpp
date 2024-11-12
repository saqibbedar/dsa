// Thanks to TheCherno for this program: https://www.youtube.com/watch?v=p4sDgQ-jao4

#include <iostream>

void forEach(int *arr, int size, void(*func)(int)){
    for (int i = 0; i < size; ++i)
    {
        func(arr[i]);
    }
}

int main(){
    int arr[5] = {1, 3, 5, 7, 9};
    forEach(arr, 5, [](int value) { std::cout << value << " "; });
    return 0;
}