#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* worker(void *data) {
	int* ptr = (int*) malloc (sizeof(int));
	*ptr = 7;
	printf("malloc returned in worker %u\n",ptr);
	//free(ptr);
	printf("thread returning\n");
	return NULL;
}

void main() {

	int i; int *ptr;
	for (i=0; i < 20; i++) {
		ptr = (int*) malloc(sizeof(int));
		*ptr = 6;
		printf("pointer got = %u\n",ptr);
		free(ptr);
	}
	ptr = (int*) malloc(sizeof(int)*20);
	for (i = 0; i < 20; i++) {
		ptr[i] = i;
	}

	const int NUM_THREADS = 20;
	pthread_t threads[NUM_THREADS];
	printf("*****JUST BEFORE CREATING THREADS****\n");	
	for (i=0; i < NUM_THREADS ; i++)
		pthread_create(&threads[i],NULL,&worker,NULL);
	
	for (i = 0 ; i < NUM_THREADS; i++) {
		pthread_join(threads[i],NULL);
	}
	printf("test client \n");
}

