// Write a function which takes a stack as parameter and reverse it

#include <iostream>
#include <stack>
#include <queue>

template <typename T>
void reverse_stack(std::stack<T>& stk){

    std::queue<T> q;

    while (!stk.empty())
    {
        q.push(stk.top());
        stk.pop();
    }
    
    while (!q.empty())
    {
        stk.push(q.front());
        q.pop();
    }

}

template <typename T>
void display(std::stack<T> stk){

    while (!stk.empty())
    {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    
}

int main(){

    std::stack<int> stk;
    
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);

    std::cout << "before reverse: ";
    display(stk);
    std::cout << std::endl;

    reverse_stack(stk);

    std::cout << "After reverse: ";
    display(stk);

    return 0;
}