// Program to check if brackets are balanced or not, using STL stack.

#include <iostream>
#include <stack> // using STL stack
#include <string>

int main()
{
    std::stack<char> stk;
    std::string str;
    std::cin >> str;

    for (int i = 0; i < str.length(); i++){
        if(str[i] == '('){
            stk.push(str[i]);
        } else if(str[i] == ')'){
            if(stk.empty() || stk.top() != '('){
                std::cout << "Brackets are not balanced." << std::endl;
                return 0;
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