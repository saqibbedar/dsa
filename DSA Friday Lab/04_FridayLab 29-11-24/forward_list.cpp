#include <iostream>

struct Node{
    int val;
    Node *next;
    Node(int val) : val(val), next(nullptr) {}
};

class forward_list {
    Node *head, *tail;
    int n; // size of list

public:
    forward_list() : head(nullptr), tail(nullptr), n(0) {}

    void push_front(int val) {
        Node *new_node = new Node(val);
        if(this->head == nullptr){
            this->head = new_node;
            this->tail = new_node;
        } else {
            Node *temp = this->head;
            this->head = new_node;
            this->head->next = temp;
        }
        ++this->n;
    }

    void pop_front(){
        if(this->head == nullptr){
            throw("Error <forward_list> list is empty");
        } else {
            Node *temp = this->head->next;
            delete this->head;
            head = temp;
            
            if(head == nullptr){ // check if list becomes empty, then make tail empty too
                tail = nullptr;
            }

        }
        --this->n;
    }

    void print_list(){
        if(head == nullptr){
            throw("Error: <forward_list> list is empty");
        }
        Node *temp = this->head;
        std::cout << "List: [ ";
        while(temp != nullptr){
            std::cout << temp->val << ", ";
            temp = temp->next;
        }
        std::cout << "]";
    }

    int front() const{
        if(this->head == nullptr){
            return -1; // we can throw exception too
        }
        return this->head->val;
    }

    int back() const {
        if(this->head == nullptr){
            return -1; // we can throw exception too
        }
        return this->tail->val;
    }

    int size() const {
        return this->n;
    }

    bool empty() const {
        return n == 0;
    }

    void clear(){
        Node *temp = this->head;
        while (temp != nullptr)
        {
            Node *nex_node_holder = temp->next;
            delete temp;
            temp = nex_node_holder; // move to next_node
        }
        this->head = this->tail = temp;
        this->n = 0;
    }

    ~forward_list(){
        clear();
    }
};

int main()
{
    try
    {
        forward_list fl;
        fl.push_front(1);
        fl.push_front(2);
        fl.push_front(3);

        fl.print_list();
        fl.clear();
        std::cout << std::endl;
        std::cout << fl.back() << std::endl;
    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }

    return 0;
}