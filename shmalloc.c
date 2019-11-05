/******** shmalloc.h **********/

#include<stdio.h>

int *ptr;  s

int *shmalloc(int size)
{
	  
    //ptr = malloc(size * sizeof(*ptr)); //We are usig mymalloc()
    if (ptr == NULL) 
	{
      	printf("Error! memory not allocated.");
     	exit(0);
    } 
    return ptr;
}


#define shfree() free(ptr)

void *shrealloc(int newsize)
{
	
	if(newsize == NULL )
	{
		shfree();
		exit(0);
	} 
	if(newsize <= size)
	{
		printf("Error! Size should be greater than the older size");
		return ptr;
	}
	ptr = realloc (ptr,newsize);
}
