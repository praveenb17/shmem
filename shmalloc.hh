/******** shmalloc.c **********/

#include<shmem.h>

/*For allocating memory */
int *shmalloc(int size);

/* For Reallocating memory with new size */
void *shrealloc(int newsize);

/*To delete the memory */
void shfree();

