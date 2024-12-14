#include <iostream>

template <typename T>
class Node {
public:
    T val;
    Node* next;
    Node(T x): val(x), next(nullptr){}
};

template <typename T>
class list{
    Node *head, *tail;
    int size;

public:

    list() : size(0), head(nullptr), tail(nullptr) {}

    void push_back(T val){ // Add new element to the end of the linked list

        Node<T> *temp = new Node<T>(val); // create a new node with given value

        if(tail == nullptr){
            head = temp;
            tail = temp;
        } else {
            tail->next = temp; // connect new to the tail next
            tail = temp;
        }

        ++size;
    }

    void push_front(T val){ // Add a new element to the beginning of the linked list

        Node<T> *temp = new Node<T>(val);

        if(head == nullptr){ // incase if it is the first element
            head = temp;
            tail = temp;
        } else {
            temp->next = head;
            head = temp;
        }

        ++size;
    }

    void pop_back() {
        if(tail == nullptr){
            throw("List underflow");
        }

        Node<T> *temp = head; // save the last node to temp

        while (temp != nullptr)
        {
            if(temp->next == tail){ // find the node before the tail
                delete tail;
                tail = temp;
                tail->next = nullptr;
                temp->next = nullptr; // this will also break the loop;
                break;
            }
            temp = temp->next;
        }

        --size;
    }
    void pop_front();
    T front();
    T back();
    int getSize() const;
    bool empty() const;
    void insert(int index, T val);
    void erase(int index);
    void clear();
    void display() const;

    ~list();
};

int main(){

    return 0;
}