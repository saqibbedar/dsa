#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::ifstream f;
    f.open("../file.txt");
    std::string s;
    while(!f.eof()){ 
        getline(f, s);
        std::cout << s << std::endl;
    }
    f.close();
    return 0;
}