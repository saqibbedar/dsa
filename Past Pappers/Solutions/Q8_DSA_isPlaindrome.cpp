#include <iostream>
#include <stack>

template <typename T>
class Node {
public:
    T val;
    Node *next;
    Node(T val) : val(val), next(nullptr) {}
};

template <typename T>
class forward_list {
private:
    Node<T> *head;
    Node<T> *tail;
    int n; // node size

public:
    forward_list() : head(nullptr), tail(nullptr), n(0) {}

    void push_back(T val) {
        Node<T> *temp = new Node<T>(val);
        if (head == nullptr) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
        ++n;
    }

    void pop_back() {
        if (tail == nullptr) {
            return;
        }
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node<T> *it = head;
            while (it->next != tail) {
                it = it->next;
            }
            delete tail;
            tail = it;
            tail->next = nullptr;
        }
        --n;
    }

    bool isPalindrome() {
        if (head == nullptr) {
            return true;
        }

        std::stack<T> s;
        Node<T> *it = head;
        while (it != nullptr) {
            s.push(it->val);
            it = it->next;
        }

        it = head;
        while (it != nullptr) {
            if (it->val != s.top()) {
                return false;
            }
            s.pop();
            it = it->next;
        }
        return true;
    }

    ~forward_list() {
        Node<T> *it = head;
        while (it != nullptr) {
            Node<T> *temp = it->next;
            delete it;
            it = temp;
        }
    }
};

int main() {
    forward_list<char> fl;
    fl.push_back('r');
    fl.push_back('a');
    fl.push_back('c');
    fl.push_back('e');
    fl.push_back('c');
    fl.push_back('a');
    fl.push_back('r');

    if (fl.isPalindrome()) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}