/*

Name: Muhammad Saqib
RegNo: 037
Semester: 3rd

Task 3: Implement the operator== and operator< functions (ADT code) for array-based Queue ADT.

*/

#include <iostream>
#include <iostream>
using namespace std;

template <typename T>
class queue{
    // indexes managers
    int front; // head index
    int back; // tail index
    int size; // size of array
    int n; // size of queue's element

    T *arr;

public:

    // constructor
    queue(int queue_size = 100): size(queue_size + 1), n(0), front(0), back(0) {
        arr = new T[size];
    }

    void push(T val){

        this->back = (this->back + 1) % this->size; // get the current index

        if(this->back == this->front){
            throw("Queue overflow");
        }

        this->arr[this->back] = val; // assign value
        ++this->n; // increment queues elem size
    }

    void pop(){
        if(this->front == this->back){
            throw("Queue Underflow");
        }
        this->front = (this->front + 1) % this->size; // take front to next index
        --this->n; // decrement queues elem size
    }

    T getFront() const {
        if(isEmpty()){
            throw("Queue Underflow");
        }
        return this->arr[this->front + 1];
    }

    T getBack() const {
        if(isEmpty()){
            throw("Queue Underflow");
        }
        return this->arr[this->back];
    }

    int getSize() const {
        return n; // return queues elem size
    }

    bool isEmpty() const {
        return this->front == this->back; // does both same index? true : false
    }

    // destructor
    ~queue(){
        delete[] arr; // free memory
    }

    // Non-Member functions
    friend bool operator==(const queue<T>& lhs, const queue<T>& rhs){
        
        if(lhs.n != rhs.n){
            return false;
        } else {
            for (int i = 0, j = 1; i < lhs.getSize(); ++i, ++j){
                // std::cout <<"Debug: "<< lhs.arr[j] << ", " << rhs.arr[j] << std::endl;
                if(lhs.arr[j] != rhs.arr[j]){
                    return false;
                }
            }
            return true;
        }

    }

    friend bool operator<(const queue<T>& lhs, const queue<T>& rhs){
        if(lhs.n > rhs.n){
            return false;
        } else {
            for (int i = 0, j = 1; i < lhs.getSize(); ++i, ++j){
                // std::cout <<"Debug: "<< lhs.arr[j] << ", " << rhs.arr[j] << std::endl;
                if(lhs.arr[j] > rhs.arr[j]){
                    return false;
                }
            }
            return true;
        }
    }

    friend bool operator>(const queue<T>& lhs, const queue<T>& rhs){
        return lhs < rhs;
    }
};

int main(){
    try
    {
        queue<int> q(5);

        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);
        // q.push(9);

        queue<int> q2(5);

        q2.push(1);
        q2.push(2);
        q2.push(3);
        q2.push(4);
        q2.push(5);

        if(q == q2){
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }

        if(q < q2){
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }


    }
    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }
    return 0;
}