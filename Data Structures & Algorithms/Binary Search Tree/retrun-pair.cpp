// This program demonstrates returning a pair from a function and printing the values

#include <iostream>
#include <utility> // for std::pair

std::pair<int, int> pair_returner(int key, int value){
    return {key, value};
}

int main(){
    std::pair<int, int> data = pair_returner(10, 30);
    std::cout << "Key: " << data.first << ", Value: " << data.second << std::endl;
    return 0;
}
