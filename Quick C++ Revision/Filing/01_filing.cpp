#include <iostream>
#include <fstream>

int main() {
    std::fstream file("file.txt", std::ios::out | std::ios::app | std::ios::ate);
    file << "# file handling data\n" << std::endl;
    file.close();
    return 0;
}