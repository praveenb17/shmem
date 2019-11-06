#include <shmem.h>

struct shmem_local{
	int my_pe;
	int heap_start;
}

void shmem_init(void);
