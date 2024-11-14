#include <iostream>
#include <fstream>
#include <cstring>

struct book {
    int id;
    char title[50];
    
    book(int i = 0, const char* t = ""): id(i) {
        strcpy(title, t);
    }

    void display() const {
        std::cout << id << " " << title << std::endl;
    }
};

int main() {
    book b1(1, "Book 1");
    std::fstream f("book.bin", std::ios::binary | std::ios::out | std::ios::in);

    for (int i = 0; i < 10; ++i){
    f.seekg(0); // Seek to the beginning of the file
    }

    book b;
    f.seekg(sizeof(book));
    f.read((char *)&b, sizeof(b));
    b.display();

    return 0;
}