std::string fix_spaces(std::string &str){
        for (int i = 0; i < str.length(); ++i){
        }
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