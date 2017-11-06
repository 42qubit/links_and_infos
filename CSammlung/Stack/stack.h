#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct stack {

    char *array;
    int length;

};


struct stack *new_stack() {

    struct stack *stck = (struct stack*) malloc (sizeof(struct stack));
    stck->array = (char*) malloc (0);
    stck->length = 0;
    return stck;

}


int empty(struct stack *stck) {
    return stck->length == 0;
}


char top(struct stack *stck) {

    if (empty(stck))
        return '\0';
    else
        return stck->array[stck->length-1];

}


void push(struct stack *stck, char value) {

    stck->length ++;
    stck->array = (char*) realloc ( stck->array, stck->length*sizeof(char) );
    stck->array[stck->length-1] = value;

}


char pop(struct stack *stck) {

    if (empty(stck))
        return '\0';

    char value = top(stck);
    stck->length --;
    stck->array = (char*) realloc ( stck->array, stck->length*sizeof(char) );
    return value;

}

#endif // STACK_H
