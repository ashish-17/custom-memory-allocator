/*
 * CacheScratch.c
 *
 *  Created on: 13-Jul-2015
 *      Author: architaagarwal
 */
// This is also known as "Passive False"
// Command line arguments:
// <allocator flag> <nThreads> <objSize> <nIterations> <nTimesToWriteOnEachByte>
// each thread allocates nIterations times objects of size objSize
// and write on each byte of the object nTimesToWriteOnEachByte times.

#include <pthread.h>
#include <stdio.h>
#include "../../allocators/WaitFreeMemAlloc/src/WaitFreePool.h"
//#include "../../utils/mini-logger/logger.h"
#include <stdlib.h>
#include <sys/time.h>

typedef struct _ThreadData {
	int allocatorNo;
	int nThreads;
	int objSize;
	int iterations;
	int repetitions;
	int threadId;
	void *obj;
} ThreadData;


void* worker(void *data) {
	//	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	free(threadData->obj);
	for (int i = 0; i < threadData->iterations; i++) {
		char* ptr = malloc(threadData->objSize);
		// Write into ptr a bunch of times
		for (int j = 0; j < threadData->repetitions; j++) {
			for  (int k = 0; k < threadData->objSize; k++) {
				*(ptr + k) = (char)k;
				char temp = *(ptr + k);
				temp++;
			}
		}
		free(ptr);
	}
	//	LOG_EPILOG();
	return NULL;
}

void workerWaitFreePool(void *data) {
	//	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	freeMem(threadData->threadId, threadData->obj);
	for (int i = 0; i < threadData->iterations; i++) {
		char* ptr = allocate(threadData->threadId, 0);
		//		LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		// Write into ptr a bunch of times
		for (int j = 0; j < threadData->repetitions; j++) {
			for  (int k = 0; k < threadData->objSize; k++) {
				*(ptr + k) = (char)k;
				char temp = *(ptr + k);
				temp++;
			}
		}
		freeMem(threadData->threadId, ptr);
	}
	//	LOG_EPILOG();
}


int main(int argc, char* argv[]) {
	//LOG_INIT_CONSOLE();
	//LOG_INIT_FILE();
	//	LOG_PROLOG();

	int allocatorNo, nThreads, objSize, iterations, repetitions;

	if (argc == 6) {
		allocatorNo = atoi(argv[1]);
		nThreads = atoi(argv[2]);
		objSize = atoi(argv[3]);
		iterations = atoi(argv[4]);
		repetitions = atoi(argv[5]);
	}
	else {
		printf("Error: Not enough arguments provided\n");
		return 1;
	}

	struct timeval start, end;
	ThreadData *threadData = (ThreadData*)malloc(nThreads * sizeof(ThreadData));
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * nThreads);
	int rc;

	if (allocatorNo == 1) {
		int nBlocks = nThreads * 1 + 3 * nThreads;
		createWaitFreePool(nBlocks, nThreads, 1, iterations, objSize); // nBlocks, nThreads, chunkSize, donationsSteps
		for (int t = 0; t < nThreads; t++) {
			threadData[t].obj = allocate(0,1);
		}
	}
	else {
		for (int t = 0; t < nThreads; t++) {
			threadData[t].obj = malloc(objSize);
		}
	}
	gettimeofday (&start, NULL);
	for (int t = 0; t < nThreads; t++) {
		threadData[t].allocatorNo = allocatorNo;
		threadData[t].nThreads = nThreads;
		threadData[t].objSize = objSize;
		threadData[t].iterations = iterations;
		threadData[t].repetitions = repetitions;
		threadData[t].threadId = t;
		if (allocatorNo == 1) {
			rc = pthread_create((threads + t), NULL, workerWaitFreePool, (threadData + t));
		}
		else{
			rc = pthread_create((threads + t), NULL, worker, (threadData + t));
		}
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d", rc);
			exit(-1);
		}
	}

	void *status;
	for (int t = 0; t < nThreads; t++) {
		rc = pthread_join(threads[t], &status);
	}

	gettimeofday (&end, NULL);
	if (allocatorNo == 1) {
		destroyWaitFreePool();
	}

	long int timeTaken = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec ));
	printf("%ld", timeTaken);


	free(threadData);

	//	LOG_EPILOG();
	//	LOG_INFO("Test Client");
	//LOG_CLOSE();
}
