#include <stdio.h>
#include "StackGeneric.h"
#include <stdlib.h>
#include <string.h>

Stack *stackCreate(size_t datasize , int capacity) {
    Stack *stack = (malloc(sizeof(Stack)));
    stack->datatype = datasize;
    stack->capacity = capacity;
    stack->data = malloc(capacity * datasize);
    stack->top = -1;
    return stack;
}

int isFull(Stack *stack) {
    return (stack->capacity - 1 == stack->top);
}
 
int push(Stack *stack , void *element) {
    // first check if the stack is full
    if(isFull(stack)) return 0 ;
    stack->top ++; 
    void *position = (char*)stack->data + (stack->top * stack->datatype);
    memcpy(position,element,stack->datatype);
    return 1;
}

int pop(Stack *stack , void* target) {
    void* source = (char*)stack->data + (stack->top * stack->datatype);
    stack->top --;
    memcpy(target, source, stack->datatype);
    return 0;    
}
