/**
 * @file node.h
 * Authoer: Hanshi Zuo  
 * Header for node and memory functions
 *
 */

#ifndef NODE
#define NODE

void * safecalloc(int num, int size);
void * safefree(void * ptr);

struct Node
{
   struct Node * prev;
   struct Node * next;

   char * str;
};

struct Node * Nodeconstruct(char * instr, int size);

void Nodedel(struct Node * node);

#endif
