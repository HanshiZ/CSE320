
/**
 * @file stack.h
 * @author : Hanshi Zuo
 * header that declares the stack
 */
#ifndef STACK
#define STACK
#include "node.h"

struct Stack
{   
    struct Node * top;
    struct Node * bottom;
    int count;
};


struct Stack * Stackconstruct(void);

void push(struct Stack * stack, struct Node * node);

struct Node * pop(struct Stack * stack);

char * peek(const struct Stack * stack);

void Stackdel(struct Stack * stack);

#endif

