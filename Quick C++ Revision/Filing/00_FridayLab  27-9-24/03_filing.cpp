#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream f;
    f.open("../file.txt");
    std::string text;
    while(getline(f, text)){
        std::cout << text <<std::endl;
    }
    f.close();
    return 0;
}