#include <iostream>
using namespace std;

template <class T>
class Arithmetic
{
    T a;
    T b;

public:
    Arithmetic(T a, T b)
    {
        this->a = a;
        this->b = b;
    }

    T add();
    T sub();
};

// accessing them using scope resolution operator and see syntax for a template class

template <class T>
T Arithmetic<T>::add()
{
    return a + b;
}

template <class T>
T Arithmetic<T>::sub()
{
    return a - b;
}

int main()
{
    Arithmetic<int> a(10, 20);
    cout << a.add() << endl;

    Arithmetic<float> b(2.5, 2);
    cout << b.add() << endl;

    return 0;
}