// Circular Threaded BST with dummy head

#include <iostream>

template <typename T>
struct tnode
{
    T val;
    tnode *left_node, *right_node, *parent_node;
};

template <typename T>
class BST
{
    tnode<T> *root, *head;
    int n;

public:
    BST(){
        // self assignment for root node
        head = new tnode<T>;
        head->parent_node = head;
        head->left_node = head;
        head->right_node = head;
        root = head;
        n = 0;
    }

    void push(T &val){
        
        // Create a new Node
        tnode<T> *new_node = new tnode<T>;
        new_node->val = val;

        if(n == 0){ // is it first node?
            new_node->left_node = head;
            new_node->right_node = head;
            new_node->parent_node = head;
            root = new_node;
            head->parent_node = root;
        } else {
            tnode *it;
        }
    }
};


int main(){

    return 0;
}