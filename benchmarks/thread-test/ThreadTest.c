/*
 * ThreadTest.c
 *
 *  Created on: 14-Jul-2015
 *      Author: architaagarwal
 */

// Command line arguments:
// <allocator flag> <nThreads> <objSize> <nIterations>

#include <pthread.h>
#include <stdio.h>
#include "../../allocators/WaitFreeMemAlloc/src/WaitFreePool.h"
#include "../../utils/mini-logger/logger.h"
#include <stdlib.h>
#include <time.h>
//#include "../../allocators/michael/michael.h"

typedef struct _ThreadData {
	int allocatorNo;
	int nThreads;
	int objSize;
	int iterations;
	int repetitions;
	int threadId;
} ThreadData;

extern void* xxmalloc(int);
extern void xxfree(void*);
//extern void* m_malloc(size_t sz);
//extern void m_free(void* ptr);

void workerNormal(void *data) {
	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	char **ptr = (char**) malloc(sizeof(char*) * threadData->iterations);
	for (int i = 0; i < threadData->repetitions; i++) {
		for (int j = 0; j < threadData->iterations; j++) {
			ptr[j] = malloc(threadData->objSize);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
		for (int j = 0; j < threadData->iterations; j++) {
			free(ptr[j]);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
	}
	free(ptr);
	LOG_EPILOG();
}

void workerWaitFreePool(void *data) {
	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	char **ptr = (char**) malloc(sizeof(char*) * threadData->iterations);
	for (int i = 0; i < threadData->repetitions; i++) {
		for (int j = 0; j < threadData->iterations; j++) {
			ptr[j] = allocate(threadData->threadId, 0);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
		for (int j = 0; j < threadData->iterations; j++) {
			freeMem(threadData->threadId, ptr[j]);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
	}
	free(ptr);
	LOG_EPILOG();
}

void workerHoard(void *data) {
	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	char **ptr = (char**) malloc(sizeof(char*) * threadData->iterations);
	for (int i = 0; i < threadData->repetitions; i++) {
		for (int j = 0; j < threadData->iterations; j++) {
			ptr[j] = xxmalloc(threadData->objSize);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
		for (int j = 0; j < threadData->iterations; j++) {
			xxfree(ptr[j]);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
	}
	free(ptr);
	LOG_EPILOG();
}
/*
void workerMichael(void *data) {
	LOG_PROLOG();
	ThreadData* threadData = (ThreadData*) data;
	char **ptr = (char**) malloc(sizeof(char*) * threadData->iterations);
	for (int i = 0; i < threadData->repetitions; i++) {
		for (int j = 0; j < threadData->iterations; j++) {
			ptr[j] = m_malloc(threadData->objSize);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
		for (int j = 0; j < threadData->iterations; j++) {
			m_free(ptr[j]);
			LOG_INFO("thread %d ptr got is %u\n", threadData->threadId, ptr);
		}
	}
	free(ptr);
	LOG_EPILOG();
}
*/
int main(int argc, char* argv[]) {
	//	LOG_INIT_CONSOLE();
	//	LOG_INIT_FILE();
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

	if (allocatorNo == 1) {
		int nBlocks = nThreads * iterations;
		createWaitFreePool(nBlocks, nThreads, iterations, iterations*repetitions, objSize); // nBlocks, nThreads, chunkSize, donationsSteps
		//hashTableCreate(nBlocks);
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
		}/*
		else if (allocatorNo == 3) {
			rc = pthread_create((threads + t), NULL, workerMichael, (threadData + t));
		}*/
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
	//	LOG_CLOSE();
}
