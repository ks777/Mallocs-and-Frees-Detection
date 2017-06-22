#include "malfree.h"
#include "sorted_List.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

sorted_List_Ptr point;

void * myMalloc(unsigned int x, char * y, int z)
{
	void *return_Ptr;	//Return point
	memoryEntry *ptr;
	memoryEntry *next;
	static memoryEntry *front = 0;	//points to front of memoryEntry list
	static memoryEntry *back = 0;	//points to back of memoryEntry list
	ptr = front;
	while(ptr != 0)
	{
		if(ptr->isFree == 0 || (ptr->size < x))
		{
			ptr = ptr->next;
		} else if(ptr->size < (x + sizeof(memoryEntry)))
		{
			ptr->isFree = 0;
			return_Ptr = (char *)ptr + sizeof(memoryEntry);
			sorted_List_Insert(point, return_Ptr);

			printf( "Allocated block 0x%x\n" , return_Ptr);
			return return_Ptr;
		} else
		{
			next = (memoryEntry *)((char *)ptr + sizeof(memoryEntry) + x);
			next->previous = ptr;
			next->next = ptr->next;
			if(ptr->next != 0)
			{
				ptr->next->previous = next;
			}
			ptr->next = next;
			next->size = ptr->size - sizeof(memoryEntry) - x;
			next->isFree = 1;
			ptr->size = x;
			ptr->isFree = 0;
			if (ptr == back)
			{
				back = next;
			}
			return_Ptr = (char *)ptr + sizeof(memoryEntry);
			// Adding this block to the list of blocks.
			sorted_List_Insert(point, return_Ptr);

			printf( "Allocated block 0x%x\n" , return_Ptr);
			return return_Ptr;
		}
	}
	ptr = (memoryEntry *)sbrk(x + sizeof(memoryEntry));
	if(ptr == (void *)-1)
	{
		printf( "Error: Malloc failed in file %s at line %d\n" , y, z);
		return 0;
	} else if(back == 0)
	{
		ptr->previous = 0;
		ptr->next = 0;
		ptr->size = x;
		ptr->isFree = 0;
		front = ptr;
		back = ptr;
		return_Ptr = (char *)ptr + sizeof(memoryEntry);
		point = sorted_List_Create(ptrcmp);
		sorted_List_Insert(point, return_Ptr);

		printf( "Allocated block 0x%x\n" , return_Ptr);
		return return_Ptr;
	} else
	{
		ptr->previous = back;
		ptr->next = back->next;
		ptr->size = x;
		ptr->isFree = 0;
		back->next = ptr;
		back = ptr;
		return_Ptr = (char *)ptr + sizeof(memoryEntry);
		sorted_List_Insert(point, return_Ptr);

		printf( "Allocated block 0x%x\n" , return_Ptr);
		return return_Ptr;
	}
	printf( "Error: Malloc failed in file %s at line %d\n" , y, z);
	return 0;
}

void myFree(void * x, char * y, int z)
{
	memoryEntry *ptr;
	memoryEntry *previous;	//memoryEntry for the previous block
	memoryEntry *next;	//memoryEntry for the next block

	if(point == NULL)
	{
		printf( "Error: No malloc memory in the list. Failed to free.\n" );
		return;
	} if(sorted_List_Find(point, x) == NULL)
	{
		printf( "Error: This memory point was never malloc in the list. Failed to free.\n" );
		return;
	}

	ptr = (memoryEntry *)((char *)x - sizeof(memoryEntry));

	if((previous = ptr->previous) != 0 && previous->isFree)
	{
		previous->size += sizeof(memoryEntry) + ptr->size;
		previous->next = ptr->next;
		ptr->isFree = 1;
		previous->next = ptr->next;
		if(ptr->next != 0)
		{
			ptr->next->previous = previous;
		}

		sorted_List_Remove(point, x);
	} else
	{
		if (ptr->isFree == 0)
		{
		    sorted_List_Remove(point, x);
		    ptr->isFree = 1;
		    previous = ptr;
		    printf( "Freed block 0x%x\n" , x);
		} else
		{
			printf( "Error: Attempted to double free a point. Failed to free.\n" );
		}
	}
	if((next = ptr->next) != 0 && next->isFree)
	{
		previous->size += sizeof(memoryEntry) + next->size;
		previous->next = next->next;
		previous->isFree = 1;
		if(next->next != 0)
		{
			next->next->previous = previous;
		}

		sorted_List_Remove(point, x);
	}
}


int ptrcmp(void * pointer1, void * pointer2)
{
	return pointer1 - pointer2;
}
