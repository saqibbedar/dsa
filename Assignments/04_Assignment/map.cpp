#include <iostream>
#include <string>

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
            mnode<K, V> *nn = new mnode<K, V>; // nn: new_node
            nn->key = key;
            nn->val = val;
            nn->is_H = false;
            nn->L = this->H;
            nn->R = this->H;

            if(n == 0) { // 2. set root node
                nn->P = this->H;
                this->H->P = nn;
                this->H->L = nn;
                this->H->R = nn;
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
                } else {
                    parent->R = nn;
                }

                // 6. Set dummy heads left and right to point smaller and larger values
                if (key < H->L->key) {
                    H->L = nn;
                }else{
                    H->R = nn;
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

        bool empty() const { // checks whether the container is empty
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

        void clear() const { // Erases all elements from the container
            mnode<K, V> *current = this->H;
            mnode<K, V> *parent = nullptr;

            while(current != this->H) {
                
            }
        }


        class iterator {
            mnode<K, V> *ptr;
            friend map<K,V>;

            public: 

            iterator(){
                this->ptr = nullptr;
            }

            bool operator!=(const iterator &rhs) const {
                return this->ptr != rhs.ptr;
            }

            bool operator==(const iterator &rhs) const {
                return this->ptr == rhs.ptr;
            }

            std::pair<K,V> operator*() const { // Dereferences the iterator to access the key & the value pointed by the iterator
                return {this->ptr->key, this->ptr->val};
            }

            // std::pair<K, V>* operator->() const { // Accesses the member of the object pointed to by the iterator & return pointer to the value
            //     return std::pair<K,V>(this->ptr->key,this->ptr->val);
            // }

            iterator operator++() {
                mnode<K, V> *ptr = this->ptr; // store the current pointer in ptr

                if(ptr->R->is_H != true){
                    ptr = ptr->R;
                    while(ptr->L->is_H != true){
                        ptr = ptr->L;
                    }
                    this->ptr = ptr;
                    return *this;
                } else {
                    mnode<K, V> *parent = ptr->P;
                    while(ptr == parent->R && ptr->P->is_H != true) {
                        ptr = parent;
                        parent = ptr->P;
                    }
                    this->ptr = parent;
                    return *this;
                }
            }

        };

        // K& operator[](const K &key) { // access or insert specified element

        // }

        iterator find(const K &key) const { // finds element/node with specific key

            mnode<K, V> *current = this->H->P; // start from root node

            while(current != this->H){
                if(key == current->key) {
                    iterator it; // iterator to return element found
                    it.ptr = current;
                    return it;
                } else if (key < current->key) {
                    current = current->L;
                } else {
                    current = current->R;
                }
            }

            return this->end();
        }

        iterator begin() const {
            iterator it;
            it.ptr = this->H->L; // assign smallest node
            return it;
        }

        iterator end() const {
            iterator it;
            it.ptr = this->H; // assign dummy head - nullptr
            return it;
        }

};


int main() {
    map<int, std::string> m;

    m.insert(1, "one");
    m.insert(3, "three");
    m.insert(2, "two");
    m.insert(3, "three");
    m.insert(3, "three");
    m.insert(4, "four");
    m.insert(6, "six");

    std::cout << "Contains key 1: " << m.contains(1) << std::endl;
    std::cout << "Contains key 4: " << m.contains(4) << std::endl;

    std::cout << "Size of map: " << m.size() << std::endl;

    map<int, std::string>::iterator it = m.begin(); 

    while (it != m.end()) {
        std::pair<int, std::string> data = *it;
        std::cout << "Key: " << data.first << ", Value: " << data.second << std::endl;
        ++it;
    }

    return 0;
}