#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/**
 * @author cristian.chilipirea
 * Run: mpirun -np 12 ./a.out
 */

int graph[][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, 
                  { 3, 4 }, { 4, 11 }, { 11, 5 }, 
                  { 5, 6 }, { 6, 7 }, { 7, 8 },
                  { 8, 9 }, { 9, 10 }, { 10, 9 },
                  { 9, 8 }, { 8, 7 }, { 7, 6 },
                  { 6, 5 }, { 5, 11 }, { 11, 4 },
                  { 4, 3 }, { 3, 2 }, { 2, 1 },
                  { 1, 0 }, { 9, 5 }, { 5, 9 },
                  { 5, 3 }, { 3, 5 }, { 0, 2 },
                  { 2, 0 }, { 9, 7 }, { 7, 9 } };

int * getNeighbors(int myRank) {
	int * neigh = malloc(sizeof(int) * 100);
	int i;
	int j = 1;
	for(i=0;i<30;i++) {
		if(graph[i][0] == myRank) {
			neigh[j] = graph[i][1];
			j++;
		}
	}
	neigh[0] = j;
	return neigh;
}

int * getLocalTopology(int myRank ,int * neigh) {
	int * topology = malloc(sizeof(int) * 100);
	int i;
	int j = 1;
	for(i=1; i<neigh[0]; i++) {
		topology[2 * j] = myRank;
		topology[2 * j + 1] = neigh[i];
		j++;
	}
	topology[0] = j;
	return topology;
}


int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;


	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	int * neigh = getNeighbors(rank);
	int i;
	char aux[1000];
	aux[0]=0;
	sprintf(aux + strlen(aux), "Rank %i neighbors: ", rank);
	for(i=1; i<neigh[0]; i++) {
		sprintf(aux + strlen(aux), " %i,", neigh[i]);
	}
	sprintf(aux + strlen(aux)-1, "\n");
	printf("%s", aux);


	// YOU ARE ONLY ALLOWED TO COMMUNICATE WITH NEIGHBOR PROCESSES


	printf("Bye from %i/%i\n", rank, nProcesses);
	MPI_Finalize();
	return 0;
}