#include <iostream>

template <typename T>
class Node{
    public:
        T val;
        Node *next;
        Node(T val) : val(val), next(nullptr){}
};

int main(){
    Node<int> *head = nullptr;
    Node<int> *tail = nullptr;

    int arr[5] = {1, 3, 5, 7, 9};

    for (int i = 0; i < 5; ++i){
        Node<int> *temp = new Node<int>(arr[i]);
        if(head == nullptr){
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    Node<int> *temp = head;

    while(temp != nullptr){
        std::cout << temp->val << " ";
        temp = temp->next;
    }

    // Clean up memory
    Node<int> *current = head;
    while (current != nullptr) {
        Node<int> *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}