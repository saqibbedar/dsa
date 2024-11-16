/*

Q1: Assume that you're using array-based stack and queues. How would the objects S and Q look like in the memory after executing the following code? In case of an error in the code, mention it, resolve it, and then execute it.

    stack<char> S(12);
    queue<char> Q(12);

    string str = "this is easy";

    for (int i = 0; i < str.length(); ++i){
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == ' '){
            S.push(str[i]);
        } else {
            Q.push(str[i]);
        }
    }

    while (S.empty() != true && S.empty() != true)
    {
        if(S.top() == ' '){
            Q.pop();
        } else {
            Q.push(S.top());
        }
        S.pop();
    }


*/


// Solution: *Not using array based stack & queue

#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

template <typename T>
void display(queue<T> q){
    int i = 0;
    std::cout << "[";
    while (!q.empty())
    {
        std::cout << q.front()<<", ";
        q.pop();
        ++i;
    }
    std::cout << "]";
}

int main(){
    stack<char> S; // size given in question S(12)
    queue<char> Q; // size given in question Q(12)

    string str = "this is easy";

    for (int i = 0; i < str.length(); ++i){
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == ' '){
            S.push(str[i]);
        } else {
            Q.push(str[i]);
        }
    }

    while (S.empty() != true)
    {
        if(S.top() == ' '){
            Q.pop();
        } else {
            Q.push(S.top());
        }
        S.pop();
    }

    display(Q);
    return 0;
}