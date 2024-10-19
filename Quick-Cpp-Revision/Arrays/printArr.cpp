#include <iostream>
using namespace std;

void fun(int * arr, int n){
    for(int i=0; i<n; i++)
        cout<<arr[i]<<" ";
}

int main(){
    int arr[5] = {1,3,4,5,6};
    fun(arr, 5);
    return 0;
}