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

        // Merge sort: divide and conquer rule
        void sort() const {
            // if empty
            if(head == nullptr){
                throw("Error: <sort> List is empty");
            }

            // Step 1: Split the list into two halves
            Node<T> *middle = getMiddle(); // getMiddle will return middle of list
            Node<T> *nexOfMiddle = middle->next; // next part of middle
            middle->next = nullptr; 

            // Step 2: Recursively sort the two halves


            // Step 3: Merge the sorted halves

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

    };

}

int main()
{
    try
    {
        my_std::forward_list<int> fl;

        int i = 0;
        while (i <= 100000)
        {
            fl.push_front(i);
            ++i;
        }
        
        fl.sort();

        my_std::forward_list<int>::iterator it;

        it = fl.begin();

        while(it != fl.end()){
            std::cout << *it << " ";
            ++it;
        }

        fl.clear();
        std::cout << std::endl;
        // std::cout << fl.back() << std::endl;

        std::forward_list<int> fl2;
        fl2.push_front(1);
        fl2.push_front(2);
        fl2.push_front(3);
        fl2.push_front(4);

        fl2.sort();

        std::forward_list<int>::iterator it2;
        for (it2 = fl2.begin(); it2 != fl2.end(); ++it2){
            std::cout << *it2 << " ";
        }
    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }

    return 0;
}