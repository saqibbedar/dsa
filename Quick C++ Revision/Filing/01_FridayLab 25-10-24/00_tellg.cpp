/**
 * @file 00_tellg.cpp
 * @brief Demonstrates the use of tellg() function in file handling.
 *
 * The tellg() function is used to get the current position of the get pointer in an input stream.
 * It returns the position as a streampos object, which can be used to determine the current read position in the file.
 * The tellg() function does not take any parameters.
 */

#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Main function to demonstrate the use of tellg() in file handling.
 *
 * This function opens a file named "file.txt" located in the parent directory,
 * reads its content line by line, and prints the current position of the get pointer
 * before reading each line.
 *
 * @return int Returns 0 upon successful execution.
 */
int main()
{
    std::ifstream f; // Input file stream object
    f.open("../file.txt"); // Open the file in read mode
    std::string s; // String to store each line read from the file
    while(f.good()){ 
        std::cout << f.tellg() << " "; // Print the current position of the get pointer
        getline(f, s); // Read a line from the file
        std::cout << s << std::endl; // Print the line read from the file
    }
    f.close(); // Close the file
    return 0;
}