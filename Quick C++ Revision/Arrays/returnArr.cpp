#include <iostream>
using namespace std;

int* fun(int n){
    int *ptr = new int[n];
    for(int i=0; i<n; i++){
        ptr[i] = i+1;
    }
    return ptr;
}

int main()
{
    int *ptrArr;
    ptrArr = fun(5);

    for(int i=0; i<5; i++){
        cout<<ptrArr[i]<<" ";
    }

    delete [] ptrArr;

    return 0;
}