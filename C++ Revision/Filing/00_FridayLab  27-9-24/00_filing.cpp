#include <iostream>
#include <fstream>
#include <string>

void get(std::string& text){
    std::fstream file("file.txt", std::ios::in);
    if(!file){
        std::cout<<"Error: can't open file!"<<std::endl;
        return;
    }
    std::string temp;
    while(getline(file, temp)){
        text += temp + "\n";
    }
    file.close();
}

void put(std::string text){
    std::fstream file("file.txt", std::ios::out | std::ios::app);
    if(!file){
        std::cout<<"Error: can't access file"<<std::endl;
        return;
    }
    file<<text<<std::endl;
    file.close();
}

int main()
{
    std::ifstream f;
    f.open("file.txt");
    std::string s;
    f >> s;
    std::cout << s << std::endl;
    f.close();
    return 0;
}