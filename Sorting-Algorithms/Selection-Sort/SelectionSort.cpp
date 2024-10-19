#include <iostream>

const int SIZE = 5;

int main()
{
    int a[SIZE] = {5, 4, 3, 2, 1};

    for (int i = 0; i < SIZE-1; i++){
        int min_index = i;
        for (int j = i + 1; j < SIZE; j++){
            if(a[j] < a[min_index]){
                min_index = j;
            }
        }
        if(a[i] > a[min_index]){
            std::swap(a[i], a[min_index]);
        }
    }

    for (int i = 0; i < SIZE; i++){
        std::cout << a[i] << ", ";
    }

    return 0;
}
