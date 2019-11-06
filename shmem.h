#include <stdint.h>
#include <pthread.h>

#define SHMEM_MAX_PES      6
#define SHMEM_BASE_COREID  ____

#define HEAP_START 0x________ //address of shared heap
#define NUM_SECTIONS 6 // num of sections into which shared memory is split up for locking

typedef struct
{
	void*    src_addr;
	void*    dst_addr;
} __attribute__((aligned(8))) shmem_dma_desc_t; //

struct shmem_internals_t{
	int n_pes;
	int barrier[6];
	pthread_mutex_t lock[NUM_SECTIONS];
	shmem_dma_desc_t dma_desc;
} __attribute__ ((section(".shared_heap_meta"))) shmem_internals;

char * __attribute__ ((section(".shared_heap_meta"))) heap_pointer[NUM_SECTIONS];

