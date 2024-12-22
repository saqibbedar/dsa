#include <iostream>

template <typename K>
struct tnode {
    K key; // value in a node
    tnode *P; // Parent node
    tnode *L; // Left child
    tnode *R; // Right child
};

template <typename K>
class Set {
    tnode<K> *H; // Dummy head node
    int n;       // Size of the Tree

    void inOrderTraversal(tnode<K> *node) {
        if (node == H) return;
        inOrderTraversal(node->L);
        std::cout << node->key << " ";
        inOrderTraversal(node->R);
    }

public:
    // Constructor
    Set() {
        H = new tnode<K>; // Allocate memory for the dummy head node
        H->L = H;         // Left pointer points to itself
        H->R = H;         // Right pointer points to itself
        H->P = H;         // Parent pointer points to itself
        n = 0;            // Initialize tree size
    }

    // It takes a new Key as a value and insert it in a tree
    void insert(const K &key) {
        if(find(key)){ // If value is already existing then do nothing and retrun
            return;
        } else { // If value is not existing in tree then insert one
            tnode<K> *new_node = new tnode<K>;
            new_node->key = key; // assign the value to node
            // Initialize left and right to dummy head node 
            new_node->L = H; 
            new_node->R = H;

            if (n == 0) { // If the tree is empty
                new_node->P = H; // Parent is dummy head
                H->P = new_node; // Root pointer in dummy head
            } else {
                tnode<K> *current = H->P; // Start from root
                tnode<K> *parent = nullptr;

                // Traverse to find the correct position
                while (current != H) {
                    parent = current;
                    if (key < current->key)
                        current = current->L; // Go left
                    else
                        current = current->R; // Go right
                }

                // Insert the new node
                if (key < parent->key)
                    parent->L = new_node;
                else
                    parent->R = new_node;

                // set the parent 
                new_node->P = parent;
            }

            n++; // Increment tree size
        }
    }

    // Takes key as value and search for it in a tree if Yes then return true else false
    bool find(const K &key) const {

        tnode<K> *current = H->P; // start from root node

        while (current != H)
        {
            if(key == current->key) {
                return true; // return true if value was is found
            } else if (key < current->key) { // go left
                current = current->L;
            } else {
                current = current->R; // go right
            }
        }

        return false; // return false if value was not found
        
    }

    void erase(const K &key) {
        // case 1: deleting the leaf node
        // case 2(a): node has only left child
        // case 2(b): node has right child only

        tnode<K> *current = H->P; // start from root

        // case 1: deleting the leaf node
        while(current != H){
            if(key == current->key) {
                tnode<K> *temp = current; // store the current to temp node
                
            } else if(key < current->key) {
                current = current->L; // go left
            } else {
                current = current->R; // go right
            }
        }
    }

    // Display in-order
    void display() {
        if (n == 0) { // Tree is empty
            std::cout << "Tree is empty" << std::endl;
            return;
        }
        inOrderTraversal(H->P);
        std::cout << std::endl;
    }


};

int main() {
    Set<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(0);
    tree.insert(3);
    tree.insert(10);

    if(tree.find(3)){
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    tree.display();

    return 0;
}
