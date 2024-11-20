// seekg() is a function used to move the get pointer (input pointer) to a specified location in the input sequence.
// It can be used to set the position relative to the beginning of the file, the current position, or the end of the file.
// seekg() takes two parameters: the first parameter is the offset (number of bytes to move), and the second parameter is the direction (std::ios::beg, std::ios::cur, or std::ios::end).

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream f;
    f.open("../file.txt"); // Open the file for reading

    // seekg(): we can pass other args for reading from end of the file
    // f.seekg(-8, std::ios::beg) || f.seekg(-8, std::end) || f.seekg(-8, std::cur)
    f.seekg(15); // Move the get pointer to the 15th byte from the beginning of the file

    std::string s;

    // Read the file line by line
    while(f.good()){ 
        std::cout << f.tellg() << " "; // Output the current position of the get pointer
        getline(f, s); // Read a line from the file
        std::cout << s << std::endl; // Output the line
    }
    f.close(); // Close the file
    return 0;
}