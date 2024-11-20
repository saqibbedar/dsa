/*

Name: Muhammad Saqib
RegNo: 037
Semester: 3rd

Task 2: Write a function (client code) which takes a queue as a parameter and reverses it. Use queue class from STL.

*/

#include <iostream>
#include <queue>
#include <stack>

template <typename T>
void reverse_queue(std::queue<T> &q){
    std::stack<int> stk;

    while(q.size() != 0){
        stk.push(q.front()); // push the front of queue to stack
        q.pop(); // remove the front 
    }

    while(stk.size() != 0){
        q.push(stk.top()); // now push the stacks top to queue
        stk.pop(); // remove the top from stack once copied to the queue
    }
}

template <typename T>
void display(const std::queue<T> q){

    std::queue<T> temp = q;

    while(temp.size() != 0){
        std::cout << temp.front() << " "; // display front element
        temp.pop(); // remove front element
    }

}

int main(){
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    reverse_queue(q);
    display(q);

    return 0;
}