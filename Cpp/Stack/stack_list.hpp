#ifndef STACK_HPP
#define STACK_HPP

#include "stack_interface.hpp"


template<typename T>
struct element {

    T value;
    element* next;

};


template<typename T>
class stack : stack_interface<T> {

    public:

        stack();
        ~stack();

        T top();
        T pop();
        void push(T value);
        bool empty();

    private:

        element<T>* first_;

        stack(const stack& s);              // Nicht-Implementierung von Copy-Konstruktor
        stack& operator=(const stack& s);   // und Zuweisungsoperator verhindert ungueltige Zeiger

};


template<typename T>
stack<T>::stack() : first_(nullptr) {

}


template<typename T>
stack<T>::~stack() {

    while (!empty())
        pop();

}


template<typename T>
T stack<T>::top() {

    if (!empty())
        return first_->value;
    else
        throw "stack is empty";

}


template<typename T>
T stack<T>::pop() {

    if (!empty()) {
        char value = first_->value;
        element<T>* e = first_->next;
        delete first_;
        first_ = e;
        return value;
    }
    else
        throw "stack is empty";

}


template<typename T>
void stack<T>::push(T value) {

    element<T>* e = new element<T>;
    e->value = value;
    e->next = first_;

    first_ = e;
}


template<typename T>
bool stack<T>::empty() {

    return first_ == nullptr;

}

#endif // STACK_HPP
