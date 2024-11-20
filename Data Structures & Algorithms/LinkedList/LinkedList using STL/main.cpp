#include <iostream>
#include <forward_list>

int main(){
    std::forward_list<int> fl;

    fl.push_front(1);
    fl.push_front(12);
    fl.push_front(5);
    fl.push_front(16);
    fl.push_front(11);
    fl.push_front(9);
    fl.push_front(19);

    auto it = fl.begin();

    while(it != fl.end()){
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    std::cout << "Forward List after sort: ";

    fl.sort();

    it = fl.begin();

    while(it != fl.end()){
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    return 0;
}