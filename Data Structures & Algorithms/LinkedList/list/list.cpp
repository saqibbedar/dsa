#include<iostream>

namespace my_list {

	template<typename T>

	/*
		Structure of list node:

				node
		 --------------------
		| prev | data | next |
		 --------------------

	*/

	struct node {
		node<T>*prev; // previous node
		T data; // value
		node<T>*next; // next node
	};
    
	template<typename T>

	class list {

	private:
		node<T> *H; // dummy head
		int n; // size

	public:

		// Constructor
		list() {
			// Create a dummy head node
			H = new node<T>;
			H->next = H;
			H->prev = H;
			n = 0;
		}

		~list() {
			clear(); // clear list childs
			delete H; // clear the dummy head node
		}

		void clear() {
			while (!empty())
			{
				this->pop_back();
			}
		}

		bool empty() const {
			if (this->H->next = this->H) {
				return true;
			}
			else {
				return false;
			}
		}

		void push_front(const T&val) {
			node<T>*newNode;
			newNode = new node<T>;
			if (newNode == nullptr) {
				throw("List overflow!");
			}
			newNode->data = val;
			newNode->next = this->H->next;
			newNode->prev = this->H;
			this->H->next->prev = newNode;
			this->H->next = newNode;
			this->n++;
		}

		void push_back(const T&val) {
			node<T>*newNode;
			newNode = new node<T>;
			if (newNode == nullptr) {
				throw("List overflow!");
			}
			newNode->data = val;
			newNode ->next = this->H;
			newNode->prev = this->H->prev;
			this->H->prev->next = newNode;
			this->H->prev = newNode;
			this->n++;
		}

		T front()const {
			if (this->H->next == this->H) {
				throw("List is empty!");
			}
			return this->H->next->data;
		}

		T back()const {
			if (this->H->next == this->H) {
				throw("List is empty!");
			}
			return this->H->prev->data;
		}

		void pop_front() {
			if (this->H ->next == this->H) {
				throw("List is empty!");
			}
			node<T>*temp;
			temp = this->H->next;
			this->H->next = temp->next;
			temp->next->prev = this->H;
			delete temp;
			this->n--;
		}

		void pop_back() {
			if (this->H ->next == this->H) {
				throw("List is empty!");
			}
			node <T>*temp;
			temp = this->H->prev;
			temp->prev->next = this->H;
			this->H->prev = temp->prev;
			delete temp;
			this->n--;
		}

		void unique() {
			node<T>*current;
			current = this->H->next;
			while (current->next != this->H) {
				if (current->data == current->next->data) {
					node<T>*temp;
					temp = current->next;
					current->next = temp->next;
					temp->next->prev = current;
					delete temp;
					this->n--;

				}
				current = current->next;
			}
		}

		void remove(const T&val) {
			if (this->H->next->data == val) {
				node<T>*temp;
				temp = this->H->next;
				this->H->next = temp->next;
				temp->next->prev = this->H;
				delete temp;
				this->n--;
			}
			else {
				node<T>*temp;
				temp = this->H->next;
				while(temp->next != this->H && temp->next->data != val) {
					temp = temp->next;
				}
				if (temp->next == this->H) {
					throw("Value not found!");
				}
				node<T>*temp1;
				temp1 = temp->next;
				temp->next = temp1->next;
				temp1->next->prev = temp;
				delete temp1;
				this->n--;
			}
		}

		class iterator {
			private:
				node<T>*ptr;
				friend list;
				
			public:
				bool operator!=(const iterator &rhs)const {
					return this->ptr != rhs.ptr;
				}
				bool operator==(const iterator &rhs) const {
					return this->ptr == rhs.ptr;
				}
				T operator*()const {
					return this->ptr->data;
				}
				T* operator->()const {
					return &(this->ptr->data);
				}
				iterator& operator++() {
					this->ptr = this->ptr->next;
					return*this;
				}

		};

		iterator begin()const {
			iterator it;
			it.ptr = this->H->next;
			return it;
		}

		iterator end()const {
			iterator it;
			it.ptr = this->H;
			return it;
		}

		void splice_after(iterator it, list<T>&other) {
			node<T>*pos;
			pos = it.ptr;
			if (other.H->next == other.H) {
				std::cout << "List2 is empty!";
				return;
			}
			other.H->prev->next = pos->next;
			pos->next->prev = other.H->prev;
			pos->next = other.H->next;
			other.H->next->prev = pos;

			this->n += other.n;
			other.H->next = other.H;
			other.H->prev = other.H;
			other.n = 0;
		}

		iterator insert(iterator it, const T&val) {
			node<T>*pos;
			pos = it.ptr;
			node<T>*newNode;
			newNode = new node<T>;

			newNode->data = val;
			newNode->next = pos;
			newNode->prev = pos->prev;
			pos->prev->next = newNode;
			pos->prev = newNode;
			this->n++;
			it.ptr = newNode;
			return it;
		}

	};

	template<typename T>
	void display(my_list::list<T>&l) {
		typename my_list::list<T>::iterator it;
		it = l.begin();
		std::cout << "{ ";
		while (it != l.end()) {
			std::cout << *it << ", ";
			++it;
		}
		std::cout << "}" << std::endl;
	}
}


int main() {

	my_list::list<int> l1, l2;

	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	l1.push_front(4);
	l1.clear();
	l1.push_front(5);

	l2.push_front(100);
	l2.push_front(200);

	std::cout << "List1: ";
	my_list::display(l1);

	std::cout << "List2: ";
	my_list::display(l2);

	std::cout << "List1: ";
	my_list::list<int>::iterator it;
	it = l1.begin();
	it=l1.insert(it, 11000);
	my_list::display(l1);
	
}