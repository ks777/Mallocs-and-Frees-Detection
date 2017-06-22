#ifndef MALFREE_H
#define MALFREE_H
#include "sorted_List.h"

struct memory_Entry  // Memory entry structure.
{
	unsigned int size;
    unsigned int isFree;
    struct memory_Entry *previous;
    struct memory_Entry *next;
};
typedef struct memory_Entry memoryEntry;

void myFree(void * x, char * y, int z); // The revised Free function. Takes in a void pointer and doesn`t return anything, yet will print any errors.

void* myMalloc(unsigned int x, char * y, int z); // The revised Malloc Function. Takes in an integer for the size of the block (x), filename string (y), and the line number integer (z). Returns a pointer to the data on success, otherwise 0.

int ptrcmp(void * pointer1, void * pointer2); // Comparator function for the Sorted List.
#endif
