// Chaining Based Hash Tables
// Note: This ADT is not fully implemented yet, soon it will be updated.

#include <iostream>
#include <forward_list>

template <typename K, typename V>
class unordered_map{
    std::forward_list<std::pair<K, V>> *DATA;
    int SIZE;
    int n;

    int hash(K key) {
        return key % SIZE;
    }

public:
    unordered_map(int size){
        this->SIZE = size / 5;
        DATA = new std::forward_list<std::pair<K, V>>[this->SIZE];
    };

    ~unordered_map(){
        delete this->DATA;
    }

    void insert(const std::pair<K,V> & data){
        int index = this->hash(data.first);
        
        for (int i = 0; i < this->SIZE; ++i) {
            if(data[index] == -1) {

            }
        }
    } 

    

};

int main(){

    return 0;
}
