#include <iostream>

/*
    Structure of mnode:

           mnode
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
struct mnode {
    K key; // Key
    V val; // value
    mnode<K,V> *P; // Parent node
    mnode<K,V> *L; // Left child
    mnode<K,V> *R; // Right child
    bool is_H; // for dummy head only
};

template <typename K, typename V>
class map {
    mnode<K, V> *H; // Dummy head node
    int n;       // Size of the Tree

    bool recursive_find(mnode<K,V> *ptr, const K &key) const{
        if(ptr == H){
            return false;
        } else if (ptr->key == key) {
            return true;
        } else if (key < ptr->key) {
            recursive_find(ptr->L, key);
        } else {
            recursive_find(ptr->R, key);
        }
    }

    void recursive_preorder_display(mnode<K,V> *ptr) const {
        if(ptr == H){
            return;
        } else {
            std::cout << "Key: " << ptr->key << ", Value: " << ptr->val << std::endl;
            recursive_preorder_display(ptr->L);
            recursive_preorder_display(ptr->R);
        }
    }

    void empty_map_r(mnode<K,V> *ptr){
        if(ptr == H){
            return;
        } else {
            empty_map_r(ptr->L);
            empty_map_r(ptr->R);
            delete ptr;
        }
    }

    map<K,V>* copy_r(mnode<K,V> *ptr){
        if(ptr->is_H == false) {
            mnode<K, V> *new_node = new mnode<K, V>;
            new_node->val = ptr->val;
            new_node->key = ptr->key;

            new_node->L = copy_r(ptr->L);

            if(new_node->L->is_H == false){
                new_node->L->P = new_node;
            } if (new_node->R->is_H == false) {
                new_node->R->P = new_node;
                return new_node;
            }
        } else {
            return this->H;
        }
    }

public:
    // Constructor
    map() {
        H = new mnode<K,V>; // Allocate memory for the dummy head node
        H->L = H;         // Left pointer points to itself
        H->R = H;         // Right pointer points to itself
        H->P = H;         // Parent pointer points to itself
        H->is_H = true;
        n = 0;            // Initialize tree size
    }

    ~map(){
        this->empty_map_r(H->P);
        delete this->H;
    }

    // It takes a new Key as a value and insert it in a tree
    void insert(const K &key, const V &val) {
        mnode<K,V> *new_node = new mnode<K,V>;
        new_node->key = key; // assign the value to node
        new_node->val = val;
        // Initialize left and right to dummy head node 
        new_node->L = H; 
        new_node->R = H;
        new_node->is_H = false;

        if (n == 0) { // If the tree is empty
            new_node->P = H; // Parent is dummy head
            H->P = new_node; // Root pointer in dummy head
        } else {
            mnode<K,V> *current = H->P; // Start from root node: Dummy Head parent holds the root node
            mnode<K,V> *parent = nullptr;

            // Traverse to find the correct position
            while (current != H) {
                parent = current;
                if(key == current->key){
                    delete new_node;
                    return;
                }
                else if (key < current->key)
                    current = current->L; // Go left
                else
                    current = current->R; // Go right
            }

            // Insert the new node
            if (key < parent->key) {
                parent->L = new_node;
                H->L = new_node; // dummy head left always points to lowest value in a tree
            }
            else {
                parent->R = new_node;
                H->R = new_node; // dummy head right always points to highest value in a tree
            }

            // set the parent 
            new_node->P = parent;
        }

        n++; // Increment tree size
    }

    bool find_r(const K &key) const {
        return recursive_find(H->P, key);
    }

    void clear_r() { // recursive function
        empty_map_r(this->H->P);
        // reset the dummy head node
        H->P = H;
        H->L = H;
        H->R = H;
        n = 0;
    }

    map<K,V>& operator=(const map<K,V> &obj) {
        if (this != &obj) { // Check for self-assignment
            this->clear_r(); // Clear the current map
            this->H->P = copy_r(obj.H->P); // Copy the root node
            if (this->H->P != this->H) {
                this->H->P->P = this->H; // Set the parent of the new root to the dummy head
            }
            this->H->L = obj.H->L; // Copy the leftmost node
            this->H->R = obj.H->R; // Copy the rightmost node
            this->n = obj.n; // Copy the size of the tree
        }
        return *this;
    }

    

    // Takes key as value and search for it in a tree if Yes then return true else false
    bool find(const K &key) const {

        mnode<K,V> *current = H->P; // start from root node

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

    void display_r() const {
        recursive_preorder_display(H->P);
    }
    
    // Takes key as a value and search it in a tree and delete it
    size_t erase(const K &key) {
        mnode<K, V> *current = H->P; // Start from the root
        mnode<K, V> *parent = H;     // Keep track of the parent node

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
            return -1; // Key not found
        }
        // Case 1: Deleting a leaf node
        else if (current->L == H && current->R == H) {
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
            mnode<K,V> *successor = current->R;
            mnode<K,V> *successor_parent = current;
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

    class iterator{
            mnode<K,V> *ptr;
            friend map;

        public:
            iterator() : ptr(nullptr){}

            // Check if two iterators are equal, if yes true else false & rhs param is the iterator to compare with
            bool operator!=(const iterator &rhs) const {
                return this->ptr != rhs.ptr;
            }
            // Dereferences the iterator to access the value & the value pointed to by the iterator
            std::pair<K,V> operator*() const {
                return {this->ptr->key, this->ptr->val};
            }
            // Pre-increment operator to move the iterator to the next element & return incremented iterator
            iterator operator++() {

				mnode<K,V>* ptr = this->ptr; // set current pointer to temporary pointer

				if (ptr->R->is_H != true) {
					ptr = ptr->R;

					while (ptr->R->is_H != true) {
						ptr = ptr->L;
					}

					this->ptr = ptr;
					return *this;
				}

				else {
					mnode<K,V>* _parent;
					_parent = ptr->P;

					while (ptr == _parent->R && ptr->P->is_H != true) {
						ptr = _parent;
						_parent = ptr->P;
					}

					this->ptr = _parent;
					return *this;
				}
			}

            iterator operator++(int) {
				iterator old = this->ptr;
				this->operator++();
				return old;
			}
            // Checks if two iterators are equal, true if equal else false & rhs is the iterator to compare with.
            bool operator==(const iterator &rhs) const {
                return this->ptr != rhs.ptr;
            }
            // Accesses the member of the object pointed to by the iterator & return pointer to the value
            // std::pair<K,V>* operator->(){
            //     return {&this->ptr->key, &this->ptr->val}; // return the address of value
            // }
    };

    /* Iterator functions */

    iterator begin() const{
        iterator it;
        it.ptr = H->L; // smallest node
        return it;
    }

    iterator end() const{
        iterator it;
        it.ptr = H; // Dummy head
        return it;
    }
};

int main() {
    map<int, int> tree;

    // Insert elements
    tree.insert(10, 15);
    tree.insert(5, 4);
    tree.clear_r();
    tree.insert(15, 223);
    tree.insert(3, 23);

    for (map<int,int>::iterator it = tree.begin(); it != tree.end(); ++it) {
        std::pair<int, int> data = *it; // extract the data from iterator
        std::cout << "Key: " << data.first << ", Value: " << data.second << std::endl;
    }

    return 0;
}
