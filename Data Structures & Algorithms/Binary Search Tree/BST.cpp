#include <iostream>

template <typename K>
struct tnode {
    K key;
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

    // Insert a new value
    void insert(const K &key) {
        tnode<K> *new_node = new tnode<K>;
        new_node->key = key;
        // Initialize left and right to dummy head
        new_node->L = H; 
        new_node->R = H;

        if (n == 0) { // If the tree is empty
            new_node->P = H; // Parent is dummy head
            H->P = new_node; // Root pointer in dummy head
        } else {
            tnode<K> *root_node = H->P; // Start from root node: Dummy Head parent holds the root node
            tnode<K> *parent = nullptr;

            // Traverse to find the correct position
            while (root_node != H) {
                parent = root_node;
                if (key < root_node->key)
                    root_node = root_node->L; // Go left
                else
                    root_node = root_node->R; // Go right
            }

            // Insert the new node
            if (key < parent->key)
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

        tnode<K> *current = H->P;

        // Find the leftmost node
        while (current->L != H) {
            current = current->L;
        }

        // Traverse the tree in-order
        while (current != H) {
            std::cout << current->key << " ";

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
    Set<int> tree;
    int x = 19;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(x);

    tree.display();

    return 0;
}
