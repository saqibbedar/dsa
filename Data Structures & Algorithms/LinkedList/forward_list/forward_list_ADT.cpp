/*
    Disclaimer
    This file contains code for a custom implementation of a forward_list ADT in C++. While the code has been tested and works as expected in various scenarios, it may still contain errors or edge cases that have not been accounted for.

    I have made efforts to ensure the correctness of the implementation, but I cannot guarantee that the code will work flawlessly in every situation or with every input. If you find any bugs, or if the code doesn't work as expected in your use case, please feel free to open an issue or contribute a fix.

    Use the code at your own discretion.

    Saqib Bedar - January 26, 2025
*/

#include <iostream>

namespace mystd {

    /*
		Structure of forward_list node:

                   fnode
               --------------
              | value | next |
               --------------

	*/

    /*
        forward_list: It is also referred as singly list and it is different from the list(doubly list) because forward list has only next pointer not previous to go back, so this is the slight difference between them. Below is the complete implementation of forward_list as defined in STL.    
    */

    // forward_list node
    template <typename T>
    struct fnode
    {
        T val;
        fnode<T> *next; 
        fnode(const T& v): val(v), next(nullptr) {}
    };

    template <typename T>
    class forward_list{

        fnode<T> *head;
        int n = 0;

    public:

        forward_list(){
            this->head = nullptr;
            this->n = 0;
        }

        ~forward_list(){
            this->clear();
        }

        void push_front(const T &val){ // inserts an element to the beginning
            fnode<T> *new_node = new fnode<T>(val);
            new_node->next = this->head;
            this->head = new_node;
            this->n++;
        }

        void pop_front() { // removes the first element
            if(this->head == nullptr)
                throw("List underflow");
            fnode<T> *temp = this->head;
            this->head = temp->next;
            delete temp;
            --this->n;
        }

        forward_list& operator=(const forward_list &rhs){ // assigns values to the container
        
            if(*this == rhs) return *this; 
            
            this->clear();

            fnode<T> *current = rhs.head;

            while (current) {
                this->push_front(current->val);
                current = current->next;
            }

            this->reverse();
            return *this;
        }

        T front() const { // access the first element
            return this->head->val;
        }

        bool empty() const { // checks whether the container is empty
            return this->n == 0;
        }

        size_t size() const {
            return this->n;
        }

        void clear() { // clears the contents
            while (this->head)
            {
                fnode<T> *temp = this->head;
                this->head = this->head->next;
                delete temp;
            }
            this->n = 0;
        }

        void swap(forward_list &rhs) { // swaps the contents
            std::swap(this->head, rhs.head);
            std::swap(this->n, rhs.n);
        }

        void reverse() {

            fnode<T>* prev = nullptr;
            fnode<T>* current = this->head;
            fnode<T>* next = nullptr;

            while (current != nullptr) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            this->head = prev;  // Update head to point to the new first element
        }


        class iterator {

            fnode<T> *ptr;
            friend forward_list;

            public:
                
                iterator(): ptr(nullptr) {}

                bool operator!=(const iterator &rhs) const {
                    return this->ptr != rhs.ptr;
                }

                bool operator==(const iterator &rhs) const {
                    return this->ptr == rhs.ptr;
                }

                T& operator*() const {
                    return this->ptr->val;
                }

                T* operator->() const {
                    return &(this->ptr->val);
                }

                iterator& operator++(){
                    this->ptr = this->ptr->next;
                    return *this;
                }
        };

        iterator begin() const { // returns an iterator to the beginning
            iterator it;
            it.ptr = this->head;
            return it;
        }

        iterator end() const { // returns an iterator to the end
            iterator it;
            it.ptr = nullptr;
            return it;
        }

        void unique() {
            if (this->head == nullptr) return;

            fnode<T>* current = this->head;

            // Iterate over each element of the list
            while (current != nullptr && current->next != nullptr) {
                fnode<T>* runner = current;
                while (runner->next != nullptr) {
                    if (current->val == runner->next->val) {
                        // Duplicate found, remove it
                        fnode<T>* temp = runner->next;
                        runner->next = runner->next->next;
                        delete temp;
                        --this->n;  // Adjust size
                    } else {
                        runner = runner->next;
                    }
                }
                current = current->next;
            }
        }


        // Non-member functions

        friend bool operator==(const forward_list &lhs, const forward_list &rhs) {
            // Case 1: If both lists are empty
            if (lhs.head == nullptr && rhs.head == nullptr) {
                return true;
            }

            // Case 2: If the sizes differ, the lists are not equal
            if (lhs.n != rhs.n) {
                return false;
            }

            // Case 3: Compare each element
            iterator lhs_it = lhs.begin();
            iterator rhs_it = rhs.begin();

            while (lhs_it != lhs.end() && rhs_it != rhs.end()) {
                if (*lhs_it != *rhs_it) {
                    return false;
                }
                ++lhs_it;
                ++rhs_it;
            }

            return true;
        }

        friend bool operator!=(const forward_list &lhs, const forward_list &rhs) {
            return !(lhs == rhs);
        }

    };
}


int main(){

    mystd::forward_list<int> f;

    // Test push_front
    f.push_front(30);
    f.push_front(30);
    f.push_front(30);
    f.clear();
    f.push_front(10);
    f.push_front(20);
    f.push_front(30);
    f.push_front(30);
    f.push_front(30);
    f.push_front(30);
    f.push_front(40);
    f.unique();

    for (auto it = f.begin(); it != f.end(); ++it) {
        std::cout << *it << " "; // output: 40 30 20 10
    }

    f.reverse();
    std::cout << std::endl;
    for (auto it = f.begin(); it != f.end(); ++it) {
        std::cout << *it << " "; // output: 10 20 30 40
    }
    
    return 0;
}