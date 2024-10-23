#pragma once
#include <iostream>

// stack implementation 
namespace my_stk {
    
    // stack implementation class
    template <typename T>
    class stack {
        private:
            T *stk; // Pointer to dynamically allocated array for stack elements
            int size; // Maximum size of the stack
            int Top; // Index of the top element in the stack
        
        public:
        // Constructor with default size of 100
        stack(int s = 100): size(s), Top(-1){ 
            stk = new T[size]; // Allocate memory for stack
        }
        
        // Member functions
        void push(T); // Push an element onto the stack
        void pop(); // Pop an element from the stack
        T top() const; // Get the top element of the stack
        bool empty() const; // Check if the stack is empty

        // Destructor
        ~stack(); // Destructor to free allocated memory

        // 
        stack& operator=(const stack<T> &) const;

        // Non-member function - friend function for equality comparison
        template <typename U>
        friend bool operator==(const stack<U>& lhs, const stack<U>& rhs);
    };

    template <typename T>
    stack<T>::stack(int s=100):size(s), Top(-1){
        stk = new T[size];
    }

    // Destructor
    template <typename T>
    stack<T>::~stack(){
        delete[] stk; // Free the allocated memory
    }

    // Push function
    template <typename T>
    void stack<T>::push(T value){
        if(Top == size -1){ // Check if stack is full
            std::cout << "Stack is Full";
        } else {
            Top++; // Increment top index
            stk[Top] = value; // Add value to the stack
        }
    }

    // Pop function
    template <typename T>
    void stack<T>::pop(){
        if(Top < 0){ // Check if stack is empty
            std::cout << "Stack is empty\n";
        } else {
            Top--; // Decrement top index
        }
    }

    // Top function
    template <typename T>
    T stack<T>::top() const{
        if(Top < 0){ // Check if stack is empty
            std::cout << "Stack is empty\n";
            return -1; // Return -1 if stack is empty
        } else {
            return stk[Top]; // Return the top element
        }
    }

    // Empty function 
    template <typename T>
    bool stack<T>::empty() const{
        return Top < 0; // Return true if stack is empty
    }

    template <typename T>
    stack<T>& stack<T>::operator=(const stack<T>& rhs) const{
        if(this != &rhs){
            delete[] stk;
            size = rhs.size;
            Top = rhs.Top;
            stk = new T[size];
            for (int i = 0; i < Top; i++){
                stk[i] = rhs.stk[i];
            }
            return *this;
        }
    }

    // Non-member function for equality comparison
    template <typename T>
    bool operator==(const stack<T>& lhs, const stack<T>& rhs){
        if(lhs.size != rhs.size || lhs.Top != rhs.Top) // Check if sizes or top indices are different
            return false;
        for (int i = 0; i <= lhs.Top; ++i){ // Compare elements of both stacks
            if(lhs.stk[i] != rhs.stk[i])
                return false;
        }
        return true; // Return true if all elements are equal
    }
}
