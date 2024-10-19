#include <iostream>
#include <fstream>

int main() {
    std::fstream file("file.txt", std::ios::out | std::ios::app);
    file << "Hello, world" << std::endl;
    file.close();
    return 0;
}