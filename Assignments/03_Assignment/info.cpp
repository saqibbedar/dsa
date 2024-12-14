/*      My Digital Library Information System Using forward_list     */

/*                  Features
    
    - Perform CURD Operations
    - Store Books Based on Categories
    - Search Book Based on Category, Author Name and Book Title
    - Smooth Architecture
    - Save Records with Unique ID

*/ 

#include <iostream>
#include <forward_list>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> // for random unique_id
#include <ctime> // for random unique_id
#include <cctype>  // for tolower

bool FindByUID(const char *filename, int uid); // unique_id handler

// Data Model for Books
class BookModel {
    // Book schema
    int unique_id; // book unique id
    char book_name[150]; // book name
    char book_author[100]; // book author
    char year_of_publish[50]; // Book published year
    char category[50]; // book category
    char categories[4][12] = {"General", "Literature", "Science", "Religion"}; // default categories

    friend class Utility; // Access to BookModel Schema

public:
    // constructor
    BookModel(int uid=0, const char* bn="", const char* author="", const char* yop="", const char* category=""){
        this->unique_id = uid;
        strcpy(book_name, bn);
        strcpy(book_author, author);
        strcpy(year_of_publish, yop);
        strcpy(this->category, category);
    };

    // Getter for unique ID
    int GetUID() const {
        return unique_id;
    }

    /* 
        @brief input a book based on book schema defined 
        @param passing filename to input for FindByUID function 
    */
    void input(const char* filename){
        // On every input call, generate a new unique id for each book
        std::srand(time(0));
        while(true){
            int random_number = rand(); // Get a random number
            if(!FindByUID(filename, random_number)){
                unique_id = random_number;
                break;
            }
        }

        do{ // validate Book name
            try
            {
                std::cout << "Enter Book Name: ";
                std::cin.getline(book_name, 150);

                if(std::strlen(book_name) < 4 )
                    throw("Error: <Short Name> Please enter atleast 4-char name");
                if(std::strlen(book_name) >= 150)
                    throw("Error: <Long Name> Please enter 70-char name only");
                
                break;
            }
            catch(const char* error)
            {
                std::cerr << error << '\n';
            }
            
        } while (true);

        do{ // validate Author name
            try
            {
                std::cout << "Enter Book Author: ";
                std::cin.getline(book_author, 100);
                if(std::strlen(book_author) < 3)
                    throw("Error: <Short Name> Please enter atleast 3-char name");
                if(std::strlen(book_author) >= 100)
                    throw("Error: <Long Name> Please enter 50-char name only");
                break;
            }
            catch(const char* error)
            {
                std::cerr << error << '\n';
            }
        } while (true);

        do{ // validate Year of publish
            try
            {
                std::cout << "Enter Year of Publish: <int-only> ";
                std::cin.getline(year_of_publish, 50);

                if (std::strlen(year_of_publish) != 4) {
                    throw("Error: <Invalid publish year> Please enter a 4-digit number");
                }

                if(is_number(year_of_publish)){
                    int year = std::stoi(year_of_publish);
                    if(year > 2024)
                        throw("Error: <Invalid publish year> Publish year can't be > 2024");
                    if(year < 1000)
                        throw("Error: <Invalid publish year> Please enter a 4-digit number");
                } else {
                    throw("Error: <Invalid type> Please enter numbers only");
                }

                break;
            }
            catch(const char* error)
            {
                std::cerr << error << '\n';
            }
        } while (true);

        do{ // validate Category
            try
            {
                std::cout << "Select a category [General, Literature, Science, Religion]: ";
                std::cin.getline(category, 50);
                if(!find_category(category) || std::strlen(category) >= 12)
                    throw("Error: <Invalid category> Please select a valid category");
                break;
            }
            catch(const char* error)
            {
                std::cerr << error << '\n';
            }
            
        } while (true);
    }
    
    // Display
    void display() const{
        std::cout << "_id: " << unique_id << std::endl
                  << "Name: " << book_name << std::endl
                  << "Author: " << book_author << std::endl
                  << "Published: " << year_of_publish << std::endl
                  << "Category: " << category << std::endl;
    }

    // check if entered category match with the defined categories
    bool find_category(const char* str) const{
        for (int i = 0; i < 4; ++i){
            if(strcmp(str, categories[i]) == 0)
                return true;
        }
        return false;
    }

    // handle year_of_publish input
    bool is_number(const char* yop){
        for (int i = 0; i < strlen(yop); ++i){
            if(!std::isdigit(yop[i])){
                return false;
            }
        }
        return true;
    }
    
};

// Utility class: holds helper functions
class Utility {

public:

    /*      Working with Binary Files     */

    // Return Total length of Records/Objects in a binary file
    int getBinaryFileLength(const char* filename){
        std::ifstream f(filename, std::ios::binary | std::ios::in);

        if(!f.is_open()){ // if not file throw exception
            f.close();
            return 0; // if file does not exist
        } else { // if file is available

            // Get the file size
            f.seekg(0, std::ios::end);
            std::streampos file_size = f.tellg();
            f.seekg(0, std::ios::beg);

            f.close(); // close file

            // calculate the no. of objects || Students records
            int size = file_size / sizeof(BookModel);

            // return Student objects size || total records
            return size;
        }
        
    }

    // Write to a file binary file
    void writeToBinaryFile(const char* filename, std::forward_list<BookModel>& books, int size){
        try
        {
            std::ofstream f(filename, std::ios::binary | std::ios::app);

            if(!f.is_open()){ // if file is not available
                throw("Error: <file> Unable to open file to write ");
            }

            std::forward_list<BookModel>::iterator it;

            for (it = books.begin(); it != books.end(); ++it){
                f.write((const char *)(&(*it)), sizeof(BookModel));
            }

            f.close(); // close file
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    // Read from file binary file
    void readFromBinaryFile(const char* filename, std::forward_list<BookModel> &books, int size) 
    {
        try
        {
            // setup ifstream
            std::ifstream f(filename, std::ios::binary | std::ios::in);

            if(!f.is_open()){ // if file is not available
                throw("Error: <file> Unable to open file");
            }

            books.clear(); // clear list before reading records

            for (int i = 0; i < size; ++i)
            {
                BookModel book;
                f.read((char *)&book, sizeof(BookModel)); // read single record
                books.push_front(book); // insert record to list
            }

            f.close(); // close file
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    /*      Working with CSV Files        */

    // Get total records length from CSV file 
    int getCSVFileLength(const char* filename){
        std::ifstream f(filename);
        int size = 0;
        std::string line; // count the lines

        if(!f.is_open()){
            f.close();
            return 0;
        } else {
            while (std::getline(f, line)) {
                ++size;
            }
            f.close();
            return size - 1; // -1 for firs line data headings
        }
    }

    // write to CSV file
    void WriteToCSVFile(const char* filename, int size)
    {
        try
        {
            std::forward_list<BookModel> books;
            readFromBinaryFile(filename, books, size); // read all records

            // setup ofstream to write records to csv file
            std::ofstream f("BooksModel.csv", std::ios::app);

            if(!f.is_open()) {
                throw("Error: <file> Unable to open CSV file to write records");
            } else {

                int csv_file_size = getCSVFileLength("BooksModel.csv"); // get records from csv file

                if(csv_file_size <= 0) { // headings
                    f << "_id,Name,Author,Published,Category" << std::endl;
                }

                std::forward_list<BookModel>::iterator it;

                // write to csv
                for (it = books.begin(); it != books.end(); ++it)
                {
                    f << it->unique_id << "," << it->book_name << "," << it->book_author << "," << it->year_of_publish << "," << it->category << std::endl;
                }

                std::cout << "\nData Exported Successfully to CSV file" << std::endl;

                f.close();
            }

        }
        catch(const char *error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    // Read from CSV file
    void ReadFromCSVFile(const char* filename) {
        std::ifstream f;
        f.open("BooksModel.csv");
        if(!f.is_open()){
            throw("Error: <file> Unable to open CSV file for reading");
        } else {

            int size = getCSVFileLength("BooksModel.csv");
            if(size <= 0){
                throw("Error: <Invalid Size> Please first enter some records in CSV file");
            }

            std::forward_list<BookModel> books;
            std::string temp;

            std::getline(f, temp); // read first line

            BookModel book;

            while(std::getline(f, temp, ',')){
                // read unique id
                book.unique_id = std::stoi(temp);

                // read book name
                std::getline(f, temp, ',');
                strcpy(book.book_name, temp.c_str());

                // read book author
                std::getline(f, temp, ',');
                strcpy(book.book_author, temp.c_str());

                // read year of publish
                std::getline(f, temp, ',');
                strcpy(book.year_of_publish, temp.c_str());

                // read category
                std::getline(f, temp);
                strcpy(book.category, temp.c_str());
                books.push_front(book); // push book to the list
            }

            writeToBinaryFile(filename, books, size); // write data to binary

            std::cout << "\nData Imported Successfully to Binary file" << std::endl; // screen message
        }
    }

};

int main(){
    std::forward_list<BookModel> books;

    BookModel b1, b2;
    b1.input("file.bin");
    b2.input("file.bin");

    books.push_front(b1);
    books.push_front(b2);

    Utility utils;
    int binary_file_size = utils.getBinaryFileLength("file.bin");
    utils.writeToBinaryFile("file.bin", books, binary_file_size);

    books.clear(); // clear list 

    // int size = utils.getBinaryFileLength("file.bin");

    utils.readFromBinaryFile("file.bin", books, binary_file_size);
    // utils.WriteToCSVFile("file.bin", size);
    // utils.ReadFromCSVFile("file.bin");

    for (std::forward_list<BookModel>::iterator it = books.begin(); it != books.end(); ++it){
        it->display();
    }

    return 0;
} 

// Check if a book id is already taken? 
bool FindByUID(const char* filename, int uid){
    std::forward_list<BookModel> books;
    Utility utils;

    // get total objects size from file
    int size = utils.getBinaryFileLength(filename);

    if(size <= 0){ // return false if there is no record available
        return false;
    }

    utils.readFromBinaryFile(filename, books, size);

    std::forward_list<BookModel>::iterator it;

    for (it = books.begin(); it != books.end(); ++it)
    {
        if(it->GetUID() == uid){
            return true;
        }
    }

    return false;
}
