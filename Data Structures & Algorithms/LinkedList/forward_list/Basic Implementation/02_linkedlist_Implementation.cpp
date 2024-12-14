#include <iostream>
using namespace std;

struct Node{
    int val;
    Node *next;
};

int main()
{
    Node *head, *tail;
    head = new Node;
    tail = head;

    // head->val = 10;
    // cout << tail->val; // ouput: 10

    head->val = 0;
    head->next = nullptr;

    int arr[3] = {1, 3, 5};

    // Create and link new nodes
    for (int i = 0; i < 3; ++i){
        Node *temp = new Node; // new node
        temp->val = arr[i]; // set value
        temp->next = nullptr;
        tail->next = temp; // Link the current tail node to the new node
        tail = temp; // Move the tail to the new node
    }

    return 0;
}