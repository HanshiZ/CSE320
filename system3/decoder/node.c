/**
 * @file node.c
 * @author Hanshi Zuo
 * definitions for our nodes
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

/**
 * Constructor for the node
 * @param instr string to be in the node
 * @param size the size of the string without 0
 * @return the node * that is created
 */
struct Node * Nodeconstruct(char * instr, int size)
{
   struct Node * Return = (struct Node *)safecalloc(1,sizeof(struct Node));
   Return->prev = 0;
   Return->next= 0;
   Return ->str = (char*) safecalloc(size+1, sizeof(char));
   memcpy(Return->str,instr,size);
   return Return;
}

/**
 *  destructor for the Node
 *  @param node node pointer to be freed
 */
void Nodedel(struct Node * node)
{
    safefree(node -> str);
    safefree(node);
}

/**
 * function to make sure memory actually allocated
 * @param num is the size of array
 * @param size is the size of the object in array
 * @return a void pointer or Null dependign on success
 */

void * safecalloc(int num, int size)
{
    void * test =calloc(num, size);
    if (test != NULL)
        return test;

    else
        printf("*Memory allocation failed.*");
    exit(EXIT_FAILURE);
    return 0;
}

/**
 * function that sets deleted memory to null
 * to prevent dereferncing
 * @param ptr is the ptr to be deleted
 * @return a Null pointer
 */

void * safefree(void * ptr)
{
    free(ptr);
    ptr = 0;
    return ptr;
}

