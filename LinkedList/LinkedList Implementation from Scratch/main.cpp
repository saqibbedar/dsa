#include <iostream>

class Node {
    public:
    int val;
    Node* next;
    Node(int x=0): val(x), next(nullptr){}
};

int main(){
    Node *head, *tail;
    head = new Node;
    tail = head;

    int arr[3] = {1, 3, 5};

    for (int i = 0; i < 3; ++i){
        Node *temp = new Node(arr[i]);
        tail->next = temp;
        tail = temp;
    }

    Node *temp = head->next;
    while(temp != nullptr){
        std::cout << temp->val << " ";
        temp = temp->next;
    }

    return 0;
}