#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include "Workers.h"

void printSomething(void * data, int thread_id);
int N;
int printLevel;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

Task makeTask(int i) 
{
	Task task;
	int * newData = (int*)malloc(sizeof(int));
	newData[0]=i;
	task.data=newData;
	task.runTask = printSomething;
	return task;
}

void printSomething(void * data, int thread_id) 
{
	int task_id = *(int*)data;
	if(task_id>N) {
		forceShutDownWorkers();
		return;
	}
	//we added thread_if, gotTasks, putTasks here just for debugging purpouses
	if(printLevel)
		printf("Something %i from thread %i we processed %i tasks and submitted %i tasks\n", task_id, thread_id, gotTasks, putTasks);
	putTask(makeTask(task_id+1));
}

int main(int argc, char** argv)
{
	getArgs(argc, argv);
	startWorkers();
	putTask(makeTask(0));
	joinWorkerThreads();

	return 0;
}
