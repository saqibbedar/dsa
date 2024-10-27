#include "record.h"

// Task 1: Write a program which writes n records of books/student to the file, where n is given by the user.
void task_one(const char* filename){

    int n;
    std::cout << "Enter no. of Students you want to register: ";
    std::cin >> n;

    my_std::Student *s = new my_std::Student[n]; // allocating dynamic memory

    for (int i = 0; i < n; ++i){
        s[i].read();
    }

    // Write Student Record
    try
    {
        my_std::writeToFile(filename, s, n);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    delete[] s; // Deallocate dynamic memory
}

// Task 2: Write a program which reads all the records in the file into the memory and displays those records
void task_two(const char* filename){
    int n = my_std::records_len(filename); // get size of student records

    my_std::Student *s = new my_std::Student[n]; // allocating dynamic memory

    // Read records from file
    try
    {
        my_std::readFromFile(filename, s, n);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    // Display all records
    for (int i = 0; i < n; ++i)
    {
        s[i].display();
    }

    delete[] s; // deallocate dynamic memory
}

// Task 3: Write a program which displays nth record from the file
void task_three(const char* filename){
    int n;
    try
    {
        n = my_std::records_len(filename); // get size of student records
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // Allocate dynamic memory to Student objects
    my_std::Student *s = new my_std::Student[n];

    // read from file
    try
    {
        my_std::readFromFile(filename, s, n);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    // Get nth record index from user
    std::cout << "Enter the index of record you want to display from "<<n-1 <<" records: ";
    int record_index;
    std::cin >> record_index;

    // display nth record
    s[record_index].display();

    delete[] s;
}

// Task 4: Write a program which updates nth record in the file
void task_four(const char* filename){

    int n; // Record Size holder
    try
    {
        n = my_std::records_len(filename); // Get record size
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    // Input index to update the nth record in file
    int record_index;
    std::cout << "Enter the index of record you want to update from "<<n-1 <<" records: ";
    std::cin >> record_index;
        
    // Get Student temporary record to update it
    std::cout << "Enter Student Id: ";
    int id;
    std::cin >> id;

    std::cout << "Enter Student Name: ";
    char *name = new char[18];
    std::cin >> name;

    // Allocate dynamic memory for Student Objects
    my_std::Student *s = new my_std::Student[n];

    // read records from file
    try
    {
        my_std::readFromFile(filename, s, n);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    // Update Record
    s[record_index].set_id(id);
    s[record_index].set_name(name);

    // Update file
    try
    {
        my_std::writeToFile(filename, s, n);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    // display the updated record
    std::cout << "Update Student Record" << std::endl;
    for (int i = 0; i < n; ++i){
        s[i].display();
    }
    
    // Cleanup memory
    delete[] name;
    delete[] s;
}

// Task 5: Write a program which deletes nth record from the file
void task_five(const char* filename){
    // code is pending for now
}

int main()
{
    const char filename[12] = "Student.bin";
    task_one(filename);
    // task_two(filename);
    // task_three(filename);
    // task_four(filename);

    return 0;
}