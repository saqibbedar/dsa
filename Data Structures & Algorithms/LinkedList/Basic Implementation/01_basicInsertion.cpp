#include <iostream>

class Node
{
    public:
    int val;
    Node *next;
    Node(int x):val(x), next(nullptr){}
};


int main(){
    // insertion
    Node *head;
    Node *temp;
    int arr[4] = {1, 2, 3, 4};
    for (int i = 0; i < 4; ++i){
        if(head->next == nullptr){
            head = new Node(arr[i]);
        } else{
            temp = new Node(arr[i]);
            temp->next = head;
            head = temp;
        }
    }

    while(temp != nullptr){
        std::cout << temp->val << " ";
        temp = temp->next;
    }
        return 0;
}