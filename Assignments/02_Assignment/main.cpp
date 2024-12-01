#include <iostream>
#include <stack>
#include <string>

// hold utility functions
class Utility{
public:
    // check precedence
    int precedence(char op) {
        if(op == '+' || op == '-') return 1;
        if(op == '*' || op == '/') return 2;
        if(op == '^') return 3;
        return 0;
    }

    // check if brackets are balanced or not
    bool check_brackets_balanced(std::string &str){
        std::stack<char> stk;
        for (int i = 0; i < str.length(); ++i){
            if(str[i] == '('){
                stk.push(str[i]);
            } else if(str[i] == ')') {
                if(stk.empty() || stk.top() != '('){
                    return false;
                }
                stk.pop();
            }
        }

        if(!stk.empty()){
            return false;
        } else {
            return true;
        }
    }

    // handle operators validation
    bool validate_operators(std::string &str) {
        for (int i = 0; i < str.length(); ++i){
            if(str[i] >= '0' && str[i] <= '9' || str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == ' ' || str[i] == '(' || str[i] == ')' || str[i] == '"'){
                continue;
            } else {
                return false;
            }
        }
        return true;
    }

    // fix spaces for final postfix_expression
    std::string fix_spaces(std::string &str){
        std::string result;
        bool tell_previous_space = false;
        for (int i = 0; i < str.length(); ++i){
            if (str[i] == ' '){
                if (!tell_previous_space){
                    result += str[i];
                    tell_previous_space = true;
                }
            } else {
                result += str[i];
                tell_previous_space = false;
            }
        }
        return result;    
    }

    // convert infix to postfix expression
    std::string infix_to_postfix(std::string &str){ 
        if(check_brackets_balanced(str) && validate_operators(str)){
            std::string output = ""; // for printing postfix expression
            std::stack<char> stk; // hold stack based values for infix to postfix conversion

            for (int i = 0; i < str.length(); ++i){
                if(str[i] == '"'){
                    continue;
                }else if(str[i] == ' '){
                    output += str[i]; // include spaces too
                    // continue;
                }
                else if((str[i] >= '0' && str[i] <= '9')){
                    output += str[i]; // if number or alphabet then put into output
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

            output = fix_spaces(output);

            return output; // return final output

        } else {
            throw("Error: invalid expression");
        }
    }

    // evaluate sum
    int evaluate_postfix_expression(std::string &str){
        std::stack<int> stk; // store operands
        int temporay_number_holder = 0;
        bool flag = false; // check if we are working with number?
        
        for (int i = 0; i < str.length(); ++i) {
            if (str[i] >= '0' && str[i] <= '9') { 
                temporay_number_holder = temporay_number_holder * 10 + (str[i] - '0');
                flag = true;
            } else if (str[i] == ' ' && flag) {// if space push num to stack
                stk.push(temporay_number_holder);
                temporay_number_holder = 0; // Reset for next number
                flag = false;
            } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
                // If the character is an operator, pop two operands, apply the operator, and push the result
                int operand2 = stk.top(); stk.pop();
                int operand1 = stk.top(); stk.pop();
                
                int result = 0;
                if (str[i] == '+') {
                    result = operand1 + operand2;
                } else if (str[i] == '-') {
                    result = operand1 - operand2;
                } else if (str[i] == '*') {
                    result = operand1 * operand2;
                } else if (str[i] == '/') {
                    result = operand1 / operand2;
                }
                stk.push(result); // Push the result back onto the stack
            }
        }

        // After processing all tokens, the result should be the only element in the stack
        return stk.top();
    }
};

// Controls application logic
class Controller{
    Utility utils;
public:

    void RunApp(int size, char *arguments[]){
        std::string str;
        try
        {
            if(size > 1){
                for (int i = 1; i < size; i++)
                {
                    str = ""; // refresh it after each iteration
                    str += arguments[i];
                    str = utils.infix_to_postfix(str);
                    std::cout << "Posfix Expression: " << str << std::endl;
                    std::cout << "Expression Result: " << utils.evaluate_postfix_expression(str) << std::endl;
                }
            } else {
                std::cout << "\n\t" << "Command Line Calculator\n" << std::endl;
                std::cout << "Please enter expression string type expression: ";
                std::getline(std::cin, str);
                str = utils.infix_to_postfix(str);
                std::cout << "Posfix Expression: " << str << std::endl;
                std::cout << "Expression Result: " << utils.evaluate_postfix_expression(str) << std::endl;
            }
        }
        catch(const char* error)
        {
            std::cerr << error << std::endl;
        }
    }

};

int main(int argc, char *argv[]){
    Controller controller;
    controller.RunApp(argc, argv);
    return 0;
}
