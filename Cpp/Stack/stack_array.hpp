#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include <exception>

#include "stack_interface.hpp"


class stack_full : std::exception {

    public:

        const char* what() const throw() {
            return "stack is full";
        }

};


template<int MAX_SIZE, typename T>
class stack : stack_interface<T> {

    public:

        stack();
        ~stack();

        T top();
        T pop();
        void push(T value);

        bool empty();
        bool full();

    private:

        T *values_;
        int index_;

        stack(const stack& s);              // Nicht-Implementierung von Copy-Konstruktor
        stack& operator=(const stack& s);   // und Zuweisungsoperator verhindert ungueltige Zeiger

};


template<int MAX_SIZE, typename T>
stack<MAX_SIZE, T>::stack() :
    values_(new T[MAX_SIZE]),
    index_(-1)
{}


template<int MAX_SIZE, typename T>
stack<MAX_SIZE, T>::~stack()
{
    delete[] values_;
}


template<int MAX_SIZE, typename T>
T stack<MAX_SIZE, T>::top() {

    if (!empty())
        return values_[index_];
    else
        throw stack_empty();

}


template<int MAX_SIZE, typename T>
T stack<MAX_SIZE, T>::pop() {

    if (!empty())
        return values_[index_--];
    else
        throw stack_empty();

}


template<int MAX_SIZE, typename T>
void stack<MAX_SIZE, T>::push(T value) {

    if (!full())
        values_[++index_] = value;
    else
        throw stack_full();

}


template<int MAX_SIZE, typename T>
bool stack<MAX_SIZE, T>::empty() {

    return index_ == -1;

}


template<int MAX_SIZE, typename T>
bool stack<MAX_SIZE, T>::full() {

    return index_ == MAX_SIZE;

}

#endif // STACK_ARRAY_HPP
