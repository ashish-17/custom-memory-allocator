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
#include "../../utils/mini-logger/logger.h"
#include <stdlib.h>
#include <time.h>

typedef struct _ThreadData {
	int allocatorNo;
	int nThreads;
	int objSize;
	int iterations;
	int repetitions;
	int threadId;
	void *obj;
} ThreadData;

extern void* xxmalloc(int);

extern void xxfree(void*);

void* workerNormal(void *data) {
	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	free(threadData->obj);
	for (int i = 0; i < threadData->iterations; i++) {
		char* ptr = malloc(threadData->objSize);
		//LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
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
	LOG_EPILOG();
	return NULL;
}

void workerWaitFreePool(void *data) {
	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	freeMem(threadData->threadId, threadData->obj);
	for (int i = 0; i < threadData->iterations; i++) {
		char* ptr = allocate(threadData->threadId, 0);
		LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
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
	LOG_EPILOG();
}


void* workerHoard(void *data) {
	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	xxfree(threadData->obj);
	for (int i = 0; i < threadData->iterations; i++) {
		char* ptr = xxmalloc(threadData->objSize);
		//LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		// Write into ptr a bunch of times
		for (int j = 0; j < threadData->repetitions; j++) {
			for  (int k = 0; k < threadData->objSize; k++) {
				*(ptr + k) = (char)k;
				char temp = *(ptr + k);
				temp++;
			}
		}
		xxfree(ptr);
	}
	LOG_EPILOG();
	return NULL;
}

/*
void workerMichael(void *data) {
	ThreadData* threadData = (ThreadData*) threadData;
	for (int i = 0; i < threadData->iterations; i++) {
		malloc(threadData->threadId);
	}
}
 */

int main(int argc, char* argv[]) {
	//LOG_INIT_CONSOLE();
	//LOG_INIT_FILE();
	LOG_PROLOG();

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

	clock_t start, diff;
	ThreadData *threadData = (ThreadData*)malloc(nThreads * sizeof(ThreadData));
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * nThreads);
	int rc;

	if (allocatorNo == 0) {
		for (int t = 0; t < nThreads; t++) {
			threadData[t].obj = malloc(objSize);
		}
	}
	else if (allocatorNo == 1) {
		int nBlocks = nThreads * 1 + 3 * nThreads;
		createWaitFreePool(nBlocks, nThreads, 1, iterations, objSize); // nBlocks, nThreads, chunkSize, donationsSteps
		//hashTableCreate(nBlocks);
		for (int t = 0; t < nThreads; t++) {
			threadData[t].obj = allocate(0,1);
		}
	}
	else if (allocatorNo == 2) {
		for (int t = 0; t < nThreads; t++) {
			threadData[t].obj = xxmalloc(objSize);
		}
	}

	start = clock();
	for (int t = 0; t < nThreads; t++) {
		threadData[t].allocatorNo = allocatorNo;
		threadData[t].nThreads = nThreads;
		threadData[t].objSize = objSize;
		threadData[t].iterations = iterations;
		threadData[t].repetitions = repetitions;
		threadData[t].threadId = t;
		if (allocatorNo == 0) {
			rc = pthread_create((threads + t), NULL, workerNormal, (threadData + t));
		}
		else if (allocatorNo == 1) {
			rc = pthread_create((threads + t), NULL, workerWaitFreePool, (threadData + t));
		}
		else if (allocatorNo == 2) {
			rc = pthread_create((threads + t), NULL, workerHoard, (threadData + t));
		}
		else if (allocatorNo == 3) {
			rc = pthread_create((threads + t), NULL, workerWaitFreePool, (threadData + t));
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

	diff = clock() - start;
	if (allocatorNo == 1) {
		destroyWaitFreePool();
	}

	int msec = diff * 1000 / CLOCKS_PER_SEC;

	printf("%d", msec);

	free(threadData);

	LOG_EPILOG();
	LOG_INFO("Test Client");
	//LOG_CLOSE();
}
