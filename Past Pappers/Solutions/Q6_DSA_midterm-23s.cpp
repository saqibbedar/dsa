#include <iostream>
#include <stack>
#include <queue>
#include <list>
using namespace std;

void Q1(int n){

    //(a) What is the exact time-complexity of the given code in terms of n?
    for (int i=1; i<=n*n; i=i+3); 
    // Answer: C1x(N+1)xN || O(n^2)

    //(b) What is the exact time-complexity of the given code in terms of n?
    for (int i=1; i<n; i=i+1)
        for (int j=i; j<=n; j=j+3);
    // Answer: C1x(N-1)+C1x(N-1)xN || O(n^2)

    //(c) Which algorithm from parts (a) and (b) is more efficient and for which values of n?
    // Answer: 

    //(d) In which scenarios insertion sort is better than selection sort and vice-versa. Discuss why?

    /* Answer:

        Insertion Sort:

        Best Case: O(n) when the array is already sorted or nearly sorted.
        Worst Case: O(n^2) when the array is sorted in reverse order.

        Insertion Sort is better when the array is nearly sorted because it performs fewer shifts. It is adaptive to the input, meaning it can run in linear time if the data is already sorted or nearly sorted.

        Selection Sort:

        Best Case: O(n^2), as it always performs the same number of comparisons and swaps, regardless of the initial order of the array.
        Worst Case: O(n^2), as it always performs the same number of operations.

    */

}

void Q2(){
    /*

    (a) What is the difference between ate and app flags in fstream?

    ate: (at end) : pointer is at end but still it allows you to write at beginning of file by overwriting it while app: (append) simply append the text to file at the end of file and strict to overwrite the file contents, always write at end of file.


    //(b) What are command line arguments? Explain their usage with the help of a small example.

    Command line arguments are helpful to create a CLI application or to get arguments via CLI. when program is compiled we can run the .exe file in terminal main.exe and type arguments.

    int main(int argc, char *argv[]){
        std::string temp;
        std::ifstream f;

        for(int i=1; i<argc; ++i){
            f(argv[i]);
            if(f.isopen()){
                while(f.good()){
                    std::getline(f, temp);
                    std::cout<<temp;
                }
                std::cout<<std::endl;
            }
            f.close();
        }
    }

    //(c) While reading and displaying records (structures) from a binary file, the last record is displayed twice. What is the reason for it? How can we prevent it?

    */
}

void Q3(){
    // What would be the output of the code? In case of an error, mention it.
    stack<int> s; queue<int> q; list<int> t;

    s.push(2); 
    s.push(5); 
    s.push(7); 
    s.push(4);

    q.push(s.top()); 
    q.push(s.top()); 
    q.push(s.top()); 
    q.push(s.top());

    s.empty();

    while(!q.empty()) {
        if (s.top()%2 == 0)
            t.push_back(q.front());
        else
            t.push_front(s.top());
        q.pop();
        s.pop();
        if (s.empty())
            break;
    }

    while(!t.empty()) {
        if (t.front()%2 == 0)
            cout<<t.front()<<" ";
        else
            cout<<t.back()<<" ";
        t.pop_back();
    }

}

void Q4(){
    // For this question, write code based on following liked structures and pointer to nodes. Write independent code for each part

    /*
    head:[5|-] > [2|-] > [3|-] > ptr:[7|-] > [1|-] > tail:[9|/]
    */

   class Node
   {
        public:
        int val;
        Node *next;

        Node(int val=0): val(val), next(nullptr){}
   };

   int arr[10] = {5, 2, 3, 7, 1, 9};

   Node *head = nullptr;
   Node *tail = nullptr;
   Node *ptr = nullptr;

   for (int i = 0; i < 6; ++i){
        Node *temp = new Node(arr[i]);
        if (head == nullptr){
           head = temp;
           tail = temp;
        } else {
            if(arr[i] == 1){
                ptr = temp; // point to value 7
            }
            tail->next = temp;
            tail = temp;
        }
   }

    // (a): Display value 1
   std::cout << ptr->val <<std::endl; // output: 1
   
   // (b): Display all the values 

   ptr = head;
   while (ptr != nullptr)
   {
       std::cout << ptr->val << " ";
        if(ptr->val == 7){
            break;
        }
       ptr = ptr->next;
   }

   std::cout << std::endl;

   // (c): Create a new node, store value 4 in it and insert it after the node with value 1

   Node *newNode = new Node(4);
   newNode->next = ptr->next->next;
   ptr->next->next = newNode;

    // print all nodes to verify
   ptr = head;
   while (ptr != nullptr)
   {
       std::cout << ptr->val << " ";
       ptr = ptr->next;
   }

   // (d): Swap the nodes with values 5 and 2 (swap whole nodes, not just their data parts)

   Node *prev1 = nullptr;
    ptr = head;
   Node *prev2 = nullptr, *ptr2 = head;

   std::cout << std::endl;

   // print all nodes to verify
   ptr = head;
   while (ptr != nullptr)
   {
       std::cout << ptr->val << " ";
       ptr = ptr->next;
   }
}

int main(){

    Q4();

    return 0;
}