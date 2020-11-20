#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarymath.h"

const int chrsiz = sizeof(char);

/**
 * Increment a BINARY_SIZE binary number expressed as a 
 * character string.
 * @param bitstring  The number we are passed
 * @returns Incremented version of the number
 */
char * inc(const char * bitstring)
{
    char * new = (char*) safecalloc(BINARY_SIZE+1, chrsiz);  
    
    char * lastzero = strrchr(bitstring, '0') ;
    int location = (lastzero ? lastzero - bitstring: -1);
    
    if (location > -1)
    {    
        memcpy(new, bitstring , chrsiz * location);
        *(new + location) = '1';
        if (location++ < BINARY_SIZE)
            memset(new + location, '0', BINARY_SIZE - location);
    }
    
    else 
        memset(new, '0', BINARY_SIZE);
    return new;
        
}

/**
 * Negate a BINARY_SIZE binary number expressed as a character string
 * @param bitstr The number we are passed
 * @returns Incremented version of the number
 */
char* negate(const char * bitstr)
{
    char * temp = (char*) safecalloc(BINARY_SIZE+1, chrsiz);
    for (int iterator= 0; iterator < BINARY_SIZE; iterator++)
        *(temp+iterator) = ( *(bitstr+iterator) == '1' ? '0' :'1');
    
    char * final = inc(temp);
    safefree(temp);
    
    return final;
}

/**
 * Add two BINARY_SIZE binary numbers expressed as
 * a character string. 
 * @param add1 First number to add
 * @param add2 Second number to add
 * @return a + b
 */

char * add (const char* add1, const char* add2)
{   
   short sum =0;
   char * new = (char*) safecalloc(BINARY_SIZE+1, chrsiz);
   
   for (int iterator = BINARY_SIZE ; iterator;)
   {	
       if (*(add1 +--iterator) == '1')
           ++sum ; 

       if (*(add2 + iterator) == '1')
           ++sum;

       *(new + iterator) = ( sum % 2 ? '1':'0'); 	
       sum = (sum > 1 ? 1 : 0 );
   }               
   return new; 
  
}

/**
 * Subtract two BINARY_SIZE binary numbers expressed as
 * a character string.
 * @param sub1 First number
 * @param sub2 Second number 
 * @return a - b
 */
char * sub(const char * sub1, const char * sub2)
{    
    char * temp = negate(sub2);
    char * difference = add(sub1,temp); 
    safefree(temp);
    return difference;
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
