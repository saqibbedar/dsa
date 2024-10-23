#include "stack.h"

int main(){
    my_stk::stack<int> stk1(3);
    my_stk::stack<int> stk2(3);

    stk1.push(1);
    stk1.push(2);
    stk1.push(3);

    stk2.push(1);
    stk2.push(2);
    stk2.push(3);

    if(stk1 == stk2)
        std::cout << "Stacks are equal"; // output: Stacks are equal
    else
        std::cout << "Stack are not equal";

    return 0;
}