// implementing binary search tree using map

#include <iostream>

/*
    Structure of map node:

       mnode
    ----------
   |   Parent  |
    ----------
   | key | val |
    ----------
   |   is_H    |
    ----------
   |  H  |  H  |
    ----------

*/

struct mnode
{
    int key; // key
    int val; // value
    mnode *P; // Parent
    mnode *L; // Left 
    mnode *R; // Right
    bool is_H; // is dummy head - it will help us in iterator class
};

class map
{
    /*
    Description: Dummy is acting as a nullptr and we are wasting this node but we are trying to implement as STL is implemented, so we will dynamically allocate it in maps constructor
    */
    mnode *H; // dummy head (nullptr)
    int n; // size of tree

public:
    map(){
        H = new mnode; // dynamic dummy head node, it will act as nullptr represented with H
        // for dummy head, all mnode parts would be assigned with H OR more specifically nullptr
        H->P = H;
        H->L = H;
        H->R = H;
        H->is_H = true; // for dummy head node it will be true
        n = 0; // tree height is zero still
    };

    void insert (const int &key, const int &val){
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
        mnode *new_node = new mnode; // new dynamic mnode
        new_node->key = key; // assign key to new_nodes key
        new_node->val = val; // assign value to new_nodes val
        new_node->L = H; // assign dummy head to new_nodes left part
        new_node->R = H; // assign dummy head to new_nodes Right part
        new_node->is_H = false; // for every other tnodes it will be false except the dummy head which is set in constructor

        
        if(n == 0){ // if it is first node
            new_node->P = H;
            H->P = new_node;
        } else { // if not first node then first find the position where to insert the new_node and then insert it to the tree
            mnode *current = H->P; // start from root_node - Head parent holds the root_node addrress
            mnode *parent = H; // parent will be the last node where value would be inserted

            // iterate though tree to find to correct position for the insertion
            while (current != H) // this loop will iterate until we reached to dummy head
            {
                parent = current; // assign the current node so that parent can have a record of last node
                if(key < current->key) { // if given value is less than current node then we know we will go left
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

    class iterator {
        mnode *ptr;
        friend map;

        public:
            bool operator==(const iterator &rhs) const {
                return ptr->key == rhs.ptr->key && ptr->val == rhs.ptr->val;
            }
            bool operator!=(const iterator &rhs) const {
                return ptr == rhs.ptr;
            }
            int operator*() const {
                return ptr->key;
            }
            int* operator->() const {
                return &ptr->key;
            }
            iterator operator++() {
                
            }
    };

    iterator begin() const { // it will return the smallest value in a tree
        iterator it;
        it.ptr = H->L; // H->L holds the smallest value
        return it;
    }

    iterator end() const { // it will return the highest value in a tree
        iterator it;
        it.ptr = H->R; // H->R holds the highest value
        return it;
    }

};

int main() {
    map m;
    m.insert(10, 20);

    map::iterator it = m.begin();

    while(it != m.end()){
        
    }

    return 0;
}