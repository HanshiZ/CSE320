/**
 * @file main.c
 * @author Hanshi Zuo
 *
 * Program to decode the images
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "stack.h"

void printX(const char* decoded);

int main(int argc, char *argv[])
{
    /** checking input */
    if (argc < 2)
    {
        printf("Usage: decoder file\n");
        return 1;
    }
    /* opening file for reading */
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Unable to open input file\n");
        return 2;
    }
    /* setting max size for key*/
    const int maxSize = 1001;
    
    char key[maxSize];         
    fgets(key,maxSize,fp);    
   
    /* above: reading key
       below: replacing newline with 0 */

    char * newline = strchr(key,10); // finding newline
    if (newline)
         (*newline) = 0;

    const int length = strlen(key); // finding length of a line

    /* initializing lines and positions within those lines in the file */
    int linepos = 0; 
    int linenum = 0;   
   
    /* stack constructor */
    struct Stack* stack = Stackconstruct();         
    /* place to hold the new chars, int because getc returns int */
    int inchr =0;
    /* temporary string */
    char * newstr = (char*)safecalloc(2*length,sizeof(char));
    while ( (inchr = fgetc(fp)) != EOF )
    {
        if (inchr  == '\n')     
        {    
             if (linepos != length)
             {
                 printf("Line lengths differ.");
                 exit(3);
             }
             linepos = 0;  //reseting position within line
             /* rotating the string */
             memmove(newstr+length, newstr, linenum % length);
             /* pushing onto stack and then reseting to 0 */
             push(stack, Nodeconstruct(newstr + linenum++ % length, length));
             memset(newstr,0,2*length*sizeof(char));
        }
        else 
        {     
              /* putting chars onto string using XOR logic */
              *(newstr + linepos) = ((char)inchr == *(key + linepos) ? '0' : '1');
              linepos = linepos + 1;
        }            
        
    }   
    fclose(fp); //closing file
    safefree(newstr); // deleting the temp string
    /* printing and deleting as we go */
    while (stack -> top)
    {
        printX(stack -> top ->str);
        Nodedel(pop(stack));
    }
    /* deleting the stack */
    Stackdel(stack);
 
    return 0;
}


/**
 * Function that prints out the Xs
 * @param decoded is the decoded strng
 */

void printX(const char* decoded)
{
     for (; *decoded ;)
          putchar(*decoded++ == '0' ? ' ' : 'X');
     putchar('\n');
}

