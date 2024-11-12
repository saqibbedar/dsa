/*      My Digital Library Information System       */

/*                  Features
    
    - Perform CURD Operations
    - Store Books Based on Categories
    - Search Book Based on Category, Author Name and Book Title
    - Smooth Architecture
    - Save Records with Unique ID

*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> // for random unique_id
#include <ctime> // for random unique_id
#include <cctype>  // for tolower

// Utility class handle file operations and holds helper functions
class Utility; // forward declaration to use it in BookModel
class BACKEND; // forward declaration

bool FindByUID(const char *filename, int uid); // unique_id handler

// Book Model
class BookModel {
    // Book schema
    int unique_id; // book unique id
    char book_name[150]; // book name
    char book_author[100]; // book author
    char year_of_publish[50]; // Book published year
    char category[50]; // book category
    std::string categories[4] = {"General", "Literature", "Science", "Religion"}; // default categories

    friend class Utility; // Access to BookModel Schema
    friend class BACKEND; // Access to BookModel Schema

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

    // Input 
    void input(const char* filename){
        // Best; O(1)
        // Worst: O(n) We don't know how much time validation loop will iterate.

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
                std::cout << "Enter Year of Publish: ";
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
        // Best: O(1)
        // Worst: O(1)

        std::cout << "_id: " << unique_id << std::endl
                  << "Name: " << book_name << std::endl
                  << "Author: " << book_author << std::endl
                  << "Published: " << year_of_publish << std::endl
                  << "Category: " << category << std::endl;
    }

    // check if entered category match with the defined categories
    bool find_category(const char* str) const{
        // Best: O(1)
        // worst: O(1)
        for (int i = 0; i < 4; ++i){
            if(str == categories[i])
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
    int records_len(const char* filename){
        // Best: O(1)
        // Worst: O(1)// setup ifstream
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
    void writeToFile(const char* filename, const BookModel* books, int size){
        // Best: O(n)
        // Worst: O(n)

        try
        {
            // setup ofstream
            std::ofstream f(filename, std::ios::binary | std::ios::app | std::ios::out);

            if(!f.is_open()){ // if file is not available
                f.close();
                throw("Error: <file> Unable to open file to write ");
            } else { // if available
                for (int i = 0; i<size; ++i){
                    f.write((const char *)&books[i], sizeof(BookModel));
                }    
            }

            f.close(); // close file
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    // Read from file binary file
    void readFromFile(const char* filename, BookModel* books, int size){
        // Best: O(1)
        // Worst: O(1)

        try
        {
            // setup ifstream
            std::ifstream f;
            f.open(filename, std::ios::binary | std::ios::in);

            if(!f.is_open()){ // if file is not available
                f.close();
                throw("Error: <file> Unable to open file");
            } else { // if available
                f.read((char *)books, size * sizeof(BookModel)); // read file
                f.close(); // close file
            }
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    /*      Working with CSV Files        */

    // Get total records length from CSV file 
    int GetCSVLength(const char* filename){
        // Best: O(n)
        // Worst: O(n)
        
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
    void WriteToCSVFile(const char* filename, int size){
        // Best: O(n)
        // Worst: O(n)

        try
        {

            BookModel *books = new BookModel[size];
            readFromFile(filename, books, size); // read all records

            // setup ofstream to write records to csv file
            std::ofstream f("BooksModel.csv", std::ios::app);

            if(!f.is_open()) {
                f.close();
                delete[] books;
                books = nullptr;
                throw("Error: <file> Unable to open CSV file to write records");
            } else {

                int csv_file_size = GetCSVLength("BooksModel.csv"); // get records from csv file

                if(csv_file_size <= 0) { // headings
                    f << "_id,Name,Author,Published,Category" << std::endl;
                }

                // write to csv
                for (int i = 0; i < size; ++i) {
                    f << books[i].unique_id << "," << books[i].book_name << "," << books[i].book_author << "," << books[i].year_of_publish << "," << books[i].category << std::endl;
                }

                std::cout << "\nData Exported Successfully to CSV file" << std::endl;

                f.close();
                delete[] books;
            }

        }
        catch(const char *error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    // Read from CSV file
    void ReadFromCSVFile(const char* filename) {
        // Best: O(1)
        // Worst: O(1)

        std::ifstream f;
        f.open("BooksModel.csv");
        if(!f.is_open()){
            throw("Error: <file> Unable to open CSV file for reading");
        } else {

            int size = GetCSVLength("BooksModel.csv");
            if(size <= 0){
                throw("Error: <Invalid Size> Please first enter some records in CSV file");
            }

            BookModel *books = new BookModel[size];
            std::string temp;

            std::getline(f, temp); // read first line

            int i = 0;
            while(std::getline(f, temp, ',')){
                // read unique id
                books[i].unique_id = std::stoi(temp);

                // read book name
                std::getline(f, temp, ',');
                strcpy(books[i].book_name, temp.c_str());

                // read book author
                std::getline(f, temp, ',');
                strcpy(books[i].book_author, temp.c_str());

                // read year of publish
                std::getline(f, temp, ',');
                strcpy(books[i].year_of_publish, temp.c_str());

                // read category
                std::getline(f, temp);
                strcpy(books[i].category, temp.c_str());

                ++i;
            }

            // for (i = 0; i < size; ++i){
            //     books[i].display();
            // }

            writeToFile(filename, books, size); // write data to binary

            std::cout << "\nData Imported Successfully to Binary file" << std::endl; // screen message

            delete[] books;
            books = nullptr;
        }
    }

    // Utility Function: Convert String To LowerCase
    void toLowerCase(char* str) {
        for (int i = 0; str[i] != '\0'; ++i) {
            str[i] = std::tolower(str[i]); 
        }
    }

    /* FRONTEND MENUS */

    // welcome_page_menu
    void home_page_menu(const char* page_title) const{

        std::cout << page_title << std::endl; // Menu title

        // Menu Options
        std::cout << "1. Search a Book" << std::endl
                  << "2. View All Books" << std::endl
                  << "3. Contribute a Book" << std::endl
                  << "4. Update a Book" << std::endl
                  << "5. Delete a Book" << std::endl
                  << "6. Export Binary file data to CSV File" << std::endl
                  << "7. Import CSV file data to Binary File" << std::endl
                  << "8. Help" << std::endl
                  << "9. exit" << std::endl;
    }

    // search_page_menu
    void search_page_menu(const char* page_title) const{

        std::cout << page_title << std::endl; // Menu title

        // Menu Options
        std::cout << "1. Search a Book by Name" << std::endl
                  << "2. Search a Book by Category" << std::endl
                  << "3. Search a Book by Author Name" << std::endl
                  << "4. Back to Main Menu" << std::endl
                  << "5. Help" << std::endl
                  << "6. exit" << std::endl;

    }

    // help_page_menu
    void help_page_menu(const char* page_title) const{

        std::cout << page_title << std::endl; // Menu title

        // Menu Options
        std::cout << "1. About My Digital Library System" << std::endl
                  << "2. How can I use it?" << std::endl
                  << "3. List Contributors" << std::endl
                  << "4. View Source Code" << std::endl
                  << "5. View LICENSE" << std::endl
                  << "6. Back to Main Menu" << std::endl
                  << "7. exit" << std::endl;
    }

};

// Perform CURD operations & Application Logic
class BACKEND {
    Utility utils; // helper functions

public:

    /* Methods: GET | POST | PUT | DELETE */

    // GET RECORDS
    void GET(const char* filename){
        // Best: O(n)
        // Worst: O(n)
        int size = utils.records_len(filename);
        BookModel *books = new BookModel[size];
        try
        {
            utils.readFromFile(filename, books, size);
            std::cout << "\n\t All Library Books \n" << std::endl;
            for (int i = 0; i < size; ++i){
                books[i].display();
                std::cout << std::endl;
            }
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
        
        delete[] books; // free memory
        books = nullptr;
    }

    // POST RECORD
    void POST(const char* filename, int size)
    {
        if(size <= 0){
            throw("Error: <Invalid size> Invalid size for books contribution");
        } else {

            BookModel * books = new BookModel[size]; // allocate memory 

            try
            {
                for (int i = 0; i < size; ++i){
                    std::cout << std::endl; // for better readability in console
                    books[i].input(filename); // input records
                }

                utils.writeToFile(filename, books, size); // Write records to file

                std::cout << "Thank you for contributing to Digital Library" << std::endl
                          << "\nYour contributions were saved successfully!" << std::endl;
            }
            catch(const char* error)
            {
                std::cerr << error << std::endl;
            }

            delete[] books; // free memory
            books = nullptr;
        }
    }

    // PUT RECORD
    void PUT(const char* filename, int index, int size){

        BookModel *books = new BookModel[size]; // assign memory

        try
        {
            utils.readFromFile(filename, books, size); // read records

            std::cout << "\n\tRecord you want to update\n" << std::endl;
            books[index].display(); // show record before its get updated
            std::cout << std::endl;

            books[index].input(filename); // take new input 

            std::cout << "\n\tUpdated Record\n" << std::endl;
            books[index].display(); // show record after it get updated
            std::cout << std::endl;

            // setup ofstream to update file
            std::ofstream f;
            f.open(filename, std::ios::binary | std::ios::out | std::ios::trunc);

            if(!f.is_open()){
                f.close();
                throw("Error: <file> Unable to open file to update record"); // incase of file is not available
            } else{
                for (int i = 0; i < size; ++i) {
                    f.write((const char *)&books[i], sizeof(BookModel)); // write all records back to the file
                }
                f.close();
            }
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }

        delete[] books; // free memory
        books = nullptr;
    }

    // DELETE RECORD
    void DELETE(const char* filename, int index, int size){

        BookModel *books = new BookModel[size]; // assign memory

        try
        {
            utils.readFromFile(filename, books, size);

            // overwrite records
            for (int i = index; i < size - 1; ++i){
                books[i].unique_id = books[i + 1].unique_id;
                strcpy(books[i].book_name, books[i + 1].book_name);
                strcpy(books[i].book_author, books[i + 1].book_author);
                strcpy(books[i].year_of_publish, books[i + 1].year_of_publish);
                strcpy(books[i].category, books[i + 1].category);
            }

            --size; // Record deleted so decrement size

            std::ofstream f; // to overwrite the records leaving index record
            f.open(filename, std::ios::binary | std::ios::out); // open file

            if(!f.is_open()){ // if file is not available
                f.close();
                throw("Error: <file> Unable to open file");
            } else { // if file is available
                for (int i = 0; i < size; ++i)
                {   
                    // overwrite the records
                    f.write((const char *)&books[i], sizeof(BookModel));
                }
            }

            std::cout << "\nRecord deleted successfully"<< std::endl;
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
        
        delete[] books; // free memory
        books = nullptr;
    }

    /* Array Filter Methods */

    // Search by category
    void SearchByCategory(const char* filename, char *category){

            int size = utils.records_len(filename); // get length of available objects in file

            BookModel *books = new BookModel[size]; // allocate memory

            utils.readFromFile(filename, books, size); // read data

            bool currentState = true; // flag

            for (int i = 0; i < size; ++i){ // iterate over array

                // ignore cases
                utils.toLowerCase(category); 
                utils.toLowerCase(books[i].category);

                if(strcmp(category, books[i].category) == 0){ // filter based category
                    currentState = false; // set currentState to false if any record found
                    std::cout << std::endl; // formatting
                    books[i].display(); // only display matched records
                }
            }

            if(currentState){ // incase if there is no record available
                std::cout << "\nSorry! We couldn't find any record for query '" << category << "' "
                        << std::endl << "Please Try Search Again..." << std::endl;
            }

            delete[] books; // free memory
            books = nullptr;
    }

    // Search by book Name
    void SearchByBookName(const char* filename, char *book_title){

        int size = utils.records_len(filename); // get records size
        BookModel *books = new BookModel[size]; // allocate memory

        try
        {


            utils.readFromFile(filename, books, size); // read records

            bool currentState = true; // flag

            for (int i = 0; i < size; ++i){

                // ignore cases
                utils.toLowerCase(book_title);
                utils.toLowerCase(books[i].book_name);

                if(strcmp(book_title, books[i].book_name) == 0){
                    currentState = false; // set currentState to false any record found
                    std::cout << std::endl; // for formatting
                    books[i].display(); // display records
                    std::cout << std::endl;
                }
            }

            if(currentState){ // incase if there is no record available
                std::cout << "\nSorry! We couldn't find any record for query '" << book_title << "' "
                        << std::endl << "Please Try Search Again..." << std::endl;
            }

            delete[] books; // free memory
            books = nullptr;
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
            if(books != nullptr){
                delete[] books;
                books = nullptr;
            }
        }
        
    }

    // Search by Author Name
    void SearchByAuthorName(const char* filename, char *author_name){

            int size = utils.records_len(filename); // get total records

            BookModel *books = new BookModel[size]; // allocate memory

            utils.readFromFile(filename, books, size); // read records

            bool currentState = true; // flag 

            for (int i = 0; i < size; ++i){

                // ignore cases
                utils.toLowerCase(author_name);
                utils.toLowerCase(books[i].book_author);

                if(strcmp(author_name, books[i].book_author) == 0){ // compare author name
                    currentState = false; // set currentState to false any record found
                    std::cout << std::endl; // for formatting
                    books[i].display(); // display records
                }
            }

            if(currentState){ // incase if there is no record available
                std::cout << "\nSorry! We couldn't find any record for query '" << author_name << "'"
                        << std::endl << "Please Try Search Again..." << std::endl;
            }

            delete[] books; // free memory
            books = nullptr;
        }

};

// Render UI in console
class FRONTEND {
    BACKEND backend; // Application Logic
    Utility utils; // Reusable components/menus

public:

    void home_page(const char* filename, const char* menu_title)
    {
        utils.home_page_menu(menu_title); // Home page menu from Utility class
        int records_size = utils.records_len(filename); // get total records
        do{
            try
            {
                // input option and render data menu wise
                int option;
                std::cout << "\nEnter a option [1, 2, 3, 4, 5, 6, 7, 8, 9]: ";
                std::cin >> option;

                // terminate program incase of bad type error
                if(std::cin.fail()){ // bad type error
                    std::cout << "Error: <Invalid type> Program crashed due to invalid type"; // print exception message before program terminates
                    exit(0); // exist program
                }

                if(option <= 0 || option > 9){ // validate option
                    throw("Error: <Invalid option> Please enter valid option");
                } else { // perform actions 
                    switch (option)
                    {
                        case 1: // Search page
                            search_page(filename);
                            break;

                        case 2: // fetch all books records from file
                            backend.GET(filename);
                            break;

                        case 3: // Insert a new record
                            int n;
                            std::cout << "\nEnter no. of Books you want to contribute: ";
                            std::cin >> n;

                            // terminate program incase of bad type error
                            if(std::cin.fail()){ // bad type error
                                std::cout << "Error: <Invalid type> Program crashed due to invalid type"; // print exception message before program terminates
                                exit(0); // exist program
                            }

                            std::cin.ignore(); 
                            backend.POST(filename, n);
                            break;

                        case 4: // Update existing record

                                int index_to_update_record;
                                while (true)
                                {
                                    try
                                    {
                                        std::cout << "\nEnter Book index to update record: ";
                                        std::cin >> index_to_update_record;

                                        std::cin.ignore(); // 

                                        // terminate program incase of bad type error
                                        if(std::cin.fail()){ // bad type error
                                            std::cout << "Error: <Invalid type> Program crashed due to invalid type"; // print exception message before program terminates
                                            exit(0); // exist program
                                        }

                                        if(index_to_update_record < 0 || index_to_update_record > records_size){
                                            throw("Error: <Invalid Index> Please enter valid index to update record");
                                        } else {
                                            break;
                                        }
                                    }
                                    catch(const char *error)
                                    {
                                        std::cerr << error << std::endl;
                                    }
                                }
                                
                                backend.PUT(filename, index_to_update_record, records_size);

                            break;

                        case 5: // Delete a record

                                int index_to_delete_record;
                                while (true)
                                {
                                    try
                                    {
                                        std::cout << "\nEnter Book index to delete record: ";
                                        std::cin >> index_to_delete_record;

                                        std::cin.ignore(); // 

                                        // terminate program incase of bad type error
                                        if(std::cin.fail()){ // bad type error
                                            std::cout << "Error: <Invalid type> Program crashed due to invalid type"; // print exception message before program terminates
                                            exit(0); // exist program
                                        }

                                        if(index_to_delete_record < 0 || index_to_delete_record > records_size){
                                            throw("Error: <Invalid Index> Please enter valid index to update record");
                                        } else {
                                            break;
                                        }
                                    }
                                    catch(const char *error)
                                    {
                                        std::cerr << error << std::endl;
                                    }
                                }

                            backend.DELETE(filename, index_to_delete_record, records_size);

                            break;

                        case 6: // Write to CSV File
                            utils.WriteToCSVFile(filename, records_size);
                            break;

                        case 7:
                            utils.ReadFromCSVFile("BookModel.bin");
                            break;

                        case 8: // Show help i.e. how to use Application
                            help_page(filename);
                            break;

                        case 9: // Terminate program
                            std::cout << "\nThank You for using My Digital Library System" << std::endl;
                            exit(0);

                        default: // Throw exception incase of invalid option
                            throw("Error: <Invalid option> Please enter valid option");
                            break;
                    }
                }

                break; // get out of loop
            
            }
            catch(const char* error)
            {
                std::cerr << error << std::endl;
            }
            
        } while (true);
    }

    void search_page(const char* filename){
        do
        {
            try {
                    utils.search_page_menu("\n\tMy Digital Library Search System\n"); // display Search Menu
                    int option;
                    std::cout << "\nEnter a option [1, 2, 3, 4, 5]: ";
                    std::cin >> option;

                    // terminate program incase of bad type error
                    if(std::cin.fail()){
                        std::cout << "Error: <Invalid type> Program crashed due to invalid type"; // print exception before program terminates
                        exit(0); // exist program
                    }

                    std::cin.ignore(); 

                    if(option <= 0 || option > 6){
                        throw("Error: <Invalid option> Please enter valid option");
                    } else { // if everything goes well then run program

                        switch (option)
                        {
                            case 1: // case 1: Search by Book Name

                                char BookNameQuery[70];
                                std::cout << "\nEnter Book Name: ";
                                std::cin.getline(BookNameQuery, 70);
                                
                                backend.SearchByBookName(filename, BookNameQuery);

                                break;

                            case 2: // Case 2: Search by Category
                                char CategoryQuery[12];
                                std::cout << "\nEnter Category: ";
                                std::cin.getline(CategoryQuery, 12);

                                backend.SearchByCategory(filename, CategoryQuery);

                            break;
                            
                            case 3: // Case 3: Search by Author Name
                                char AuthorNameQuery[50];
                                std::cout << "\nEnter Author Name: ";
                                std::cin.getline(AuthorNameQuery, 50);
                                
                                backend.SearchByAuthorName(filename, AuthorNameQuery);

                            break;

                            case 4: // Case 4: Go back to main menu
                                home_page(filename, "\n\tWelcome Back to My Digital Library System\n");
                                break;

                            case 5: // help page
                                help_page(filename);
                                break;

                            case 6: // exit program
                                std::cout << "\nThank You for using My Digital Library System" << std::endl;
                                exit(0);

                            default: // Throw exception incase of invalid option
                                throw("Error: <Invalid option> Please enter valid option");
                                break;
                        }
                    }

                } 
                catch(const char* error) {
                    std::cerr << error << std::endl;
                }
                            
        } while (true);
                        
    }

    void help_page(const char* filename){

        while(true) {

            try
            {
                utils.help_page_menu("\n\tMy Digital Library Help Center\n"); // Page title

                // input option and render data menu wise
                int option;
                std::cout << "\nEnter a option [1, 2, 3, 4, 5, 6, 7]: ";
                std::cin >> option;

                // terminate program incase of bad type error
                if(std::cin.fail()){ // bad type error
                    std::cout << "Error: <Invalid type> Program crashed due to invalid type"; // print exception message before program terminates
                    exit(0); // exist program
                }

                if(option <= 0 || option > 8){ // validate option
                    throw("Error: <Invalid option> Please enter valid option");
                } else { // perform actions 

                    switch (option)
                    {
                        case 1: // About My Digital Library
                            std::cout << "\n\t About My Digital Library\n"
                                      << std::endl
                                      << "My Digital Library is a console based application built using C++. It includes various features such as: " << std::endl
                                      << "\n- Perform CURD Operations\n- Store Books Based on Categories\n- Search Books Based on Category, Author Name and Book Title\n- Smooth Architecture\n- Save Records with Unique ID's and more" << std::endl;
                            break;

                        case 2: // How I can use it?
                            std::cout << "\nTo use My Digital Library System, follow these steps:" << std::endl
                                      << "1. Navigate through the menu options to perform various operations." << std::endl
                                      << "2. Use the 'Search a Book' option to find books by name, category, or author." << std::endl
                                      << "3. Use the 'View All Books' option to see all the books in the library." << std::endl
                                      << "4. Use the 'Contribute a Book' option to add new books to the library." << std::endl
                                      << "5. Use the 'Update a Book' option to modify existing book records." << std::endl
                                      << "6. Use the 'Delete a Book' option to remove books from the library." << std::endl
                                      << "7. Use the 'Export Binary file data to CSV File' option to export data." << std::endl
                                      << "8. Use the 'Import CSV file data to Binary File' option to import data." << std::endl
                                      << "9. Use the 'Help' option for more information on how to use the system." << std::endl
                                      << "10. Use the 'exit' option to close the application." << std::endl;
                            break;

                        case 3: // List Contributors
                            std::cout << "\nContributors: (1)" << std::endl
                                    << "Saqib Bedar [GitHub: https://github.com/saqibbedar/]" << std::endl;
                            break;
                        
                        case 4: // View Source Code
                            std::cout << "\nSource Code: https://github.com/saqibbedar/digital-library" << std::endl;
                            break;

                        case 5: // View LICENSE
                            std::cout << "\nMIT LICENSE" << std::endl
                                    << "Copyright (c) 2024 Saqib Bedar" << std::endl;
                            break;

                        case 6: // Back to Main Menu
                            home_page(filename, "\n\tMy Digital Library Search System\n");
                            break;

                        case 7: // Terminate Program
                            std::cout << "\nThank You for using My Digital Library System" << std::endl;
                            exit(0);

                        default: // Throw exception incase of invalid option
                            throw("Error: <Invalid option> Please enter valid option");
                            break;
                    }
                }
            }

            catch(const char* error)
            {
                std::cerr << error << std::endl;
            }

        }
        
    }

};

void RunApp(const char* filename){ // main function to run whole application
    FRONTEND f;

    bool isFirstIteration = true; // to manage welcome_page title
    do
    { // Best O(n) // worst: O(n^4)
        try
        {
            if(isFirstIteration){
                f.home_page(filename, "\n\tWelcome to My Digital Library System\n");
                isFirstIteration = false;
            } else {
                f.home_page(filename, "\n\tMy Digital Library System Menu\n");
            }
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
    } while (true);
}

void handleFirstTimeRun(const char* filename){ // if BookModel.bin is empty or not available, this function would be executed
    std::cout << "\nWe couldn't find the "<< filename << " file." << std::endl
              << "Please enter a few records to interaction with our Digital Library System.\n" << std::endl;

    int records_size;
    do
    {
        std::cout << "Enter no. of books you want to contribute: ";
        std::cin >> records_size;
        if(std::cin.fail()){
            std::cout << "Error: <Invalid type> Program crashed due to invalid type" << std::endl;
            exit(0); // stop the program
        }
    } while (records_size <= 0);

    std::cin.ignore(); 

    BookModel *books = new BookModel[records_size];

    std::cout << "\n\tPlease Enter Book Details\n"<< std::endl;
    // input few records 
    for (int i = 0; i < records_size; i++)
    {
        books[i].input(filename);
    }

    Utility utils;

    utils.writeToFile(filename, books, records_size);

    delete[] books;
    books = nullptr;

    // Records saved successfully message
    std::cout << "\nThanks for contribution, records were saved successfully!" << std::endl;

    RunApp(filename); // now call the entry point function for interaction
}

int main(){
    const char filename[14] = "BookModel.bin"; // don't change extension of this file to other i.e., .csv etc

    Utility utils; // for records length

    int records_size = utils.records_len(filename); // get records size from BookModel.bin

    if(records_size <= 0)  { // Incase if there is no record or BookModel.bin is not available
        handleFirstTimeRun(filename);
    } else { // main entry point function
        RunApp(filename);
    }
    
    return 0;
}

// Check if a book id is already taken? 
bool FindByUID(const char* filename, int uid){
    // Best: O(1)
    // Worst: O(n)

    BookModel *books;
    Utility utils;

    // get total objects size from file
    int size = utils.records_len(filename);

    if(size <= 0){ // return false if there is no record available
        return false;
    }

    books = new BookModel[size];

    utils.readFromFile(filename, books, size);
    for (int i = 0; i < size; ++i){
        if(books[i].GetUID() == uid){
            delete[] books; // clean memory
            books = nullptr;
            return true;
        }
    }

    delete[] books; // clean memory
    books = nullptr;
    return false;
}
