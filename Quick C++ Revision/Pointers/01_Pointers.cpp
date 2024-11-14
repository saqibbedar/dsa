#include <iostream>
using namespace std;

int main()
{
    int* x;
    x = new int(10);
    cout <<"x = " << x <<" | x& = "<<&x<<endl;

    int *y = x;
    cout <<"y = " << y <<" | y& = "<<&y<<endl;
    
    return 0;
}