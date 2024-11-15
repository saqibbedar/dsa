//Array based queue
//FIFO principle
#include<iostream>

template<typename T>
class queue
{
public:
    T* data;
    int Size; int n;
    int F, B;
    template <typename U>
    friend bool operator ==(const queue<U>& rhs, const queue <U>& lhs);
    template <typename U>
    friend bool operator <(const queue<U>& rhs, const queue <U>& lhs);
    //constructor
    queue(int s = 0)
    {

        Size = s;
        n = 0;
        data = new T(Size);
        this->F = 0;
        this->B = 0;
    }
    //push
    void push(const T& val)
    {
        this->B = (this->B + 1) % (this->Size);
        if (this->F == this->B)
        {
            throw("Queue overflow");
            this->B = n - 1;
        }
        this -> data[this->B] = val;
        ++this->n;
    }
    //Pop
    void pop()const
    {//always pop from front in queue
        if (this->F == this->B)
        {
            throw("queue underflow");
        }
        this->F = (this->F + 1) % this->Size;
        --this->n;
    }
    //front
    T front()
    {
        if (this->F == this->B)
        {
            throw("queue underflow");

        }
        return this->data[(this->F + 1) % this->Size];
    }
    //empty
    bool empty()const
    {
        return this->F == this->B;
    }
    //size;
    int size()const
    {
        return this->n;
    }

};
//non member  comparison operators
template <typename T>
//Equality 
bool operator==(const queue<T>& rhs, const queue <T>& lhs)
{
    bool flag = true;
    if (rhs.size() != lhs.size())
    {

        return false;

    }
    else {


        for (int i = 0; i < rhs.n; ++i)
        {

            if (rhs.data[i] != lhs.data[i])
            {
                flag = false;
                break;
            }
        }
    }
    if (flag)
    {

        return flag;
    }

}
//less than operator
template <typename T>
bool operator <(const queue<T>& rhs, const queue <T>& lhs)
{
    bool flag1 = true;
    int i;
    for (i = 0; i < rhs.n && lhs.n; ++i)
    {
        if (lhs.data[i] > lhs.data[i])
        {
            return false;
            break;
        }
        else if (lhs.data[i] == rhs.data[i])
        {
            return false;
        }

    }
    if (flag1 == true)
    {
        return true;
        

    }
    return false;
}
int main()
{
    queue<int> q1(30);
    queue<int> qq1(30);
    q1.push(3);
    q1.push(4);
    q1.push(5);
    q1.push(6);
    qq1.push(3);
    qq1.push(4);
    qq1.push(5);
    qq1.push(6);
    if (q1 == qq1)
    {
        std::cout << "both are equal" << std::endl;
    }
    if (q1 < qq1)
    {
        std::cout << "first is less than second " << std::endl;
    }
    else// if not less may be greater or equal

    {
        std::cout << "first is greater or equal   " << std::endl;
}
}