// cat - use to display the source code 

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    try
    {
        int sum = 0;

        for (int i = 1; i < argc; ++i){
            if(argv[i][0] >= '0' && argv[i][0] <= '9'){
                sum += std::stoi(argv[i]);
            } else {
                throw("Error: <Bad Type> Argument passed was incorrect");
            }
        }

        std::cout << "Sum: " << sum << std::endl;

    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }
    
    return 0;
}