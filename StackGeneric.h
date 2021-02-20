#if !defined(STACKGENERIC_H)
#define STACKGENERIC_H

typedef struct Stack {
    int datatype;
    void* data;
    int top;
    int capacity;

}Stack;

int pop(Stack *stack , void* target);
int push(Stack *stack , void *element);
int isFull(Stack *stack);
Stack *stackCreate(size_t datasize , int capacity);


#endif // STACK_H
