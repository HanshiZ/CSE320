/**
 * @file stack.c
 * @author Hanshi Zuo
 * definitions for the stack functions
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "node.h"   

/**
 * constructor for the stack, pointers to NULL
 * @return pointer to the stack
 */
struct Stack * Stackconstruct(void)
{
    struct Stack *Return = (struct Stack *)safecalloc(1, sizeof(struct Stack));
    Return->top= NULL;
    Return->bottom= NULL;
    Return->count = 0;
    return Return;
}

/**
 * pushing node onto stack
 * @param stack stack that is being used
 * @param node node to be added
 */
void push(struct Stack * stack, struct Node * node)
{
    if (node -> prev || node -> next)
        printf("Error, node already linked");
    else 
    {   if (stack->count)   // case where not at the bottom
        {   
             stack -> top -> prev = node;
             node -> next = stack -> top;
        }
        else        // case when top and bottom the same
            stack -> bottom = node;        

        stack -> top = node; 
        
        ++(stack->count);
    }
}

/**
 * function that pops off the top of the stack
 * @param stack with the nodes
 * @return Node that is at the top of the stack 
 */
struct Node * pop(struct Stack * stack)
{
     if (!(stack->count))    // NULL pointer for empty stack  
         return NULL;
     
     struct Node * out =  stack -> top;
     if (stack -> top -> next)    // if not the bottom
     {
         stack -> top = stack -> top -> next;    
         stack -> top -> prev = 0;
     }
      else      //case for dealing with bottom of stack
         stack -> top = 0;
     
     out -> next = 0;     

     --(stack -> count);
     return out; 
}

/**
 *  taking a look at the top of the stack
 *  @param stack stack that is being looked at  
 *  @return the string that the node at the top holds
 */
char * peek(const struct Stack * stack)
{
     return (stack -> top -> str);
}

/**
 * destructor for the stack
 * @param stack to be destroyed
 */
void Stackdel(struct Stack * stack)
{
    while (stack -> count)
       Nodedel(pop(stack));
    safefree(stack);
}

