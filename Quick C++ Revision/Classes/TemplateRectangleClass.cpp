#include <iostream>
using namespace std;

template <class T>
class Rectangle
{
    T length, breadth;

public:
    Rectangle(T l, T b) : length(l), breadth(b) {};

    // facilitators
    T area();
    T perimeter();
    
    // Setters
    void setLength(T l){
        length = l;
    }
    void setBreadth(T b){
        breadth = b;
    }

    // Getters
    T getLength(){ return length; }
    T getBreadth(){ return breadth; }

    ~Rectangle(){}
};

template <class T>
T Rectangle <T>::area(){
    return length * breadth;
}

template <class T>
T Rectangle <T>::perimeter(){
    return 2 * (length + breadth);
}

int
main()
{
    Rectangle <int> r(10,20);
    cout<<r.perimeter()<<endl;
    return 0;
}