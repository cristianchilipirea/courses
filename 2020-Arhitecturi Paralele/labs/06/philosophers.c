#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
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

pthread_mutex_t* forkmutex;

//HERE IS WHERE YOU NEED TO IMPLEMENT YOUR SOLUTION
void* phylosopherThread(void *var)
{
	int thread_id = *(int*)var;
	int i;

	for (i = 0; i < N; i++) {
			pthread_mutex_lock(&forkmutex[(thread_id + 1) % P]);
            sleep(1); // THIS IS HERE TO MAKE SURE WE SEE THE DEAD-LOCK DO NOT REMOVE
			pthread_mutex_lock(&forkmutex[thread_id]);
			// Here we are eating. 
			//LEAVE PRINT COMMENTED WHEN TESTING WE CAN NOT GUARANTEE ORDER AND TEST WILL FAIL
			//printf("eating %i\n", thread_id);
			pthread_mutex_unlock(&forkmutex[(thread_id + 1) % P]);
			pthread_mutex_unlock(&forkmutex[thread_id]);
	}

	return NULL;
}
//END HERE IS WHERE YOU NEED TO IMPLEMENT YOUR SOLUTION

int main(int argc, char **argv)
{
	getArgs(argc, argv);

	int i;
	pthread_t tid[P];
	int thread_id[P];
	for(i = 0; i < P; i++)
		thread_id[i] = i;

	forkmutex = malloc(sizeof(pthread_mutex_t) * P);
	for(i = 0; i < P; i++)
		pthread_mutex_init(&forkmutex[i], NULL);

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, phylosopherThread, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	for(i = 0; i < P; i++)
		pthread_mutex_destroy(&forkmutex[i]);

	printf("All phylosophers have eaten\n");

	return 0;
}
