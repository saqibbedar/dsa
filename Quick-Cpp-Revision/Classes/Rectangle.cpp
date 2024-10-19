#include <iostream>
using namespace std;

class Rectangle
{
    int length, breadth;

public:
    Rectangle(int l, int b) : length(l), breadth(b) {};

    // facilitators
    int area();
    int perimeter();
    
    // Setters
    void setLength(int l){
        length = l;
    }
    void setBreadth(int b){
        breadth = b;
    }

    // Getters
    int getLength(){ return length; }
    int getBreadth(){ return breadth; }

    ~Rectangle(){}
};

int Rectangle::area(){
    return length * breadth;
}

int Rectangle::perimeter(){
    return 2 *(length + breadth);
}

int
main()
{
    Rectangle r(10,20);
    cout<<r.perimeter()<<endl;
    return 0;
}