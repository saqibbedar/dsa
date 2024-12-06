#include <iostream>

    template <typename T>
    struct Node{
        T val;
        Node *next, *prev;
    };

    template <typename T>
    class list {
        Node<T> *head;
        int n; // size of list

    public:
        list() : n(0) {
            head = new Node<T>;
            head->prev = head;
            head->next = head;
        }

        ~list(){
            clear();
        }

        void push_front(T val) {
            Node<T> *new_node = new Node<T>;
            new_node->val = val;
            new_node->next = head->next;
            new_node->prev = head;
            head->next->prev = new_node;
            head->next = new_node;
            ++n;
        }

        void pop_front(){
            Node<T> *temp = head->next;
            head->next = temp->next;
            temp->next->prev = head;
            delete temp;
            --this->n;
        }

        void print_list(){
            if(head == head->next){
                throw("Error: <list> list is empty");
            }
            Node<T> *temp = this->head->next;
            std::cout << "List: [ ";
            while(temp != head){
                std::cout << temp->val << ", ";
                temp = temp->next;
            }
            std::cout << "]";
        }

        T front() const{
            return head->next->val;
        }

        T back() const {
            return this->head->prev->val;
        }

        int size() const {
            return this->n;
        }

        bool empty() const {
            return n == 0;
        }

        void clear(){
            while (head->next != head)
            {
                pop_front();
            }
        }

    };

int main()
{
    try
    {
        list<int> fl;
        fl.push_front(1);
        fl.push_front(2);
        fl.push_front(3);
        fl.push_front(4);

        fl.print_list();
        fl.clear();
        std::cout << std::endl;
        fl.print_list();

    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }

    return 0;
}