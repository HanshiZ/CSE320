/**
 * Author : Hanshi Zuo
 * File binarymath.h
 * declarations for binary functions
 *
*/
#ifndef BINMATH
#define BINMATH
#pragma once

/// The size of the binary numbers to use
#define BINARY_SIZE 100

void * safecalloc(int num, int size);
void * safefree(void * ptr);

char * inc(const char * bitstring);
char * negate(const char * bitstr);


char * add(const char* add1, const char * add2);
char * sub(const char* sub1, const char * sub2);


#endif
