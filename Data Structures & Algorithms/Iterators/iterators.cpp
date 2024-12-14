// Iterators: are used with general purpose abstract data types i.e., linkedlist(singly, doubly), trees, has tables. These are helpful to traverse over these data structures. Below is the simple traversal of singly linkedlist using iterators.

#include <iostream>
#include <forward_list>

int main(){
    std::forward_list<int> fl;
    fl.push_front(10);
    fl.push_front(20);
    fl.push_front(30);
    fl.push_front(40);
    fl.push_front(50);

    std::forward_list<int>::iterator it = fl.begin();
    // auto it = fl.begin(); // above statement is also valid and this too but this one is shorthand for above.

    while (it != fl.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    
    return 0;
}