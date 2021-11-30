#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;


void* threadFunction(void *var)
{
	//TODO preserve the correct order by using barriers
	int thread_id = *(int*)var;
	if(thread_id==0)
		printf("I should be displayed last\n");
	else if(thread_id==1)
		printf("I should be displayed in the middle\n");
	else if(thread_id==2)
		printf("I should be displayed first\n");
}

void getArgs(int argc, char **argv)
{

}

void init() 
{
}	

void printAll()
{
}

void printPartial()
{
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

int main(int argc, char *argv[])
{
	getArgs(argc, argv);
	init();

	P = 3; // ATTENTION, WE OVERWRITE THE NUMBER OF THREADS. WE ONLY NEED 3
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;
	//DO NOT EDIT
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	//DO NOT EDIT
	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	//DO NOT EDIT
	print();

	return 0;
}
