#include <iostream>
using namespace std;

int main()
{
    int h = 10;
    cout << "h addr: " << &h << endl; // 0x2008
    int* x = &h;
    cout <<"value of pointer x: "<< x <<endl; // pointer has addr as its value i.e. 0x2008
    int y = *x; // 10
    cout << y << endl; // 10

    int *z;
    z = new int(10); // z pointer created in heap with value 10

    cout << z << endl; // address 
    cout << *z << endl; // Dereference pointer

    delete z;
    z = nullptr;
    return 0;
}