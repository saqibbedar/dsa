#include <iostream>

template <typename T>
class Node {
public:
    T val;
    Node* next;
    Node(T x): val(x), next(nullptr){}
};

template <typename T>
class LinkedList{
    Node *head, *tail;
    int size;

public:

    LinkedList() : head(nullptr), tail(nullptr) {}

    // Functions similar to those in std::list
    void push_back(T val);
    void push_front(T val);
    void pop_back();
    void pop_front();
    T front();
    T back();
    int getSize() const;
    bool empty() const;
    void insert(int index, T val);
    void erase(int index);
    void clear();
    void display() const;

    ~LinkedList();
};

int main(){

    return 0;
}