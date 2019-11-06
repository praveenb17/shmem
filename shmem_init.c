void shmem_init()
{	
	int i=0;
	shmem_local.my_pe = -1;

	//copy CPUID into my_pe
	asm ("mov %0, CPUID"
		:"=m" (shmem_local.my_pe));

	if(shmem_local.my_pe == -1)
		exit(0); //core not in use
	else{
		while(i++!=6)
			if(shmem_local.my_pe==i)
				shmem_internals.n_pes++;
	}
	//if(shmem_local.my_pe == 0)
	//	shmem_internals.n_pes = 6;
	
	shmem_local.heap_start = HEAP_START + my_pe*HEAP_SIZE;

	shmem_internals.barrier[shmem_local.my_pe]=0;

	if (pthread_mutex_init(&shmem_internals.lock[shmem_local.my_pe], NULL) != 0) 
	    { 
		printf("\n mutex init has failed\n"); 
		return 1; 
	    }
	shmem_internals.heap_pointer[my_pe] = shmem_local.heap_start;
}	
