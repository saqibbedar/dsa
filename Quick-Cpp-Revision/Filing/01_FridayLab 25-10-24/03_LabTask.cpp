/*
1. Write a program which writes n records of books/student  to the file, where n is given by the user.
2. Write a program which reads all the records in the file into the memory and displays those records ()
3. Write a program which displays nth record from the file
4. Write a program which updates nth record in the file
5. Bonus: Write a program which deletes nth record from the file
*/

#include <iostream>
#include <fstream>
#include <cstring>

namespace record {
class Student{
    public:
    int std_id; // student id
    char std_name[18]; // student name

    // constructor
    Student(int i=0, const char* n = ""): std_id(i) {
        strcpy(std_name, n);
    }

    void read(){
        std::cout << "Enter Student Id: ";
        std::cin >> std_id;
        std::cout << "Enter Student Name: ";
        std::cin >> std_name;
    }

    // display the record
    void display() const {
        std::cout << "Id: " << std_id << std::endl
        << "Name: "<<std_name << std::endl;
    }
};
}

// helper function for clean up of memory
void dealloc(const record::Student *s){
    delete[] s;
}

int main(){

    // Task 1:

    // // create a Student.bin file
    // std::ofstream f;
    // f.open("Student.bin", std::ios::binary | std::ios::out);

    // // Take the no. of records from user
    // int n; // store no. of records
    // std::cout << "Enter no. of Students you want to register: ";
    // std::cin >> n;

    // record::Student *s = new record::Student[n];

    // for (int i = 0; i<n; ++i){
    //     s[i].read();
    // }

    // // writing n number of records as given by user
    // for (int i = 0; i < n; ++i) {
    //     if(f.is_open()){
    //     f.write((const char *)&s[i], sizeof(record::Student));
    //     } else {
    //         std::cout << "Unable to open file" << std::endl;
    //     }
    // }

    // // clean up memory
    // dealloc(s);
    // f.close();

    // // Task 2:

    // setup ifstream for reading from file
    // std::ifstream f;
    // f.open("Student.bin", std::ios::binary | std::ios::in);

    // if(f.is_open()){

    //     // Get the size of the file
    //     f.seekg(0, std::ios::end);
    //     std::streampos fileSize = f.tellg();
    //     f.seekg(0, std::ios::beg);

    //     // Calculate the number of records
    //     int n = fileSize / sizeof(record::Student);

    //     record::Student *s = new record::Student[n];

    //     // Read the records from the file
    //     f.read((char *)s, n * sizeof(record::Student));
    //     for (int i = 0; i < n; ++i){
    //         s[i].display();
    //     }

    //     // dealloc memory
    //     dealloc(s);
    // } else {
    //     std::cout << "Unable to open file." << std::endl;
    // }
    
    // // dealloc dynamic memory & close file
    // f.close();


    // // Task 3:
    
    // // setup ifstream for reading from file
    // std::ifstream f;
    // f.open("Student.bin", std::ios::binary | std::ios::in);

    // if(f.is_open()){

    //     // Get the size of the file
    //     f.seekg(0, std::ios::end);
    //     std::streampos fileSize = f.tellg();
    //     f.seekg(0, std::ios::beg);

    //     // Calculate the number of records
    //     int n = fileSize / sizeof(record::Student);

    //     // Take input to display the nth record from file
    //     std::cout << "Enter the index of record you want to display from "<<n-1 <<" records: ";
    //     int no_of_records;
    //     std::cin >> no_of_records;

    //     record::Student *s = new record::Student[n];

    //     // Read the records from the file
    //     f.read((char *)s, n * sizeof(record::Student));

    //     s[no_of_records].display(); // display the record

    //     // dealloc memory
    //     dealloc(s);
    // } else {
    //     std::cout << "Unable to open file." << std::endl;
    // }

    // // dealloc dynamic memory & close file
    // f.close();


    // Task 4:
    
    // setup ifstream for reading from file
    // std::ifstream f;
    // f.open("Student.bin", std::ios::binary | std::ios::in);

    // if(f.is_open()){

    //     // Get the size of the file
    //     f.seekg(0, std::ios::end);
    //     std::streampos fileSize = f.tellg();
    //     f.seekg(0, std::ios::beg);

    //     // Calculate the number of records
    //     int n = fileSize / sizeof(record::Student);

    //     // Take input to display the nth record from file
    //     std::cout << "Enter the index of record you want to update from "<<n-1 <<" records: ";
    //     int record;
    //     std::cin >> record; // getting record to update it
        
    //     // Get Student temporary record to update it
    //     std::cout << "Enter Student Id: ";
    //     int id;
    //     std::cin >> id;

    //     std::cout << "Enter Student Name: ";
    //     char *name = new char[18];
    //     std::cin >> name;

    //     record::Student *s = new record::Student[n];

    //     // Read the records from the file
    //     f.read((char *)s, n * sizeof(record::Student));

    //     s[record].std_id = id;
    //     strcpy(s[record].std_name, name);

    //     // Update the record
    //     std::ofstream out;
    //     out.open("Student.bin", std::ios::binary | std::ios::out);
    //     out.write((const char *)&s[record], sizeof(record::Student));

    //     // display the updated record
    //     std::cout << "Update Student Record" << std::endl;
    //     for (int i = 0; i < n; ++i){
    //         s[i].display();
    //     }

    //     // dealloc memory
    //     delete[] name;
    //     dealloc(s);
    // } else {
    //     std::cout << "Unable to open file." << std::endl;
    // }

    // // dealloc dynamic memory & close file
    // f.close();


    // Task 5: Write a program which deletes nth record from the file

    // setup ifstream for reading from file
    std::ifstream f;
    f.open("Student.bin", std::ios::binary | std::ios::in);

    if(f.is_open()){

        // Get the size of the file
        f.seekg(0, std::ios::end);
        std::streampos fileSize = f.tellg();
        f.seekg(0, std::ios::beg);

        // Calculate the number of records
        int n = fileSize / sizeof(record::Student);

        // Take the index to delete a record
        std::cout << "Enter the index of record you want to delete from "<<n-1 <<" records: ";
        int record_index;
        std::cin >> record_index; // getting record to update it

        record::Student *s = new record::Student[n];

        // Read the records from the file
        f.read((char *)s, n * sizeof(record::Student));

        // Create a temporary dynamic array of Students to hold the records excluding record_index
        record::Student *tempStdRecord = new record::Student[n-1]; // using n-1 because we will exclude the record_index

        // overwrite the records
        for (int i = 0, j = 0; i < n; ++i)
        {
            if(i != record_index){
                tempStdRecord[j++] = s[i];
            }
        }

        // update file with new records
        std::ofstream out;
        out.open("Student.bin", std::ios::binary | std::ios::out | std::ios::trunc);

        for (int i = 0; i < n - 1; ++i)
        {
            out.write((const char *)&tempStdRecord[i], sizeof(record::Student));
        }

        // display the updated records
        std::cout << "Updated Student Records" << std::endl;
        for (int i = 0; i < n - 1; ++i){
            tempStdRecord[i].display();
        }

        // dealloc memory
        dealloc(tempStdRecord);
        out.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }

    // dealloc dynamic memory & close file
    f.close();
    return 0;

}