#include <iostream>
#include <forward_list>

namespace my_std{

    template <typename T>
    struct Node{
        T val;
        Node *next;
        Node(T val) : val(val), next(nullptr) {}
    };

    template <typename T>
    class forward_list {
        Node<T> *head, *tail;
        int n; // size of list

        // merge sorts helper functions
        // get the middle fo list using slow & fast pointers
        Node<T>* getMiddle(){
            // start slow and fast with head
            Node<T> *slow = head;
            Node<T> *fast = head;

            while(slow != nullptr && fast != nullptr){
                slow = slow->next; // slow will move one step
                fast = fast->next->next; // move two steps at a time
            }

            return slow;
        }

    public:
        forward_list() : head(nullptr), tail(nullptr), n(0) {}
        ~forward_list(){clear();}

        void push_front(T val) {
            Node<T> *new_node = new Node<T>(val);
            if(this->head == nullptr){
                this->head = new_node;
                this->tail = new_node;
            } else {
                Node<T> *temp = this->head;
                this->head = new_node;
                this->head->next = temp;
            }
            ++this->n;
        }

        void pop_front(){
            if(this->head == nullptr){
                throw("Error <forward_list> list is empty");
            } else {
                Node<T> *temp = this->head->next;
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
            Node<T> *temp = this->head;
            std::cout << "List: [ ";
            while(temp != nullptr){
                std::cout << temp->val << ", ";
                temp = temp->next;
            }
            std::cout << "]";
        }

        T front() const{
            if(this->head == nullptr){
                throw("Error: List is empty");
            }
            return head->val;
        }

        T back() const {
            if(this->head == nullptr){
                throw("Error: <forward_list-back> List is empty");
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
            Node<T> *temp = this->head;
            while (temp != nullptr)
            {
                Node<T> *nex_node_holder = temp->next;
                delete temp;
                temp = nex_node_holder; // move to next_node
            }
            this->head = this->tail = temp;
            this->n = 0;
        }

        // change it with merge_sort or quick_sort
        void my_sort() const{
            if(head == nullptr){
                throw("Error: <sort> List is empty");
            }

            Node<T> *temp = head;
            while (temp != nullptr) { // iterator over list

                Node<T> *temp2 = temp->next;
                while(temp2 != nullptr){
                    if(temp->val > temp2->val ){
                        std::swap(temp->val, temp2->val);
                    }
                    temp2 = temp2->next;
                }

                temp = temp->next;

            }
        }

        // iterator class
        class iterator{
            Node<T> *ptr;
            friend forward_list;

        public:
            bool operator!=(const iterator &rhs) const {
                return this->ptr != rhs.ptr;
            }
            T operator*() const {
                return this->ptr->val;
            }
            iterator operator++(){
                ptr = ptr->next;
                return *this;
            }
        };

        // functions for iterator
        iterator begin() const{
            iterator temp;
            temp.ptr = this->head; // assign front to the iterator
            return temp;
        }

        iterator end() const{
            iterator temp;
            temp.ptr = nullptr;
            return temp;
        }

        void insert_after(const iterator pos, T value){
            Node<T> *newNode = new Node<T>(value); // first assign the new memory

            Node<T> *current = pos.ptr; // assign current pointer

            // insert the new node to current as we have the position
            newNode->next = current->next;
            current->next = newNode;
            ++this->n;
        }

        void erase_after(const iterator pos){
            Node<T> *current = pos.ptr; // asign current position
            Node<T> *temp = current->next; 
            current->next =  temp->next; // assign temp next to current
            delete temp;
            --this->n;
        }

        void splice_after(const iterator pos, forward_list& other){
            Node<T> *current = pos.ptr;
            Node<T> *currents_next = current->next;
            current->next = other.head;
            other.tail = currents_next;
        }

    };

}

int main()
{
    try
    {
        my_std::forward_list<int> fl;

        fl.push_front(1);
        fl.push_front(2);
        fl.push_front(3);

        my_std::forward_list<int>::iterator it;

        it = fl.begin();
        fl.insert_after(it, 10);
        fl.erase_after(it);

        my_std::forward_list<int> fl2;
        fl2.push_front(4);
        fl2.push_front(5);
        fl2.push_front(7);

        // fl.splice_after(it, fl2); // Not working, do it later

        while(it != fl.end()){
            std::cout << *it << " ";
            ++it;
        }

        fl.clear();
    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }

    return 0;
}