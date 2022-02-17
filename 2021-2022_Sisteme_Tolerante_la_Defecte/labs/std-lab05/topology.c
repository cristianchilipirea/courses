#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// clang-format off
/*
//Run: mpirun -np 5 ./a.out
// DO NOT USE DIRECTLY. USE getNeighbors() INSTEAD
int graph[][2] = { { 0, 1 }, { 1, 0 }, 
                   { 2, 1 }, { 1, 2 },
                   { 3, 1 }, { 1, 3 },
                   { 3, 4 }, { 4, 3 } };
*/

//Run: mpirun -np 12 ./a.out
// DO NOT USE DIRECTLY. USE getNeighbors() INSTEAD
int graph[][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, 
                   { 3, 4 }, { 4,11 }, {11, 5 }, 
                   { 5, 6 }, { 6, 7 }, { 7, 8 },
                   { 8, 9 }, { 9,10 }, {10, 9 },
                   { 9, 8 }, { 8, 7 }, { 7, 6 },
                   { 6, 5 }, { 5,11 }, {11, 4 },
                   { 4, 3 }, { 3, 2 }, { 2, 1 },
                   { 1, 0 }, { 9, 5 }, { 5, 9 },
                   { 5, 3 }, { 3, 5 }, { 0, 2 },
                   { 2, 0 }, { 9, 7 }, { 7, 9 } };

// clang-format on

// getNeighbors returns a 100 int vector.
// position 0 represents the number of neighbors
// positions 1+ represent the ranks of the neighbors
// your program should only send messages to processes on this list
int *getNeighbors(int myRank)
{
	int *neigh = malloc(sizeof(int) * 100);
	int i;
	int j = 1;
	int sizeOfGraph = sizeof(graph) / sizeof(int) / 2;
	for (i = 0; i < sizeOfGraph; i++) {
		if (graph[i][0] == myRank) {
			neigh[j] = graph[i][1];
			j++;
		}
	}
	neigh[0] = j;
	return neigh;
}

// getLocalTopology returns a 100 int vector.
// position 0 represents the number of pairs + 1
// positions 2+ represent pairs of nodes (as ranks) that have a connection
// the node with the smaller rank is always on the left
// example: 3|EMPTY|0|1|1|2|1|3|
//          this means Node 1 has edges with nodes 0, 2 and 3
// your processes should exchange the local topologies to build a global one
// left node is always smaller than the right node
int *getLocalTopology(int myRank, int *neigh)
{
	int *topology = malloc(sizeof(int) * 100);
	int i;
	int j = 1;
	for (i = 1; i < neigh[0]; i++) {
		int nodeA = myRank;
		int nodeB = neigh[i];
		topology[2 * j] = fmin(nodeA, nodeB);
		topology[2 * j + 1] = fmax(nodeA, nodeB);
		j++;
	}
	topology[0] = j;
	return topology;
}

void printNeighbors(int *neigh, int rank)
{
	char aux[1000];
	aux[0] = 0;
	sprintf(aux + strlen(aux), "Rank %2i neighbors: ", rank);
	for (int i = 1; i < neigh[0]; i++) {
		sprintf(aux + strlen(aux), " %2i,", neigh[i]);
	}
	sprintf(aux + strlen(aux) - 1, "\n");  // also deletes the last comma
	printf("%s", aux);
}

void printTopology(int *topology, int rank)
{
	char aux[1000];
	aux[0] = 0;
	sprintf(aux + strlen(aux), "Rank %2i topology : ", rank);
	for (int i = 1; i < topology[0]; i++) {
		sprintf(aux + strlen(aux), " [%2i,%2i],", topology[2 * i], topology[2 * i + 1]);
	}
	sprintf(aux + strlen(aux) - 1, "\n");  // also deletes the last comma
	printf("%s", aux);
}

int isInTopology(int *topology, int nodeA, int nodeB)
{
	for (int i = 1; i < topology[0]; i++)
		if (nodeA == topology[i * 2] && nodeB == topology[i * 2 + 1])
			return 1;
	return 0;
}

int mergeTopologies(int *topologyA, int *topologyB)
{
	int changed = 0;
	// TODO topology A will be the result of merging topologyA and topologyB

	return changed;
}

int getMaxNode(int *topology)
{
	int max = -1;
	for (int i = 1; i < topology[0]; i++) {
		max = fmax(max, topology[2 * i]);
		max = fmax(max, topology[2 * i + 1]);
	}
	return max;
}

void printNextHops(int *v, int rank, int N)
{
	char aux[1000];
	aux[0] = 0;
	sprintf(aux + strlen(aux), "Rank %2i next Hops : ", rank);
	for (int i = 0; i < N; i++) {
		sprintf(aux + strlen(aux), " [%2i,%2i],", i, v[i]);
	}
	sprintf(aux + strlen(aux) - 1, "\n");  // also deletes the last comma
	printf("%s", aux);
}

int *calculateNextHops(int *topology, int startNode, int numNodes)
{
	int *nextHops = malloc(sizeof(int) * numNodes);
	int *parents = malloc(sizeof(int) * numNodes);
	int *queue = malloc(sizeof(int) * numNodes);
	for (int i = 0; i < numNodes; i++) {
		queue[i] = -1;
		nextHops[i] = -1;
		parents[i] = -1;
	}
	int queueLeft = 0;
	int queueRight = 1;
	queue[0] = startNode;
	parents[startNode] = startNode;

	// TODO implement BFS/Dijsktra. You will have to use a queue.
	// (queueLeft, queueRight should be used to manipulate the queue)
	// at the end the vector parents should be filled




	// TODO for each node, go up the parent tree (vector in our case)
	// the last node before startNode is the nextHop node (write this value in nextHops)

	return nextHops;
}

int main(int argc, char *argv[])
{
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	int *neigh = getNeighbors(rank);
	printNeighbors(neigh, rank);
	int *localTopology = getLocalTopology(rank, neigh);
	printTopology(localTopology, rank);
	int *neighborTopology = malloc(sizeof(int) * 100);

	// YOU ARE ONLY ALLOWED TO COMMUNICATE WITH NEIGHBOR PROCESSES
	// The goal of the first exercise is to pretend you don't have the graph matrix and rebuild it in a distributed manner
	// The goal of the second exercise is to build routing tables. Routing tables are a list of destination + next hop.
	// Routing table for 5 is:
	// 0 -> 3 ; 1 -> 3 ; 2 -> 3 ; 3 -> 3 ; 4 -> 3 ; 5 -> 5 ; 6 -> 6 ; 7 -> 6 ; 8 -> 9 ; 9 -> 9 ; 10 -> 9 ; 11 -> 11

	// TODO send my local topology to all neighbors.
	// repeat
	//     receive topologies from ANY neighbor
	//     merge topology with local topology (mergeTopologies())
	//     if topology changed send to all neighbors (except the one
	//     if more than 5 seconds passed without any receive, break;

	printTopology(localTopology, rank);

	MPI_Barrier(MPI_COMM_WORLD);  // this is just for pretty print

	// TODO implement the calculateNextHops() function
	int *nextHops = calculateNextHops(localTopology, rank);
	printNextHops(nextHops, rank, nProcesses);

	MPI_Barrier(MPI_COMM_WORLD);  // this is just for pretty print

	// TODO send message through network
	// initiatiors send the message
	// all nodes received message with timer (5 seconds)
	// if message received, look at first element, if destiantion, print else send to nextHop

	MPI_Finalize();
	return 0;
}