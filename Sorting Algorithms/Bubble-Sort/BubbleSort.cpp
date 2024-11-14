#include <iostream>
using namespace std;

void BubbleSort(int a[], int n){

    bool isSwapped = true; // check if values are swapped or not

    for (int i = 0; i < n - 1; i++)
    {
        isSwapped = false;
        for (int j = 0; j < n - i - 1; j++){
            if(a[j] > a[j+1]) {
                swap(a[j], a[j + 1]);
                isSwapped = true;
            }
        }
        // If no two elements were swapped by inner loop, then break
        if(!isSwapped)
            break;
    }
      

}

int main()
{
    int a[5] = {5, 4, 3, 2, 1};

    int n = 5;

    BubbleSort(a, 5);

    for (int x: a)
    {
        cout << x << " ";
    }

        return 0;
}