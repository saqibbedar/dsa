#include <iostream>

template <typename T>
struct tnode {
    T val;
    tnode *P; // Parent node
    tnode *L; // Left child
    tnode *R; // Right child
};

template <typename T>
class BST {
    tnode<T> *H; // Dummy head node
    int n;       // Size of the BST

public:
    // Constructor
    BST() {
        H = new tnode<T>; // Allocate memory for the dummy head node
        H->L = H;         // Left pointer points to itself
        H->R = H;         // Right pointer points to itself
        H->P = H;         // Parent pointer points to itself
        n = 0;            // Initialize tree size
    }

    // Insert a new value
    void insert(const T &val) {
        tnode<T> *new_node = new tnode<T>;
        new_node->val = val;
        // Initialize left and right to dummy head
        new_node->L = H; 
        new_node->R = H;

        if (n == 0) { // If the tree is empty
            new_node->P = H; // Parent is dummy head
            H->P = new_node; // Root pointer in dummy head
        } else {
            tnode<T> *current = H->P; // Start from root
            tnode<T> *parent = nullptr;

            // Traverse to find the correct position
            while (current != H) {
                parent = current;
                if (val < current->val)
                    current = current->L; // Go left
                else
                    current = current->R; // Go right
            }

            // Insert the new node
            if (val < parent->val)
                parent->L = new_node;
            else
                parent->R = new_node;
            new_node->P = parent;
        }

        n++; // Increment tree size
    }

    // Display in-order
    void display() {
        if (n == 0) { // Tree is empty
            std::cout << "Tree is empty" << std::endl;
            return;
        }

        tnode<T> *current = H->P;

        // Find the leftmost node
        while (current->L != H) {
            current = current->L;
        }

        // Traverse the tree in-order
        while (current != H) {
            std::cout << current->val << " ";

            if (current->R != H && current->R->P == current) {
                current = current->R;
                while (current->L != H) {
                    current = current->L;
                }
            } else {
                current = current->R;
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    BST<int> tree;
    int x = 19;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(x);

    tree.display();

    return 0;
}
