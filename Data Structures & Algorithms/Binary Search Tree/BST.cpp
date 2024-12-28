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
        tnode<K> *new_node = new tnode<K>;
        new_node->key = key; // assign the value to node
        // Initialize left and right to dummy head node 
        new_node->L = H; 
        new_node->R = H;

        if (n == 0) { // If the tree is empty
            new_node->P = H; // Parent is dummy head
            H->P = new_node; // Root pointer in dummy head
        } else {
            tnode<K> *root_node = H->P; // Start from root node: Dummy Head parent holds the root node
            tnode<K> *parent = nullptr;

            // Traverse to find the correct position
            while (current != H) {
                parent = current;
                if(key == current->key) { // if value already exists then delete the allocated memory and simply return
                    delete new_node; // clean memory
                    return; // simply return
                } else if (key < current->key)
                    current = current->L; // Go left
                else
                    root_node = root_node->R; // Go right
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
    
    // Takes key as a value and search it in a tree and delete it
    void erase(const K &key) {
        tnode<K> *current = H->P; // Start from the root
        tnode<K> *parent = H;     // Keep track of the parent node

        // Traverse the tree to find the node to delete
        while (current != H) {
            if (key == current->val) {
                break; // Node to delete is found
            }
            parent = current;
            if (key < current->val) {
                current = current->L; // Go left
            } else {
                current = current->R; // Go right
            }
        }

        if (current == H) {
            std::cout << "Key not found." << std::endl;
            return; // Key not found
        }

        // Case 1: Deleting a leaf node
        if (current->L == H && current->R == H) {
            if (parent->L == current) {
                parent->L = H; // Update parent's left pointer
            } else {
                parent->R = H; // Update parent's right pointer
            }
            delete current;
        }
        // Case 2(a): Node with only a left child
        else if (current->L != H && current->R == H) {
            if (parent->L == current) {
                parent->L = current->L; // Update parent's left pointer
            } else {
                parent->R = current->L; // Update parent's right pointer
            }
            current->L->P = parent; // Update child's parent pointer
            delete current;
        }
        // Case 2(b): Node with only a right child
        else if (current->L == H && current->R != H) {
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
            while (successor->L != H) {
                successor_parent = successor;
                successor = successor->L;
            }

            // Replace current's value with successor's value
            current->val = successor->val;

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

    return 0;
}
