#pragma once
#include <iostream>
#include <fstream>
#include <cstring>

namespace my_std {

// Student Class
class Student
{
private:
    int _id; // Student Id
    char name[18]; // Student Name

public:
    // constructor
    Student(int i = 0, const char* n = ""): _id(i){
        strncpy(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    // member functions
    void read(){}
    void display()const{}
    
    // getter & Setters
    inline int get_id() const { return _id; }
    inline const char* get_name() const { return name; }
    inline void set_id(int x) { _id = x; }
    inline void set_name(const char *n) {  
        strncpy(name, n, sizeof(name) - 1); 
        name[sizeof(name) - 1] = '\0'; 
    }
};

/*     Member functions        */

// Read a record
void Student::read(){
    std::cout << "Enter Student Id: ";
    std::cin >> _id;
    std::cout << "Enter Student Name: ";
    std::cin >> name;
}
// display a record
void Student::display() const {
    std::cout << "Id: " << _id << std::endl<< "Name: "<<name << std::endl;
}


/*      File Handlers       */

// write to a file
void writeToFile(const char* filename, const Student* s, int size){
    std::ofstream f(filename, std::ios::binary | std::ios::out);
    if(!f){
        throw("Error while opening file for writing");
    } else {
        for (int i = 0; i<size; ++i){
            f.write((const char *)&s[i], sizeof(Student));
            if(f.fail()){
                throw("Error while writing to file");
            }
        }
    }
}

// read from file a file
void readFromFile(const char* filename, const Student* s, int size){

    std::ifstream f(filename, std::ios::binary | std::ios::in);

    if(!f){
        throw("Error while opening file for reading");
    } else {
        f.read((char *)s, size * sizeof(Student));
        if (f.fail()) {
            throw("Error while reading from file");
        }
    }
}

// Return Total length of Records/Objects
int records_len(const char* filename){
    std::ifstream f(filename, std::ios::binary | std::ios::in);

    if(!f){
        throw("Error while opening file");
    }
    else{
        // Get the file size
        f.seekg(0, std::ios::end);
        std::streampos file_size = f.tellg();
        f.seekg(0, std::ios::beg);

        f.close(); // close file

        // calculate the no. of objects || Students records
        int size = file_size / sizeof(Student);

        // return Student objects size || total records
        return size;

    }

}

}