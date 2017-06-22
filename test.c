#include "malfree.h"
#include "sorted_List.h"
#include <stdlib.h>
#include <stdio.h>
#define malloc(x) myMalloc(x, __FILE__ , __LINE__)
#define free(x) myFree(x, __FILE__, __LINE__)

void v_malloc()
{
	printf("Valid Malloc Test\n");
	printf("Expected output: Successful malloc implemented!, successful free implemented!, successful malloc implemented!, successful free implemented!\n");
	char * ptr = (char *)malloc(200);
	free(ptr);
	ptr = (char *)malloc(200);
	free(ptr);

}
void non_alloc_free()
{
	printf("\nNon-allocated Pointer-Free Test\n");
	printf("Expected output: ERROR: Failure to free non-allocated pointer.\n");
	int p;
	free(&p);
}

void d_malloc_free()
{
	printf("Double Malloc Free Test\n");
	printf("Expected output: Successful malloc implemented, successful free implemented, ERROR: failed to implement free.\n");
	char *ptr = (char *)malloc(500);
	free(ptr);
	free(ptr);

}


int main(int argc, char const *argv[])
{
	v_malloc();
	non_alloc_free();
	d_malloc_free();
	return 0;
}


