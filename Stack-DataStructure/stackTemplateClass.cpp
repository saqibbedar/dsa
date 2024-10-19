#include <iostream>
using namespace std;

namespace my_stk {
    
    template <class T>
    class stack {
        private:
            T *stk;
            int size;
            int Top;
        public:
        stack(int s): size(s), Top(-1){
            stk = new T[size];
        }
        void push(T);
        void pop();
        T top() const;
        bool empty() const;
        ~stack();
    };

    template <class T>
    stack<T>::~stack(){
        delete[] stk;
    }

    template <class T>
    void stack<T>::push(T value){
        if(Top == size -1){
            std::cout << "Stack is Full";
        } else {
            Top++;
            stk[Top] = value;
        }
    }

    template <class T>
    void stack<T>::pop(){
        if(Top < 0){
            std::cout << "Stack is empty\n" << std::endl;
        } else {
            Top--;
        }
    }

    template <class T>
    T stack<T>::top() const{
        if(Top < 0){
            std::cout << "Stack is empty\n";
            return -1;
        } else {
            return stk[Top];
        }
    }

    template <class T>
    bool stack<T>::empty() const{
        return Top < 0;
    }
}

int main()
{
    my_stk::stack<int> stk(3);
    std::string str;
    std::cin >> str;

    for (int i = 0; i < str.length(); i++){
        if(str[i] == '('){
            stk.push(str[i]);
        } else if(str[i] == ')'){
            if(stk.empty() || stk.top() != '('){
                std::cout << "Brackets are not balanced." << std::endl;
            }
            stk.pop();
        }
    }
    if(!stk.empty()){
        std::cout << "Brackets are not balanced." << std::endl;
    } else {
        std::cout << "Brackets are balanced." << std::endl;
    }

    return 0;
}