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

    int arr[3] = {1, 3, 4};

    for(int x: arr){
        Node<int> *temp = new Node<int>(x);
        if(head == nullptr){
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    // Insert a Node 
    Node<int> *temp = head;
    while (temp != nullptr) {
        if (temp->val == 1) {
            Node<int> *newNode = new Node<int>(2);  // Create new node with value 2
            newNode->next = temp->next;             // Link newNode's next to temp's next
            temp->next = newNode;                   // Link temp's next to newNode
            break;                                  // Exit after insertion
        }
        temp = temp->next;
    }

    

    temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
    


    return 0;
}