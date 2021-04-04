#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ADJACENCY MATRIX
typedef struct graphMatrix {
	int** adjacencyMatrix;
	int numNodes;
} graphMatrix;

//EDGES
typedef struct edge {
	int leftNode;
	int rightNode;
} edge;

typedef struct graphEdges {
	edge* edges;
	int numNodes;
	int numEdges;
} graphEdges;

//POINTERS/VERTEX
typedef struct vertex {
	int name;
	struct vertex** neighbors;
	int numNeighbors;
	//	int* weights;
} vertex;

typedef struct graphVertex {
	int numNodes;
	int numEdges;
	vertex* nodes;
} graphVertex;

int stack[100];
int indexStack = 0;

void push(int value)
{
	if (indexStack < 100)
		stack[indexStack++] = value;
	else
		printf("Dimensiune stiva depasita!\n");
}

int pop()
{
	//verificare daca sunt elemente in stiva
	if (indexStack > 0) {
		int value = stack[--indexStack];
		stack[indexStack] = 0;
		return value;
	}
	printf("Stiva este goala!\n");
	return (int)0;
}

void bfs_matrix(graphMatrix graph, int startNode, int* visited)
{
}

void dfs_matrix(graphMatrix graph, int currentNode, int* visited)
{
}

graphMatrix readGraphMatrix(const char* fileName)
{
	FILE* f = fopen(fileName, "r");
	graphMatrix graph;
	graph.numNodes = 0;
	if (f == NULL)
		return graph;

	//TODO

	fclose(f);
	return graph;
}

void bfs_edges(graphEdges graph, int startNode, int* visited)
{
}

void dfs_edges(graphEdges graph, int currentNode, int* visited)
{
}

graphEdges readGraphEdgeList(const char* fileName)
{
	graphEdges graph;
	graph.numEdges = 0;
	graph.edges = NULL;
	FILE* f = fopen(fileName, "r");
	if (f == NULL)
		return graph;

	//TODO

	fclose(f);
	return graph;
}

void bfs_pointers(graphVertex graph, int startNode, int* visited)
{
}

void dfs_pointers(graphVertex graph, int currentNode, int* visited)
{
}

graphVertex readGraphVertex(const char* fileName)
{
	graphVertex graph;
	graph.numEdges = 0;
	graph.numNodes = 0;
	FILE* f = fopen(fileName, "r");
	if (f == NULL)
		return graph;

	fscanf(f, "%i%i", &(graph.numNodes), &(graph.numEdges));
	graph.nodes = (vertex*)malloc(sizeof(vertex) * graph.numNodes);
	if (graph.nodes == NULL)
		return graph;
	for (int i = 0; i < graph.numNodes; i++) {
		graph.nodes[i].name = i;
		graph.nodes[i].numNeighbors = 0;
		graph.nodes[i].neighbors = NULL;
	}
	for (int i = 0; i < graph.numEdges; i++) {
		//TODO
	}
	fclose(f);
	return graph;
}

int main()
{
	//ADJACENCY MATRIX
	graphMatrix graphM = readGraphMatrix("graphMatrix.txt");
	int visited[100] = {0};  //we assume fewer than 100 nodes
	dfs_matrix(graphM, 0, visited);
	printf("\n");
	int visited1[100] = {0};  //we assume fewer than 100 nodes
	bfs_matrix(graphM, 0, visited1);
	printf("\n");
	//EDGES
	graphEdges graphE = readGraphEdgeList("graphEdges.txt");
	int visited2[100] = {0};  //we assume fewer than 100 nodes
	dfs_edges(graphE, 0, visited2);
	printf("\n");
	int visited3[100] = {0};  //we assume fewer than 100 nodes
	bfs_edges(graphE, 0, visited3);
	printf("\n");
	//POINTERS/VERTEX
	graphVertex graphV = readGraphVertex("graphEdges.txt");
	int visited4[100] = {0};  //we assume fewer than 100 nodes
	dfs_vertex(graphV, 0, visited4);
	printf("\n");
	int visited5[100] = {0};  //we assume fewer than 100 nodes
	bfs_vertex(graphV, 0, visited5);
	printf("\n");
	return 0;
}