#include <iostream>
#include <fstream>
#include <string>
#include <stack>

void Q1(){

    /* 
    
    Write code for a program which reads a CSV file having 3 columns containing numeric values. The program should display the sum of each row. Sample inputs and outputs are given below, actual input may contain any number of rows.

    */

   std::ifstream f("file.csv");
   std::string temp;
   int sum = 0;

   if (f.is_open())
   {

       std::getline(f, temp, '\n'); // ignore heading

       while (f.good())
       {
            std::getline(f, temp, ',');
            sum += std::stoi(temp);
            std::getline(f, temp, ',');
            sum += std::stoi(temp);
            std::getline(f, temp, ',');
            sum += std::stoi(temp);

            std::cout << "Sum of Row: " << sum << std::endl;

            sum = 0; // again make it zero for next iteration
       }
    } else {
        throw("Error <file> Unable to open file");
    }

}

void Q2(std::string str){

    /*

    Write code for a program which takes a string as input and checks whether the brackets in the string are balanced or not. In case the brackets are not balanced, the program should display the reason of unbalanced brackets.

    */

    std::stack<char> stk;

    for (int i = 0; i < str.length(); ++i){
        if(str[i] == '('){
            stk.push(str[i]);
        } else if(str[i] == ')') {
            if(stk.empty() || stk.top() != '('){
                std::cout << "Unbalanced\n";
                return;
            }
            stk.pop();
        }
    }

    if(!stk.empty()){
        std::cout << "Unbalanced\n";
    } else{
        std::cout << "Balanced\n";
    }
}



int main(){
    return 0;
}