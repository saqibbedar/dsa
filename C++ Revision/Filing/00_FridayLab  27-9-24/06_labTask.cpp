#include <iostream>
#include <fstream>
#include <string>

int main(){

    std::fstream f("database.csv", std::ios::out | std::ios::in | std::ios::app);

    // writing to the file

    // name, age, gpa
    // std::string name;
    // int age;
    // int gpa;

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

    std::string s[2];
    int age[2];
    int gpa[2];

    int i = 0;
    float average = 0;
    if(f.is_open()){
        while(f.good()){
        // getline(f, s); // we can go with this logic to read whole text as a string and print it
        f >> s[i] >> age[i] >> gpa[i];
        i++;
    }

    for (int i = 0; i < 2; i++){
        std::cout<< s[i] << " " <<  age[i] << " " << gpa[i] << std::endl;
        average += gpa[i];
    }

    std::cout << "Average gpa is: " << (average / 2)  << std::endl;

    f.close();
    } else{
        std::cerr << "Error while locating the resources!" << std::endl;
    }

    return 0;
}