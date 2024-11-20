#include <iostream>
#include <fstream>
#include <string>

int main(){

    std::fstream f("database.csv", std::ios::out | std::ios::in | std::ios::app);

    // writing to the file

    // name, age, gpa
    std::string name;
    int age;
    int gpa;

    // for (int i = 0; i < 2; i++){
    //     std::cout << "What's name? " << std::endl;
    //     std::cin.ignore();
    //     getline(std::cin, name);
    //     std::cout << "What's age? " << std::endl;
    //     std::cin>>age;
    //     std::cout << "What's gpa? " << std::endl;
    //     std::cin>>gpa;

    //     // write to file
    //     f << name << " " <<  age << " " << gpa << std::endl;
    // }

    // std::string s;

    if(f.is_open()){
        std::string tempAge;
        std::string tempGPA;
        while(f.good()){
        
            getline(f, name, ' ');
            getline(f, tempAge, ' ');
            getline(f, tempGPA, ' ');
            
            age = std::stoi(tempAge);
            gpa = std::stoi(tempGPA);

            std::cout << name << " " << age << " " << gpa << std::endl;
        }
    
    f.close();

    } else{
        std::cout << "Error while locating the resources!" << std::endl;
    }

    return 0;
}