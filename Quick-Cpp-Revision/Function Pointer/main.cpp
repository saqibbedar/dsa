#include <iostream>

void helloWord(){
    std::cout << "Hello, world" << std::endl;
}

void printValue(int a){
    std::cout << "Value: " << a << std::endl;
}

int main()
{
    auto function = helloWord; // assigned by reference explicitly
    function();

    void (*function2)() = helloWord; // this is how above function was assigned
    function2();

    // define the function pointer type to reuse it
    typedef void(*myType)(int);

    myType foo = printValue;

    foo(10);

    return 0;
}