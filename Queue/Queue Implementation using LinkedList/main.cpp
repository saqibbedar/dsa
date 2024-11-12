#include <iostream>
using namespace std;

// Node 
class Node{
public:
    int val;
    Node *next;
    Node(int val = 0) : val(val), next(nullptr){}
};

class queue{
    Node *head;
    Node *tail;
    int n; // size of queue
    
public:
    queue(): n(0), head(nullptr), tail(nullptr) {}

    void push(int value) {

        Node *temp = new Node(value);
        
        if(head == nullptr){
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }

        ++n;
    }

    void pop() {

        if(head == nullptr){
            throw("Queue is underflow");
        }

        Node *temp = head->next; // temp points to next node
        delete head; // delete the head
        head = temp; // again set the head as starting 
        --n; // decrement n

    }

    int front() const {

        if(head == nullptr) {
            throw("Queue is underflow");
        }

        return head->val;
    }

    int back() const {

        if(tail == nullptr) {
            throw("Queue is underflow");
        }

        return tail->val;
    }

    int size() const {
        return n;
    }

    bool isEmpty() const {
        return n == 0;
    }

    // void clear(){

    //     Node *current = head;
    //     while (current != nullptr)
    //     {
    //         Node *next_node = current->next; // save next node addr
    //         delete current; // delete the current
    //         current = next_node; // point to the next node now, as first one deleted
    //     }

    //     // after clearing queue set member variable to original state
    //     head = nullptr;
    //     tail = nullptr;
    //     n = 0;
    // }

    void clear() {
        while (!isEmpty())
        {
            pop();
        }
    }

    void display() const {

        if(head == nullptr){
            throw("Queue is underflow");
        }

        Node *temp = head;

        std::cout << "[";
        while (temp != nullptr)
        {
            std::cout << temp->val;
            if(temp->next != nullptr) { // if it is equal to tail->val means last value
                std::cout << ", ";
            }
            temp = temp->next;
        }
        std::cout << "]\n";
        
    }

    void swap(queue &rhs){

        if(&rhs == this){
            return;
        }

        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        std::swap(n, rhs.n);

    }

    ~queue(){
        clear();
    }
};

int main(){
    try
    {
        queue q;
        q.push(1);
        q.push(2);
        q.push(3);

        q.display();
        q.pop();
        q.pop();

        q.display();

        q.push(1);

        std::cout << q.front() << std::endl;
        std::cout << q.back() << std::endl;

        queue r;
        r.swap(q);

        r.display();
        
        q.display();

    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }
    return 0;
}