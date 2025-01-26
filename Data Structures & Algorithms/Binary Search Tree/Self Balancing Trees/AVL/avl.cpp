/* 
    AVL is a self-balancing tree that is very aggressive in balancing case. It balance a tree when it is not balanced. We know BST time complexity depends upon the height of the tree. So, we use this self-balancing approach for tree. 

    Ex: If data is sorted and inserted to a BST then it will always have nodes at its right and height of tree will insanely grow, to patch such problem we use self-balancing approach for tree. There are many ways to do it, one is AVL and other is Red Black tree which does STL uses internally.
*/

#include <iostream>
#include <string>

/*
    Structure of AVL node:

          anode
    -----------------
   |      Parent     |
    -----------------
   |   Key  |  Value |
    -----------------
   |      is_H       |
    -----------------
   |      Height     |
    -----------------
   |  Left  |  Right |
    -----------------

*/

template <typename K, typename V>
struct anode
{
    anode *P; // Parent
    K key; // key
    V val; // value
    bool is_H; // is dummy head? it will help us in iterator class
    anode *Height; // height (for balance factor) 
    anode *L; // Left 
    anode *R; // Right
};

template <typename K, typename V>
class avl{
    anode<K, V> *DH; // dummy head
    int n;
    public:
        avl(){
            this->DH = new anode<K, V>;
            this->DH->P = this->DH;
            this->DH->is_H = true;
            this->DH->Height = 0;
            this->DH->L = this->DH;
            this->DH->R = this->DH;
        }

};

int main(){
    avl<std::string, std::string> tree;

    return 0;
}
