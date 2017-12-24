/*
 * ContextSwitchMeasurement.cpp
 *
 *  Created on: Jun 14, 2014
 *      Author: developer
 */

#include "ContextSwitchMeasurement.h"

uint32_t counter;
pthread_mutex_t lock;
pthread_mutex_t start;
pthread_cond_t condition;

void * threads(void * unused) {
	//Wait until the first thread fires to avoid deadlock
	pthread_mutex_lock(&start);
	pthread_mutex_unlock(&start);

	pthread_mutex_lock(&lock);
	if (counter > 0) { //wake up the other thread
		pthread_cond_signal(&condition);
	}

	for(;;) {
		counter++;
		//make current thread wait
		pthread_cond_wait(&condition, &lock);
		//wake up other thread
		pthread_cond_signal(&condition);
	}
	pthread_mutex_unlock(&lock);
}

int64_t timeInMs() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (int64_t)t.tv_sec * 1000 + (int64_t)t.tv_usec / 1000;
}

uint32_t getCtxSwitchMeasurement() {
	pthread_t t1;
	pthread_t t2;
	int64_t startTime;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&start, NULL);
	pthread_cond_init(&condition, NULL);

	pthread_mutex_lock(&start);
	counter = 0;
	pthread_create(&t1, NULL, &threads, NULL);
	pthread_create(&t2, NULL, &threads, NULL);
	pthread_detach(t1);
	pthread_detach(t2);
	//Get start time
	startTime = timeInMs();
	pthread_mutex_unlock(&start);

	//Wait a little
	sleep(1);

	//Stop both threads
	pthread_mutex_lock(&lock);

	// Find out how much time has really passed. sleep won't guarantee me that
	// I sleep exactly one second, I might sleep longer since even after being
	// woken up, it can take some time before I gain back CPU time. Further
	// some more time might have passed before I obtained the lock!
	// Correct the number of thread switches accordingly
	return (uint32_t)(((uint64_t)counter * 1000) / (timeInMs() - startTime));
}

