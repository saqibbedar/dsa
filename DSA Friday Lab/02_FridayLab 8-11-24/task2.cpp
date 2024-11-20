#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    std::ifstream f;
    std::string temp;

    try
    {
        for (int i = 1; i < argc; ++i){

            f.open(argv[i]); // only file

            if(f.is_open()){

                while (f.good())
                {
                    std::getline(f, temp); // get file data
                    std::cout << temp << std::endl; // print data to console
                }
                f.close();
                } else {
                throw("Error: <file> Unable to open provided file");
            }
        }

    }
    catch(const char* error)
    {
  //      delete[] temp;
        std::cerr << error << '\n';
    }

//    delete[] temp;
    return 0;
}