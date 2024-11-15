/*

Name: Muhammad Saqib
RegNo: 037
Semester: 3rd

Task 1: A palindrome is a string which reads the same from left to right or right to left, e.g,. madam, tallat, 121, etc. Write a function (client code) which takes a string as input and tells whether the string is a palindrome or not? Think how you can use a stack and a queue to solve this problem. For implementation, use the stack and queue classes from STL

*/

#include <iostream>
#include <stack>
#include <queue>
#include <string>

bool isPalindrome(const std::string str){

    std::stack<char> stk;
    std::queue<char> q;

    for (int i = 0; i < str.length(); ++i) {
        stk.push(str[i]);
        q.push(str[i]);
    }

    for (int i = 0; i < str.length(); ++i) {
        if(stk.top() != q.front()){
            return false;
        }
        stk.pop();
        q.pop();
    }

    return stk.empty() && q.empty();
}

int main(int argc, char *argv[]){

    std::string str; // get input from CLI

    for (int i = 1; i < argc; ++i){
        str += argv[i]; // store input char by char
    }

    if (isPalindrome(str)) // check palindrome
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }

    return 0;
}