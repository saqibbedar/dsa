#include <iostream>

template <typename T>
class Node {
    public:
    T value;
    Node *next;
    Node(T x=0): value(x), next(nullptr){}
};

int main()
{
    Node<int> *head, *tail;
    head = new Node<int>(1);
    tail = head;

    int arr[3] = {3, 5, 7};

    for(int x: arr){
        Node<int> *temp = new Node<int>(x);
        tail->next = temp; // Link the current tail to the new node
        tail = temp; // Move the tail to the new node
    }

    Node<int> *temp = head;
    while(temp != nullptr){
        std::cout << temp->value << " ";
        temp = temp->next;
    }
    
    return 0;
}