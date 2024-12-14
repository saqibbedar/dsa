#include <iostream>

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

        // merge sorts helper function
        // get the middle of a list using slow & fast pointers
        // Node<T>* getMiddle(){
        //     // start slow and fast with head
        //     Node<T> *slow = head;
        //     Node<T> *fast = head;

        //     while(slow != nullptr && fast != nullptr){
        //         slow = slow->next; // slow will move one step
        //         fast = fast->next->next; // move two steps at a time
        //     }

        //     return slow;
        // }

    public:
        forward_list() : head(nullptr), tail(nullptr), n(0) {}
        ~forward_list(){clear();}

        // push value in a list
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

        // pop first value in list
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
        
        // display all values in list 
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
        
        // return top value in list
        T front() const{
            if(this->head == nullptr){
                throw("Error: List is empty");
            }
            return head->val;
        }

        // return last value in list
        T back() const {
            if(this->head == nullptr){
                throw("Error: <forward_list-back> List is empty");
            }
            return this->tail->val;
        }

        // return total size of list
        int size() const {
            return this->n;
        }
        
        // return boolean value, if list is empty or not?
        bool empty() const {
            return n == 0;
        }

        // make list empty
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

        // sort list 
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
        // void sort() const { 
        //     // if empty
        //     if(head == nullptr){
        //         throw("Error: <sort> List is empty");
        //     }

        //     // Step 1: Split the list into two halves
        //     Node<T> *middle = getMiddle(); // getMiddle will return middle of list
        //     Node<T> *nexOfMiddle = middle->next; // next part of middle
        //     middle->next = nullptr; 

        //     // Step 2: Recursively sort the two halves


        //     // Step 3: Merge the sorted halves

        // }

        // iterator class to traverse through a list
        class iterator{
            Node<T> *ptr;
            friend forward_list;

        public:
            // Check if two iterators are equal, if yes true else false & rhs param is the iterator to compare with
            bool operator!=(const iterator &rhs) const {
                return this->ptr != rhs.ptr;
            }
            // Dereferences the iterator to access the value & the value pointed to by the iterator
            T operator*() const {
                return this->ptr->val;
            }
            // Pre-increment operator to move the iterator to the next element & return incremented iterator
            iterator operator++(){
                ptr = ptr->next;
                return *this;
            }
            // Post-increment operator to move iterator to the next element & return the iterator before incrementing
            iterator operator++(int){
                iterator temp;
                temp.ptr = this->ptr;
                this->ptr = this->ptr->next;
                return temp; // return temp pointer
            }
            // Checks if two iterators are equal, true if equal else false & rhs is the iterator to compare with.
            bool operator==(const iterator &rhs) const {
                return this->ptr != rhs.ptr;
            }
            // Accesses the member of the object pointed to by the iterator & return pointer to the value
            T* operator->(){
                return &this->ptr->val; // return the address of value
            }
        };

        /* Iterator functions */

        // Returns an iterator pointing to the first element in the list
        iterator begin() const{
            iterator temp;
            temp.ptr = this->head; // assign front to the iterator
            return temp;
        }

        // Returns an iterator pointing to the past-the-end element in the list
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

        int i = 2;
        while (i <= 10)
        {
            fl.push_front(i);
            i = i+2;
        }
        
        fl.my_sort();

        my_std::forward_list<int>::iterator it;

        it = fl.begin();

        while(it != fl.end()){
            std::cout << *it << " ";
            ++it;
        }
    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }

    return 0;
}