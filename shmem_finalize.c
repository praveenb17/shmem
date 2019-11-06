#include<shmem_init.h>

void shmem_finalize(void)
{

	while(heap_pointer[shmem_local.my_pe]!=shmem_local.heap_start)
		shmem_free(heap_pointer[shmem_local.my_pe]);
	return;

}
