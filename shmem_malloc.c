/******** shmem_malloc.c **********/

#include<stdio.h>
#include "shmem_malloc.h"
#include "mymalloc.h"

void *shmem_malloc(int size)
{

	  //should be declared as a global variable
    ptr = MyMalloc(size * sizeof(*ptr)); 
    if (ptr == NULL) 
	{
      	printf("Error! memory not allocated.");
     	exit(0);
    } 
    return ptr;
}


#define shmem_free() MyFree(ptr)

void *shmem_realloc(int newsize)
{
	
	if(newsize == NULL )
	{
		shmem_free();
		exit(0);
	} 
	if(newsize <= size)
	{
		printf("Error! Size should be greater than the older size");
		return ptr;
	}
	ptr = MyRealloc(ptr,newsize); //TO DO
}
