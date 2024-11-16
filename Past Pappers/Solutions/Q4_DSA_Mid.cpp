// infix to postfix

#include <iostream>
#include <stack>
#include <string>

// check precedence
int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    if(op == '^') return 3;
    return 0;
}

int main(){
    // std::string str = "(4 + 2 * 7) - (8 * 5 / 6 + 1) / 3";
    std::string str;
    std::cout << "Enter infix expression: ";
    std::getline(std::cin, str); // input expression

    std::string output = "";
    std::stack<char> stk;

    for (int i = 0; i < str.length(); ++i){
        if(str[i] == ' '){ 
            continue; // ignore spaces
        }else if((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')){
            output += str[i]; // if number or alphabet then put into ouput
        } else if(str[i] == '^'){
            stk.push(str[i]);
        } else if(str[i] == '(') {
            stk.push(str[i]); // push ( bracket
        } else if(str[i] == ')') { // until we don't get ) bracket put operators into output and remove the operators from stack
             while (!stk.empty() && stk.top() != '(') {
                output += stk.top();
                stk.pop();
            }
            if (!stk.empty() && stk.top() == '(') { // check if still ( is there then remove it
                stk.pop();
            }
        } else { // work with operators
            while (!stk.empty() && precedence(stk.top()) >= precedence(str[i])) {
                output += stk.top();
                stk.pop();
            }
            stk.push(str[i]);
        }
    }

    // clear stack and append remaining elements to output
    while (!stk.empty())
    {
        output += stk.top();
        stk.pop();
    }
    

    std::cout << "Output: " << output << std::endl;

    return 0;
}