#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream f;
    f.open("../file.txt");
    std::string s;
    while(!f.eof()){
        f >> s;
        std::cout << s << " ";
    }
    f.close();
    return 0;
}