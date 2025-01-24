// Stack implementation using forward_list

#include <iostream>

/*
	Structure of list node:

		  node
	 --------------
	| value | next |
	 --------------

*/

// forward_list node
template <typename T>               
struct Node {
    T value; // value
    Node *next; // pointer to next node
    Node(T x) : value(x), next(nullptr) {} // constructor with direct initialization
};

// Stack ADT Class
template <typename T>
class stack{
    Node<T> *head; // Top pointer
    int n; // Total Nodes

public:
    stack(): head(nullptr), n(0){}

    void push(const T &val) {
        ++this->n;
        Node<T> *temp = new Node<T>(val); // todo: exception
        temp->next = head;
        head = temp;
    }

    void pop(){
        if(head == nullptr){
            throw("Stack underflow");
        }
        --this->n;
        Node<T> *temp = head; 
        head = head->next;
        delete temp; // free memory
    }

    T top() const{
        if(this->head == nullptr)
            throw("Stack underflow");
        return this->head->value;
    }

    bool empty() const{
        return this->head == nullptr;
    }

    int size() const{
        return this->n;
    }

    // Non-member functions
    template <typename F>
    friend bool operator!=(const stack<F>&, const stack<F>&);
    template <typename F>
    friend bool operator==(const stack<F>&, const stack<F>&);
    template <typename F>
    friend bool operator<(const stack<F>&, const stack<F>&);
    template <typename F>
    friend bool operator>(const stack<F>&, const stack<F>&);
    template <typename F>
    friend bool operator>=(const stack<F>&, const stack<F>&);

    void swap(stack&, stack&);

    void display(){
        Node<T> *temp = head;
        while(temp){
            std::cout << temp->value << std::endl;
            temp = temp->next;
        }
    }
};

template <typename T>
bool operator==(const stack<T> &lhs, const stack<T> &rhs){
    if(lhs.n != rhs.n){ // if nodes size is not equal
        return false;
    }

    Node<T> *l_head = lhs.head;
    Node<T> *r_head = rhs.head;

    while(l_head && r_head){
        if(l_head->value != r_head->value){
            return false;
        }
        l_head = l_head->next;
        r_head = r_head->next;
    }

    return true;
}

template <typename T>
bool operator!=(const stack<T> &lhs, const stack<T> &rhs){
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const stack<T> &lhs, const stack<T> &rhs){
    if (lhs == rhs) // if both are equal then return false directly
        return false;

    // if (lhs.n > rhs.n) // if left sides total nodes value is greater than return false
    //     return false;

    Node<T> *l_head = lhs.head;
    Node<T> *r_head = rhs.head;

    while(l_head && r_head){
        // check value by value
        if(l_head->value < r_head->value){
            return true;
        } else if( l_head->value > r_head->value){
            return false;
        }
        l_head = l_head->next;
        r_head = r_head->next;
    }

    return true;
}

template <typename T>
bool operator>(const stack<T> &lhs, const stack<T> &rhs){
    return !(lhs < rhs || lhs == rhs);
}

template <typename T>
bool operator>=(const stack<T> &lhs, const stack<T> &rhs){
    return (lhs > rhs || lhs == rhs);
}

template <typename T>
void stack<T>::swap(stack<T>& lhs, stack<T>& rhs){
    std::swap(lhs.head, rhs.head); // first swap the heads
    std::swap(lhs.n, rhs.n); // swap the total nodes value
}

int main(){
    try
    {
        stack<int> a;
        stack<int> b;

        if(a.empty()){
            std::cout << "Stack is empty" << std::endl;
        }

        a.push(1);
        a.push(2);
        a.push(3);

        b.push(1);
        b.push(2);
        b.push(3);

        std::cout <<"Stack A size: " << a.size() << std::endl;

        // equal to
        if(a == b){
            std::cout << "Equal" << std::endl;
        } else {
            std::cout << "Not Equal" << std::endl;
        }

        // not equal to
        if(a != b){
            std::cout << "Not Equal" << std::endl;
        } else {
            std::cout << "Equal" << std::endl;
        }

        // less than
        if(a < b){
            std::cout << "Stack A is less than B" << std::endl;
        } else {
            std::cout << "Stack A is not greater than B" << std::endl;
        }

        // greater than
        if(a > b){
            std::cout << "Stack A is greater than B" << std::endl;
        } else {
            std::cout << "Stack A is less than B" << std::endl;
        }

        // greater OR equal
        if( a >= b){
            std::cout << "True: A is greater or equal to B" << std::endl;
        } else {
            std::cout << "False: A is not or equal to B" << std::endl;
        }

        

        // remove some elements
        a.pop();
        a.pop();
        a.pop();

        std::cout <<"Stack A size: " << a.size() << std::endl;

    }
    catch(const char* msg)
    {
        std::cerr << msg << '\n';
    }
    
    return 0;
}