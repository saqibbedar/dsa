#include <iostream>

class Node
{
    public:
    int val;
    Node *next;
    Node(int x):val(x), next(nullptr){}
};


int main(){
    Node *head;
    head = new Node(4); // val = 4 and next is nullptr and node address is assigned to head pointer

    // insertion
    Node *temp;
    if(head->next == nullptr){
        head = new Node(28);
    }else{
        temp = new Node(28);
        temp->next = head;
        head = temp;
    }

    return 0;
}