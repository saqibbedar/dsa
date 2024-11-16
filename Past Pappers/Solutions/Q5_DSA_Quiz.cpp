// write code which takes a file name as command line argument and checks whether this file exists or not? If file exists, your program should display its contents, if it does not exist, your program should create it and display message "File Created".


#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]){
    std::ifstream f;
    std::string temp;

    for (int i = 1; i < argc; ++i){
        f.open(argv[i]);
        if(f.is_open()){
            while (f.good())
            {
                std::getline(f, temp);
                std::cout << temp;
            }
            std::cout << std::endl;
            f.close();
        } else {
            std::ofstream out;
            out.open(argv[i]);
            if(out.is_open()){
                std::cout << "File Created";
            }
        }
    }

    return 0;
}