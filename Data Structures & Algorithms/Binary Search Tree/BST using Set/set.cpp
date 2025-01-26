// implementing binary search tree using set
#include <iostream>
#include <string>

/*
    Structure of Tree node:

          tnode
    -----------------
   |      Parent     |
    -----------------
   |       Key       |
    -----------------
   |      is_H       |
    -----------------
   |  Left  |  Right |
    -----------------

*/

template<typename K>
struct tnode {
    tnode<K> *P; // parent
    K key;
    bool is_H; // is_dummy_head
    tnode<K> *L; // Left
    tnode<K> *R; // Right
};


template<typename K>
class set{
    tnode<K> *H; // dummy head
    int n; // size of set

    /*
        ************************
        
           Recursive functions

        ************************
    */

    void clear_r(tnode<K> *ptr) {
        if(ptr == this->H) {
            return;
        }
        clear_r(ptr->L);
        clear_r(ptr->R);
        delete ptr;
    }

    void copy_r(tnode<K>* node, tnode<K>* parent) {
        if (node->is_H) return; // Base case

        insert(node->key, node->key); // Insert node

        copy_r(node->L, parent); // Copy left subtree
        copy_r(node->R, parent); // Copy right subtree
    }

    public:
        set(){ // constructor
            this->H = new tnode<K>;
            this->H->P = this->H;
            this->H->is_H = true;
            this->H->L = this->H;
            this->H->R = this->H;
            this->n = 0;
        }

        set(const set &rhs) {
            this->H = new tnode<K>;
            this->H->P = this->H;
            this->H->is_H = true;
            this->H->L = this->H;
            this->H->R = this->H;
            this->n = 0;

            copy_r(rhs.H->P, this->H);
        }
        
        ~set(){
            clear();
        }

        void insert(const K &key) {
            // 1. Create a new node
            tnode<K> *nn = new tnode<K>; // nn: new_node
            nn->key = key;
            nn->is_H = false;
            nn->L = this->H;
            nn->R = this->H;

            if(n == 0) { // 2. set root node

                nn->P = this->H;
                this->H->P = nn;
                this->H->L = nn;
                this->H->R = nn;

            } else { // 3. Insert new node at correct position

                tnode<K> *current = H->P; // Start from root node to find position where to insert the value
                tnode<K> *parent = nullptr;

                // 4. Traverse to find the correct position
                while(current != this->H) {

                    parent = current; // keep record of last node

                    if(key == current->key) { // If already key is inserted
                        delete nn; // delete allocated node
                        return;
                    } else if (key < current->key) {
                        current = current->L; // go left
                    } else {
                        current = current->R; // go right
                    }
                }

                // 5. Check where to insert the node
                if(key < parent->key) {
                    parent->L = nn;
                } else {
                    parent->R = nn;
                }

                // 6. Set dummy heads left and right to point smaller and larger values
                if (key < H->L->key) {
                    H->L = nn;
                }else{
                    H->R = nn;
                }

                // Set the parent
                nn->P = parent;

            }

            ++this->n; // increment size
        }

        bool contains(const K &key) const { // checks if the container contains element with specific key

            tnode<K> *current = this->H->P; // start from root node

            while(current != this->H) {

                if(key == current->key) {
                    return true;
                } else if (key < current->key) {
                    current = current->L;
                } else {
                    current = current->R;
                }

            }

            return false;
        }

        bool empty() const { // checks whether the container is empty
            return this->n == 0;
        }

        int size() const { // returns the number of elements
            return this->n;
        }

        size_t count(const K &key) const { // returns the number of elements matching specific key
            // This is either 1 or 0 since this container does not allow duplicates.
            if(this->contains(key)) {
                return 1;
            } else {
                return 0;
            }
        }

        void clear() { // Erases all elements from the container
            clear_r(this->H);
            this->H->P = this->H; 
            this->H->L = this->H; 
            this->H->R = this->H; 
            this->n = 0;
        }

        size_t erase(const K &key) { // Removes specified elements from the container.
            tnode<K> *current = this->H->P; // Start from the root
            tnode<K> *parent = this->H;     // Keep track of the parent node

            // Traverse the tree to find the node to delete
            while (current != H) {
                if (key == current->key) {
                    break; // Node to delete is found
                }
                parent = current;
                if (key < current->key) {
                    current = current->L; // Go left
                } else {
                    current = current->R; // Go right
                }
            }

            if (current == this->H) {
                return -1; // Key not found
            }

            // Case 1: Deleting a leaf node
            else if (current->L == this->H && current->R == this->H) {
                if (parent->L == current) {
                    parent->L = this->H; // Update parent's left pointer
                } else {
                    parent->R = this->H; // Update parent's right pointer
                }
                delete current;
            }

            // Case 2(a): Node with only a left child
            else if (current->L != this->H && current->R == this->H) {
                if (parent->L == current) {
                    parent->L = current->L; // Update parent's left pointer
                } else {
                    parent->R = current->L; // Update parent's right pointer
                }
                current->L->P = parent; // Update child's parent pointer
                delete current;
            }

            // Case 2(b): Node with only a right child
            else if (current->L == this->H && current->R != this->H) {
                if (parent->L == current) {
                    parent->L = current->R; // Update parent's left pointer
                } else {
                    parent->R = current->R; // Update parent's right pointer
                }
                current->R->P = parent; // Update child's parent pointer
                delete current;
            }
            // Case 3: Node with two children
            else {
                // Find in-order successor (smallest node in the right subtree)
                tnode<K> *successor = current->R;
                tnode<K> *successor_parent = current;

                while (successor->L != this->H) {
                    successor_parent = successor;
                    successor = successor->L;
                }

                // Replace current's value with successor's value
                current->key = successor->key;

                // Delete the successor node (it will be a leaf or have only a right child)
                if (successor_parent->L == successor) {
                    successor_parent->L = successor->R;
                } else {
                    successor_parent->R = successor->R;
                }
                if (successor->R != H) {
                    successor->R->P = successor_parent;
                }
                delete successor;
            }

            n--; // Decrease the size of the tree
        }

        set& operator=(const set& obj) {
            if (this != &obj) {
                clear(); // free tree before copying the values
                copy_r(obj.H->P, this->H); // Copy new tree
            }
            return *this;
        }

        /*
            ********************************

                        Iterators

            ********************************
        */
        class iterator {
            tnode<K> *ptr;
            friend set<K>;

            public: 

                iterator(){
                    this->ptr = nullptr;
                }

                bool operator!=(const iterator &rhs) const {
                    return this->ptr != rhs.ptr;
                }

                bool operator==(const iterator &rhs) const {
                    return this->ptr == rhs.ptr;
                }

                K operator*() const { // Dereferences the iterator to access the key & the value pointed by the iterator
                    return this->ptr->key;
                }

                K* operator->() const { // Accesses the member of the object pointed to by the iterator & return pointer to the value
                    return &this->ptr->key;
                }

                iterator& operator++() {
                    tnode<K> *ptr = this->ptr; // store the current pointer in ptr

                    if(ptr->R->is_H != true){
                        ptr = ptr->R;
                        while(ptr->L->is_H != true){
                            ptr = ptr->L;
                        }
                        this->ptr = ptr;
                    } else {
                        tnode<K> *parent = ptr->P;
                        while(ptr == parent->R && ptr->P->is_H != true) {
                            ptr = parent;
                            parent = ptr->P;
                        }
                        this->ptr = parent;
                    }

                    return *this;
                }

                iterator& operator--() { // reverse of operator++

                    tnode<K>* temp_ptr = this->ptr; // Store the current pointer in temporary pointer

                    if (temp_ptr->L->is_H != true) { // if temp_prt's left child exist then go inside

                        // first assign the left child to ptr
                        temp_ptr = ptr->L; 

                        // find the rightmost child of subtree
                        while (temp_ptr->R->is_H != true) { 
                            temp_ptr = temp_ptr->R;
                        }

                        this->ptr = temp_ptr; // assign the temp
                    }
                    
                    // If there is no left child then move upwards
                    else {
                        tnode<K>* parent = temp_ptr->P; // Move upwards to parent
                        

                        while (temp_ptr == parent->L && parent->P->is_H != true){ // Find the first ancestor node that is a right child
                            temp_ptr = parent;
                            parent = temp_ptr->P;
                        }
                        this->ptr = parent; // Move to the previous node
                    }

                    return *this; // Return iterator by reference for chained operations
                }

                iterator operator--(int) {
                    iterator old;
                    old.ptr = this->ptr;
                    this->operator--();
                    return old;
                }

                iterator operator++(int) {
                    iterator old;
                    old.ptr = this->ptr;
                    this->operator++();
                    return old;
                }


        };

        class reverse_iterator {

            tnode<K> *ptr;
            friend set<K>;

            public: 

                reverse_iterator(){
                    this->ptr = nullptr;
                }

                bool operator!=(const reverse_iterator &rhs) const {
                    return this->ptr != rhs.ptr;
                }

                bool operator==(const reverse_iterator &rhs) const {
                    return this->ptr == rhs.ptr;
                }

                K operator*() const { 
                    return this->ptr->key;
                }

                K* operator->() const {
                    // Accesses the member of the object pointed to by the iterator & return pointer to the value
                    return &this->ptr->key; // return address
                }


                reverse_iterator& operator++() { // reverse of operator++

                    tnode<K>* temp_ptr = this->ptr; // Store the current pointer in temporary pointer

                    if (temp_ptr->L->is_H != true) { // if temp_prt's left child exist then go inside

                        // first assign the left child to ptr
                        temp_ptr = ptr->L; 

                        // find the rightmost child of subtree
                        while (temp_ptr->R->is_H != true) { 
                            temp_ptr = temp_ptr->R;
                        }

                        this->ptr = temp_ptr; // assign the temp
                    }
                    
                    // If there is no left child then move upwards
                    else {
                        tnode<K>* parent = temp_ptr->P; // Move upwards to parent
                        
                        while (temp_ptr == parent->L) { 
                            if (parent->is_H) { // Stop if we reach the dummy head 
                                this->ptr = parent; // assign dummy head node
                                return *this;
                            }
                            temp_ptr = parent;
                            parent = temp_ptr->P;
                        }
                        this->ptr = parent; // Move to the previous node
                    }

                    return *this; 
                }
                
                reverse_iterator operator++(int) {
                    reverse_iterator old;
                    old.ptr = this->ptr;
                    this->operator++();
                    return old;
                }
        };

        iterator find(const K &key) const { // finds element/node with specific key

            tnode<K> *current = this->H->P; // start from root node

            while(current != this->H){
                if(key == current->key) {
                    iterator it; // iterator to return element found
                    it.ptr = current;
                    return it;
                } else if (key < current->key) {
                    current = current->L;
                } else {
                    current = current->R;
                }
            }

            return this->end();
        }

        iterator begin() const {
            iterator it;
            it.ptr = this->H->L; // assign smallest node
            return it;
        }

        iterator end() const {
            iterator it;
            it.ptr = this->H; // assign dummy head - nullptr
            return it;
        }

        reverse_iterator rbegin() const {
            reverse_iterator rit;
            rit.ptr = this->H->R; // assign largest value
            return rit;
        }

        reverse_iterator rend() const {
            reverse_iterator rit;
            rit.ptr = this->H;
            return rit;
        }

        void swap(set<K>& rhs) {
            std::swap(this->H, rhs.H);
            std::swap(this->n, rhs.n);
        }

};


int main() {
    try
    {
        set<int> m;

        m.insert(0);
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        m.insert(5);

        std::cout << "Contains key 1: " << m.contains(0) << std::endl;
        m.erase(4);
        std::cout << "Contains key 4: " << m.contains(4) << std::endl;
        std::cout << "Size of set: " << m.size() << std::endl;

        std::cout << "Iterator" << std::endl;
        for (set<int>::iterator it = m.begin(); it != m.end(); it++){
            std::cout << "Key: " << *it << std::endl;
        }

        m.clear();

    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }
    
    return 0;
}