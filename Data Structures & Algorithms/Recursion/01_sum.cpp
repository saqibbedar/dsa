#include <iostream>

int sum(int n){
    if(n == 0){
        return 0;
    } else {
        return n + sum(n - 1);
    }
}

int main()
{
    std::cout << sum(5);
    return 0;
}