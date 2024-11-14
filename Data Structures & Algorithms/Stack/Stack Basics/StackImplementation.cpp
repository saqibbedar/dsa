// This is a simple program to show the basic implementation of Stack, please refer to Stack Important Programs ⭐ folder, for detailed and commented code for stack implementation.

#include <iostream>

class stack {
    private:
        int *stk;
        int Top;
        int size;
    public:
        stack(int s):size(s){
            Top = -1;
            stk = new int[size];
        }
        void push(int);
        void pop();
        int top() const;
        bool empty() const;
        ~stack(){
            delete[] stk;
        }
};

void stack::push(int x){
    if(Top == size -1){
        std::cout << "Stack is Full";
    } else {
        Top++;
        stk[Top] = x;
    }
}

void stack::pop(){
    if (Top < 0) {
        std::cout << "Stack is Empty\n";
    } else {
        Top--;
    }
}

int stack::top() const{
    if (Top < 0) {
        std::cout << "Stack is Empty\n";
        return -1; 
    } else {
        return stk[Top];
    }
}

bool stack::empty() const{
    return Top < 0;
}

int main()
{
    // your code will go here...
    return 0;
}