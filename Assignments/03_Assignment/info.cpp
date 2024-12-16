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
struct BookModel {
    // Book schema
    int unique_id; // book unique id
    char book_name[150]; // book name
    char book_author[100]; // book author
    char year_of_publish[50]; // Book published year
    char category[50]; // book category
    char categories[4][12] = {"General", "Literature", "Science", "Religion"}; // default categories

    // constructor
    BookModel(int uid=0, const char* bn="", const char* author="", const char* yop="", const char* category=""){
        this->unique_id = uid;
        strcpy(book_name, bn);
        strcpy(book_author, author);
        strcpy(year_of_publish, yop);
        strcpy(this->category, category);
    };

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
            return 0;
        } else {
            while (std::getline(f, line)) {
                ++size;
            }
            f.close();
            return size - 1; // -1 for first line data headings
        }
    }

    // write to CSV file
    void readFromBinaryAndWriteToCSV(const char* filename, int size)
    {
        try
        {
            std::forward_list<BookModel> books;
            readFromBinaryFile(filename, books, size); // read all records

            // setup ofstream to write records to csv file
            std::ofstream f("BookModel.csv", std::ios::app);

            if(!f.is_open()) {
                throw("Error: <file> Unable to open CSV file to write records");
            } else {

                int csv_file_size = getCSVFileLength("BookModel.csv"); // get records from csv file

                if(csv_file_size <= 0) { // headings
                    f << "_id,Name,Author,Published,Category" << std::endl;
                }

                std::forward_list<BookModel>::iterator it;

                // write to csv
                for (it = books.begin(); it != books.end(); ++it)
                {
                    f << it->unique_id << "," << it->book_name << "," << it->book_author << "," << it->year_of_publish << "," << it->category << std::endl;
                }

                std::cout << "\nData exported to CSV file, successfully." << std::endl;

                f.close();
            }

        }
        catch(const char *error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    // Read from CSV file
    void readFromCSVFileAndWriteToBinary(const char* filename) {
        std::ifstream f;
        f.open("BookModel.csv");
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

            std::cout << "\nData imported to Binary file, successfully." << std::endl; // screen message
        }
    }

    /*      Hello       */
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
                  << "4. View Arguments List" << std::endl
                  << "5. View Source Code" << std::endl
                  << "6. View LICENSE" << std::endl
                  << "7. Back to Main Menu" << std::endl
                  << "8. exit" << std::endl;
    }

    void argumentsList() const{
        std::cout << "1. ls args (list arguments)" << std::endl
                  << "2. help or --help (goto help page)" << std::endl
                  << "3. home (goto homepage)" << std::endl
                  << "4. search (goto search page)" << std::endl
                  << "5. idata (idata: import data - It imports records from csv file to binary file - only if CSV file exits)" << std::endl
                  << "6. edata (edata: export data - It writes records to CSV file)" << std::endl
                  << "7. exit (terminate program)" << std::endl;
    }
};

// Perform CURD operations & Application Logic
class BACKEND {
    Utility utils; // helper functions

public:

    /* Methods: GET | POST | PUT | DELETE */

    // GET RECORDS
    void GET(const char* filename){
        int size = utils.getBinaryFileLength(filename);
        std::forward_list<BookModel> books;
        try
        {
            utils.readFromBinaryFile(filename, books, size);
            std::cout << "\n\t All Library Books \n" << std::endl;
            for (std::forward_list<BookModel>::iterator it = books.begin(); it != books.end(); ++it)
            {
                it->display();
                std::cout << std::endl;
            }
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
    }

    // POST RECORD
    void POST(const char* filename, int size)
    {
        if(size <= 0){
            throw("Error: <Invalid size> Invalid size for books contribution");
        } else {
            std::forward_list<BookModel> books;
            try
            {
                for (int i = 0; i < size; ++i)
                {
                    BookModel book;
                    std::cout << std::endl; // for better readability in console
                    book.input(filename); // input records
                    books.push_front(book);
                }

                utils.writeToBinaryFile(filename, books, size); // Write records to file

                std::cout << "Thank you for contributing to Digital Library" << std::endl
                          << "\nYour contributions were saved successfully!" << std::endl;
            }
            catch(const char* error)
            {
                std::cerr << error << std::endl;
            }
        }
    }

    // PUT RECORD
    void PUT(const char* filename, int index, int size){

        std::forward_list<BookModel> books;

        try
        {
            std::cout << "Reading from binary file..." << std::endl;
            utils.readFromBinaryFile(filename, books, size); // read records

            // get the index
            std::forward_list<BookModel>::iterator it = books.begin();
            int currentIndex = 0; // for currentIndex 

            while (it != books.end())
            {
                if(currentIndex == index){
                    std::cout << "\n\tRecord you want to update\n" << std::endl;
                    it->display(); // show record before its get updated
                    std::cout << std::endl;
                    it->input(filename); // take new input 
                    std::cout << "\n\tUpdated Record\n" << std::endl;
                    it->display(); // show record after it get updated
                    std::cout << std::endl;
                    break;
                }
                ++currentIndex;
                ++it;
            }

            if (currentIndex != index) {
                throw("Error: <index> Index out of bounds");
            }

            // setup ofstream to update file
            std::ofstream f(filename, std::ios::binary | std::ios::out | std::ios::trunc);

            if(!f.is_open()){
                throw("Error: <file> Unable to open file to update record"); // incase of file is not available
            } else{ // write all records back to file
                utils.writeToBinaryFile(filename, books, size);
            }
            f.close();
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
    }

    // DELETE RECORD
    void DELETE(const char* filename, int index, int size){

        std::forward_list<BookModel> books;

        try
        {
            utils.readFromBinaryFile(filename, books, size);

            // set iterator for correct index
            std::forward_list<BookModel>::iterator it = books.begin();
            int currentIndex = 0;

            while(it != books.end()){
                if(currentIndex == index) {
                    books.pop_front();
                }
                ++currentIndex;
                ++it;
            }

            std::ofstream f; // to overwrite the records leaving index record
            f.open(filename, std::ios::binary | std::ios::out); // open file

            if(!f.is_open()){ // if file is not available
                throw("Error: <file> Unable to open file");
            } else { // if file is available
                utils.writeToBinaryFile(filename, books, size-1); // again write size - 1 records
            }

            std::cout << "\nRecord deleted successfully"<< std::endl;
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
    }

    /* Array Filter Methods */

    // Search by category : make sure to pass category as lowercase when calling to this function
    void SearchByCategory(const char* filename, const char *category){

            int size = utils.getBinaryFileLength(filename); // get length of available objects in file

            std::forward_list<BookModel> books; // allocate memory

            utils.readFromBinaryFile(filename, books, size); // read data

            bool currentState = true; // flag

            for (std::forward_list<BookModel>::iterator it = books.begin(); it != books.end(); ++it)
            { // iterate over list
            
                // ignore cases
                utils.toLowerCase(it->category);

                if(strcmp(category, it->category) == 0){ // filter based category
                    currentState = false; // set currentState to false if any record found
                    std::cout << std::endl; // formatting
                    it->display(); // only display matched records
                }
            }

            if(currentState){ // incase if there is no record available
                std::cout << "\nSorry! We couldn't find any record for query '" << category << "' "
                        << std::endl << "Please Try Search Again..." << std::endl;
            }
    }

    // Search by book Name : pass category as a lowercase when calling this function
    void SearchByBookName(const char* filename, const char *book_title){

        int size = utils.getBinaryFileLength(filename); // get records size
        std::forward_list<BookModel> books;

        try
        {
            utils.readFromBinaryFile(filename, books, size); // read records

            bool currentState = true; // flag

            for (std::forward_list<BookModel>::iterator it = books.begin(); it != books.end(); ++it)
            {
                utils.toLowerCase(it->book_name);
                if(strcmp(book_title, it->book_name) == 0){
                    currentState = false; // set currentState to false any record found
                    std::cout << std::endl; // for formatting
                    it->display(); // display records
                    std::cout << std::endl;
                }
            }

            if(currentState){ // incase if there is no record available
                std::cout << "\nSorry! We couldn't find any record for query '" << book_title << "' "
                        << std::endl << "Please Try Search Again..." << std::endl;
            }
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
        
    }

    // Search by Author Name : make sure to pass author_name in lowercase while calling this function
    void SearchByAuthorName(const char* filename, const char *author_name){
            int size = utils.getBinaryFileLength(filename); // get total records
            std::forward_list<BookModel> books;

            utils.readFromBinaryFile(filename, books, size); // read records

            bool currentState = true; // flag

            for (std::forward_list<BookModel>::iterator it = books.begin(); it != books.end(); ++it)
            {
                // ignore cases
                utils.toLowerCase(it->book_author);

                if(strcmp(author_name, it->book_author) == 0){ // compare author name
                    currentState = false; // set currentState to false any record found
                    std::cout << std::endl; // for formatting
                    it->display(); // display records
                }
            }

            if(currentState){ // incase if there is no record available
                std::cout << "\nSorry! We couldn't find any record for query '" << author_name << "'"
                        << std::endl << "Please Try Search Again..." << std::endl;
            }
        }
};

class FRONTEND {
    BACKEND backend; // Application Logic
    Utility utils; // Reusable components/menus

public:

    void home_page(const char* filename, const char* menu_title)
    {
        utils.home_page_menu(menu_title); // Home page menu from Utility class
        int records_size = utils.getBinaryFileLength(filename); // get total records
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
                            utils.readFromBinaryAndWriteToCSV(filename, records_size);
                            break;

                        case 7:
                            utils.readFromCSVFileAndWriteToBinary("BookModel.bin");
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

                                utils.toLowerCase(BookNameQuery); // to lowercase to ignore case in search

                                backend.SearchByBookName(filename, BookNameQuery);

                                break;

                            case 2: // Case 2: Search by Category
                                char CategoryQuery[12];
                                std::cout << "\nEnter Category: ";
                                std::cin.getline(CategoryQuery, 12);

                                utils.toLowerCase(CategoryQuery); // to lowercase to ignore case in search

                                backend.SearchByCategory(filename, CategoryQuery);

                            break;
                            
                            case 3: // Case 3: Search by Author Name
                                char AuthorNameQuery[50];
                                std::cout << "\nEnter Author Name: ";
                                std::cin.getline(AuthorNameQuery, 50);

                                utils.toLowerCase(AuthorNameQuery); // to lowercase to ignore case in search

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
                std::cout << "\nEnter a option [1, 2, 3, 4, 5, 6, 7, 8]: ";
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
                        case 1: // About My Digital Library
                            std::cout << "\n\t About My Digital Library\n"
                                      << std::endl
                                      << "My Digital Library is a console based application built using C++. It uses forward_list data structure to store the records data in binary files and also give flexibility to user to export the data from binray to csv and vice-versa. Furthermore, it also provides various command line arguments to interact with application. It includes various features such as: " << std::endl
                                      << "\n- Perform CURD Operations\n- Store Books Based on Categories\n- Search Books Based on Category, Author Name and Book Title\n- Smooth Architecture\n- Save Records with Unique ID's and more" << std::endl;
                            break;

                        case 2: // How I can use it?
                            std::cout << "\n\t To use My Digital Library System, follow these steps:\n" << std::endl
                                      << "0. Use command line arguments to perform quick task easily i.e., import, export of files etc." << std::endl
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
                        
                        case 4: // list arguments
                            std::cout << "\n\t My Digital Library Arguments List\n" << std::endl;
                            utils.argumentsList();
                            break;
                        
                        case 5: // View Source Code
                            std::cout << "\nSource Code: https://github.com/saqibbedar/digital-library" << std::endl;
                            break;

                        case 6: // View LICENSE
                            std::cout << "\nMIT LICENSE" << std::endl
                                    << "Copyright (c) 2024 Saqib Bedar" << std::endl;
                            break;

                        case 7: // Back to Main Menu
                            home_page(filename, "\n\tMy Digital Library Search System\n");
                            break;

                        case 8: // Terminate Program
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
    std::cout << "\n\t\tWe couldn't find the '"<< filename << "' file." << std::endl
              << "Please enter few records to start interaction with My Digital Library System.\n" << std::endl;

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

    std::forward_list<BookModel> books;

    std::cout << "\n\tPlease Enter Book Details\n"<< std::endl;
    // input few records 
    for (int i = 0; i < records_size; i++)
    {
        BookModel book;
        book.input(filename);
        books.push_front(book);
    }

    Utility utils;

    utils.writeToBinaryFile(filename, books, records_size);

    // Records saved successfully message
    std::cout << "\nThanks for contribution, records were saved successfully!" << std::endl;

    RunApp(filename); // now call the entry point function for interaction
}

// If arguments are passed then handle them
void argumentsHandler(const char *filename, int records_size, int argc, char* argv[]){
    FRONTEND frontend; // to show fronted pages
    Utility utils; // to show menus i.e., argumentsList etc
    for (int i = 1; i < argc; ++i){
        if (strcmp("ls", argv[i]) == 0 && strcmp("args", argv[i+1]) == 0) { // list all arguments
            utils.argumentsList(); // show arguments list
            break; // break after displaying the arguments list to user
        } else if(strcmp("--help", argv[i]) == 0 || strcmp("help", argv[i]) == 0) { // show help page
            frontend.help_page(filename);
            break;
        } else if(strcmp("idata", argv[i]) == 0) { // idata: (import data) write csv data to binary file
            std::ifstream file("BookModel.csv");
            if(file.is_open()){
                utils.readFromCSVFileAndWriteToBinary("BookModel.csv");
                frontend.home_page(filename, "\n\tWelcome to My Digital Library System\n");
                break;
            }else {
                std::cout << std::endl << "Error: <invalid argument> Please enter valid argument\n" << std::endl
                        << "\t View arguments list below and pass correct one: \n" << std::endl;
                utils.argumentsList();
                std::cout << std::endl;
            }
        } else if (strcmp("edata", argv[i]) == 0){ // edata: (export data) write binary file data to csv
            utils.readFromBinaryAndWriteToCSV(filename, records_size);
            frontend.home_page(filename, "\n\tWelcome to My Digital Library System\n");
            break;
        } else if (strcmp("search", argv[i]) == 0){ // open search page
            frontend.search_page(filename);
            break;
        } else if (strcmp("home", argv[i]) == 0) { // open home page
            frontend.home_page(filename, "\n\tWelcome to My Digital Library System\n");
            break;
        } else if (strcmp("exit", argv[i]) == 0) { // terminate program
            exit(0);
        } else {
            std::cout << std::endl << "Error: <invalid argument> Please enter valid argument\n" << std::endl
                      << "\t View arguments list below and pass correct one: \n" << std::endl;
            utils.argumentsList();
            std::cout << std::endl;
            break;
        }
    }
}

/*
    Note: This program supports arguments only if the BookModel.bin file exist means you should have few records initially to work with CLI arguments
*/
int main(int argc, char *argv[]){

    const char filename[14] = "BookModel.bin"; // don't change extension of this file to other i.e., .csv etc
    
    Utility utils; // for records length in binary file
    int records_size = utils.getBinaryFileLength(filename); // get records size from BookModel.bin

    bool flag = argc > 1 ? true : false; // If arguments are passed then true else false

    if(flag && records_size > 0){
        argumentsHandler(filename, records_size, argc, argv); // handle arguments if passed
    } else {
        if(records_size <= 0)  { // Incase if there is no record or BookModel.bin is not available
            handleFirstTimeRun(filename);
        } else { // main entry point function
            RunApp(filename);
        }
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
        if(it->unique_id == uid){
            return true;
        }
    }

    return false;
}
