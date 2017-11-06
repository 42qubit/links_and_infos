#ifndef STACK_INTERFACE_HPP
#define STACK_INTERFACE_HPP

#include <exception>


class stack_empty : std::exception {

    public:

        const char* what() const throw() {
            return "stack is empty";
        }

};


template<typename T>
class stack_interface
{

    public:

        virtual T top() = 0;
        virtual T pop() = 0;
        virtual void push(T value) = 0;

};

#endif // STACK_INTERFACE_HPP
