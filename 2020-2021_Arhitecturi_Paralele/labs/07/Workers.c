#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include "Workers.h"

int P = 8;
pthread_t * tid;
int gotTasks = 0;
int putTasks = 0;

typedef struct Tasks {
	int shuttingDown;
	sem_t sem_full;
	sem_t sem_empty;
	pthread_mutex_t mutex;
	Task queue_tasks[QUEUE_SIZE];
	int getIndex;
	int putIndex;
}Tasks;
Tasks tasks;

void forceShutDownWorkers () {
	//with this method it is possible for tasks generated by other tasks to not be executed.
	pthread_mutex_lock(&(tasks.mutex));
	tasks.shuttingDown=1;
	for(int i=0; i < P; i++) {
		sem_post(&(tasks.sem_full)); //We do this to make sure no thread is stuck waiting for threads.
	}
	pthread_mutex_unlock(&tasks.mutex);
}

Task getTask() {
	Task task;
	sem_wait(&(tasks.sem_full));
	pthread_mutex_lock(&(tasks.mutex));
	task = tasks.queue_tasks[tasks.getIndex];
	tasks.getIndex++;
	tasks.getIndex %= QUEUE_SIZE;
	gotTasks++;
	pthread_mutex_unlock(&(tasks.mutex));
	sem_post(&(tasks.sem_empty));
	return task;
}
void putTask(Task task) {
	sem_wait(&(tasks.sem_empty));
	pthread_mutex_lock(&(tasks.mutex));
	tasks.queue_tasks[tasks.putIndex] = task;
	tasks.putIndex++;
	tasks.putIndex %= QUEUE_SIZE;
	putTasks++;
	pthread_mutex_unlock(&(tasks.mutex));
	sem_post(&(tasks.sem_full));
}

void* workerThread(void *var)
{
	int thread_id = *(int*)var;

	//printf("Hello world from thread %i\n", thread_id);
	while(1) {
		Task task = getTask();
		if(tasks.shuttingDown)
			break;
		task.runTask(task.data, thread_id);
	}
	return NULL;
	//printf("Thread ended\n");
}

void startWorkers() {
	sem_init(&(tasks.sem_full), 0, 0);
	sem_init(&(tasks.sem_empty), 0, QUEUE_SIZE);
	tasks.putIndex=0;
	tasks.getIndex=0;
	tasks.shuttingDown=0;
	pthread_mutex_init(&(tasks.mutex), NULL);
	int i;
	tid=(pthread_t*)malloc(sizeof(pthread_t)*P);
	int * thread_id=(int*)malloc(sizeof(int)*P);
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, workerThread, &(thread_id[i]));
	}
	
}

void joinWorkerThreads () {
	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
}