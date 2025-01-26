// Priority queue is implemented using a heap in STL and this ADT almost cover the same implementation as STL has, this is not exact same but you will have internal look of it.

#include <iostream>

namespace mystd {

    template <typename T>
    class priority_queue {
        T *data;
        int pq_size; // size of array
        int n; // no. of elements in priority_queue 

        void ReHeapUP(T arr[], int first, int last) {

            int parent = (last - 1) / 2;

            if (last == 0) {
                return;
            }

            if (arr[last] <= arr[parent]) {
                return;
            }

            std::swap(arr[last], arr[parent]);

            ReHeapUP(arr, first, parent);

        }

        void ReHeapDown(T arr[], int first, int last) {
            
            int left_child = (first * 2) + 1;
            int right_child = (first * 2) + 2;

            // If both children are out of bounds, stop
            if (left_child > last) {
                return;
            }

            // Find the largest among the current node, left child, and right child
            int max = first;
            
            // Check if left child is within bounds and larger than current
            if (arr[left_child] > arr[max]) {
                max = left_child;
            }

            // Check if right child is within bounds and larger than current max
            if (right_child <= last && arr[right_child] > arr[max]) {
                max = right_child;
            }

            // If the current node is larger than both children, stop
            if (max == first) {
                return;
            }

            // Swap with the largest child and continue heapifying
            std::swap(arr[first], arr[max]);
            ReHeapDown(arr, max, last);  // Recursively heapify the affected subtree

        }

        void display_r(T arr[], int index) const {

            if(index < 0) {
                return;
            };

            std::cout << arr[index] << " ";
            display_r(arr, index - 1);
        }

    public:

        priority_queue(int s = 100){ // constructor
            this->pq_size = s;
            this->data = new T[this->pq_size];
            this->n = 0;
        }

        ~priority_queue(){
            if(this->pq_size != 0)
                delete[] this->data;
        }

        void push(const T &val) { // inserts element and sorts the underlying container
            this->data[this->n] = val;
            ReHeapUP(this->data, 0, this->n);
            ++this->n;
        }

        void pop() { // removes the top element
            this->data[0] = data[this->n - 1];
            --this->n;
            ReHeapDown(this->data, 0, this->n-1);
        }

        T top() const {
            if(this->n == 0) {
                throw("Priority Queue Underflow");
            }
            return this->data[0];
        }

        bool empty() const { // checks whether the container adaptor is empty
            return this->n == 0;
        }

        int size() const { // returns the number of elements
            return this->n;
        }

        void swap(priority_queue<T> &obj) {
            std::swap(this->n, obj.n);
            std::swap(this->pq_size, obj.size);
            std::swap(this->data, obj.data);
        }
        
        void display() const {
            this->display_r(this->data, this->n-1);
        }

    };

}

int main() {
    mystd::priority_queue<int> pq;

    pq.push(10);
    pq.push(20);
    pq.push(50);
    pq.pop();
    pq.push(30);
    pq.push(5);
    pq.push(15);

    std::cout << "Top: " << pq.top() << std::endl;

    pq.display();
    
    return 0;
}