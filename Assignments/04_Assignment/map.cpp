#include <iostream>

template<typename K, typename V>
struct mnode {
    mnode<K,V> *P; // parent
    K key;
    V val;
    bool is_H;
    mnode<K,V> *L; // Left
    mnode<K,V> *R; // Right
};


template<typename K, typename V>
class map{
    mnode<K,V> *H; // dummy head
    int n; // size of map

    public:
        map(){ // constructor
            this->H = new mnode<K, V>;
            this->H->P = this->H;
            this->H->is_H = true;
            this->H->L = this->H;
            this->H->R = this->H;
            this->n = 0;
        }

        void insert(const K &key, const V &val) { // inserts elements or nodes

            // 1. Create a new node
            mnode<K, V> nn = new mnode<K, V>; // nn: new_node
            nn->key = key;
            nn->val = val;
            nn->is_H = false;
            nn->L = this->H;
            nn->R = this->H;

            if(n == 0) { // 2. set root node
                nn->P = this->H;
                this->H->P = nn;
            } else { // 3. Insert new node at correct position

                mnode<K, V> *current = H->P; // Start from root node to find position where to insert the value
                mnode<K, V> *parent = nullptr;

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
                    this->H->L = nn;
                } else {
                    parent->R = nn;
                    this->H->R = nn;
                }

                // Set the parent
                nn->P = parent;
            }

            ++this->n; // increment size
        }

        bool contains(const K &key) const { // checks if the container contains element with specific key

            mnode<K, V> *current = this->H->P; // start from root node

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

        bool clear() const { // checks whether the container is empty
            return this->n == 0;
        }

        int size() const { // returns the number of elements/nodes
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

        class iterator {
            mnode<K, V> *ptr;
            friend map<K,V>;

            public: 

            iterator(){
                this->ptr = nullptr;
            }

        };

        K& operator[](const K &key) { // access or insert specified element

        }

        iterator find(const K &key) const { // finds element/node with specific key

            iterator *it; // iterator to return element found

            mnode<K, V> *current = this->H->P; // start from root node

            bool flag = false; // track if node was found?

            while(current != this->H){
                if(key == current->key) {
                    flag = true;
                    it->ptr = current;
                    return it;
                } else if (key < current->L) {
                    current = current->L;
                } else {
                    current = current->R;
                }
            }

            if(flag) { // if element was not found then return root node
                it->ptr = this->H->P;
                return it;
            }

        }

        iterator begin() const {
            iterator *it;
            it->ptr = this->H->L; // assign smallest node
            return it;
        }

        iterator end() const {
            iterator *it;
            it->ptr = this->H; // assign dummy head - nullptr
            return it;
        }

};
