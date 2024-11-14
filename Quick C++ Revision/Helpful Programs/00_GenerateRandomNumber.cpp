#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    int max_val = 19652004;
    int random = rand() % (max_val + 1);
    cout << random;
    return 0;
}