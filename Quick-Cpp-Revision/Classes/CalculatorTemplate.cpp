#include <iostream>
#include <string>
using namespace std;

class Error
{
    string msg;

public:
    Error(const string &msg) : msg(msg) {};
    void showError()
    {
        cout << msg;
    }
};

template <class T>
class Calculator
{
    T a, b;

public:
    Calculator(T a, T b) : a(a), b(b) {};
    T add()
    {
        return a + b;
    }
    T sub()
    {
        return a - b;
    }
    T mul()
    {
        return a * b;
    }
    T div()
    {
        if (b <= 0)
        {
            Error("Division with zero is not possible.");
            return -1;
        }
        return a / b;
    }
};

int main()
{
    Calculator<int> c(10, 20);
    int result = c.add();
    cout << result << endl;
    return 0;
}