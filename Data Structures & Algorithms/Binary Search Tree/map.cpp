// implementing binary search tree using map

#include <iostream>
#include <utility>

/*
    Structure of Tree node:

           tnode
    -----------------
   |      Parent     |
    -----------------
   |   Key  |  Value |
    -----------------
   |      is_H       |
    -----------------
   |  Left  |  Right |
    -----------------

*/

template <typename K, typename V>
struct mnode
{
    K key; // key
    V val; // value
    mnode *P; // Parent
    mnode *L; // Left 
    mnode *R; // Right
    bool is_H; // is dummy head? it will help us in iterator class
};

template <typename K, typename V>
class map
{
    /*
    Description: Dummy is acting as a nullptr and we are wasting this node but we are trying to implement as STL is implemented, so we will dynamically allocate it in maps constructor
    */
    mnode<K,V> *H; // dummy head (nullptr)
    int n; // size of tree
    
    void display_r(mnode<K,V> *ptr){
        // In-order traversal
        if(ptr == H){
            return;
        } else {
            std::cout << "Key: " << ptr->key << ", Value: " << ptr->val << std::endl;
            display_r(ptr->L);
            display_r(ptr->R);
        }
    }

public:
    map(){
        H = new mnode<K, V>; // dynamic dummy head node, it will act as nullptr represented with H
        // for dummy head, all mnode parts would be assigned with H OR more specifically nullptr
        H->P = this->H;
        H->L = this->H;
        H->R = this->H;
        H->is_H = true; // for dummy head node it will be true 
        n = 0; // tree height is zero still
    };

    void insert (const K &key, const V &val){
        /*
        Description: In insert function we will handle multiple steps as follows:
            Step 1: first create a new dynamic mnode and assign key to it and set the Left(L), Right(R) pointers and set is_H to false;
            Step 2: Check if we are dealing with first root_node if tree size is 0 so set dummy head and root node parents accordingly
            Step 3: If not first node then we should follow the following steps for proper insertion:
                Step 3.1: Now we have to insert value, if value is smaller than parent it will be insert at left side and if greater than parent then it will be inserted at right of parent, so to achieve this we will traverse through the tree to find the correct position and insert the new node in tree.
                Setp 3.2: After finding correct position we will insert the new node while comparing key with parents key and insert it at correct position.
            Step 4: After successful insertion we will increase the size of tree using ++n.
        */

        // as we are inserting new node so first create a new mnode dynamically
        mnode<K,V> *new_node = new mnode<K,V>; // new dynamic mnode
        new_node->key = key; // assign key to new_nodes key
        new_node->val = val; // assign value to new_nodes val
        new_node->L = H; // assign dummy head to new_nodes left part
        new_node->R = H; // assign dummy head to new_nodes Right part
        new_node->is_H = false; // for every other tnodes it will be false except the dummy head which is set in constructor

        
        if(n == 0){ // if it is first node
            new_node->P = H;
            H->P = new_node;
        } else { // if not first node then first find the position where to insert the new_node and then insert it to the tree
            mnode<K,V> *current = H->P; // start from root_node - Head parent holds the root_node addrress
            mnode<K,V> *parent = H; // parent will be the last node where value would be inserted

            // iterate though tree to find to correct position for the insertion
            while (current != H) // this loop will iterate until we reached to dummy head
            {
                parent = current; // assign the current node so that parent can have a record of last node
                if(key == current->key || val == current->val){ // avoid duplicates key or value
                    return; // if value or key already exist then return simply
                } else if(key < current->key) { // if given key is less than current node then we know we will go left
                    current = current->L; // move current to left side
                } else { // if value is greater than the given value then current should move to right side
                    current = current->R; // move current to right side
                }
            }

            // Now we have correct position to insert the new node so check where we should add, at left or right side?
            if(key < parent->key) { // compare key with parent->key if it less than or not? 
                parent->L = new_node; // assign new_node at parents left side
                H->L = new_node; 
            } else {
                parent->R = new_node;
                H->R = new_node;
            }
            
        }

        ++n; // increase the size of tree with each insertion
    }

    // return size of tree
    int size () const {
        return n;
    }
    
    /*      Recursive Functions       */

    // print values: (in-order traversal)
    void print_r(){ // r denotes to recursive function
        display_r(H->P);
    }

    class iterator {
        mnode<K,V> *ptr;
        friend map;

        public:
            
            bool operator==(const iterator &rhs) const {
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(const iterator &rhs) const {
                return this->ptr != rhs.ptr;
            }
            
            std::pair<int, int> operator*() const {
                return {ptr->key, ptr->val};
            }
            
            std::pair<int, int>* operator->() const {
                // return &ptr->key;
                return &{ptr->key, ptr->val};
            }
            iterator& operator++() {
                mnode<K,V> *current = this->ptr;  // Set current pointer to temporary pointer

                if (current->R->is_H != true) {
                    current = current->R;

                    while (current->R->is_H != true) {
                        current = current->L;
                    }

                    this->ptr = current;
                    return *this;
                } else {
                    mnode<K,V> *parent = current->P;

                    while (current == parent->R && current->P->is_H != true) {
                        current = parent;
                        parent = current->P;
                    }

                    this->ptr = parent;
                    return *this;
                }
            }
    };

    iterator begin() const { // it will return the smallest value in a tree
        iterator it;
        it.ptr = H->L; // H->L holds the smallest value
        return it;
    }

    iterator end() const { // it will return the highest value in a tree
        iterator it;
        it.ptr = H;
        return it;
    }

};

int main() {
    map<int,int> m;
    m.insert(10, 20);
    m.insert(20, 40);
    m.insert(760, 340);
    m.insert(230, 410);
    m.insert(204, 4330);

    map<int,int>::iterator it = m.begin();

    while(it != m.end()){
        std::pair<int, int> data = *it;
        std::cout << "Key: " << data.first << ", Value: " << data.second << std::endl;
        ++it;
    }

    return 0;
}
