#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define inf 99

int stack[100];
int indexStack;

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

//ADJACENCY MATRIX
typedef struct graphMatrix {
	int** adjacencyMatrix;
	int numNodes;
} graphMatrix;

//EDGES
typedef struct edge {
	int leftNode;
	int rightNode;
	//	int weigth;
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

graphMatrix* readGraph(const char* filename)
{
	FILE* f = fopen(filename, "r");

	fclose(f);
	return NULL;
}

void printGraphMatrix(graphMatrix* graph)
{
}

graphEdges* convertMatrixToEdgeList(graphMatrix* graph)
{
	graphEdges* newGraph = (graphEdges*)malloc(sizeof(graphEdges));

	return newGraph;
}

void printEdgeList(graphEdges* graph)
{
}

graphMatrix* convertEdgeListToMatrix(graphEdges* graph)
{
	graphMatrix* newGraph = (graphMatrix*)malloc(sizeof(graphMatrix));

	return newGraph;
}

graphVertex* convertEdgeListToVertex(graphEdges* graph)
{
	graphVertex* newGraph = (graphVertex*)malloc(sizeof(graphVertex));

	return newGraph;
}

void printVertex(graphVertex* graph)
{
}

int getDegreeOutMatrix(graphMatrix* graph, int name)
{
	int degree = 0;

	return degree;
}

int getDegreeOutEdgeList(graphEdges* graph, int name)
{
	int degree = 0;

	return degree;
}

int getDegreeOutVertex(graphVertex* graph, int name)
{
	int degree = 0;

	return degree;
}

int main()
{
	graphMatrix* MGraph = readGraph("graphMatrix.txt");

	printf("Graph as matrix:\n");
	printGraphMatrix(MGraph);

	printf("Graph as edges:\n");
	graphEdges* newEGraph = convertMatrixToEdgeList(MGraph);
	printEdgeList(newEGraph);

	printf("Graph as matrix:\n");
	graphEdges* newMGraph = convertEdgeListToMatrix(newEGraph);
	printEdgeList(newMGraph);

	printf("Graph as vertices:\n");
	graphVertex* newVGraph = convertEdgeListToVertex(newEGraph);
	printVertex(newVGraph);

	printf("Degree of node %i is: \n", 2);
	getDegreeOutMatrix(newMGraph, 2);
	getDegreeOutEdgeList(newEGraph, 2);
	getDegreeOutVertex(newVGraph, 2);

	return 0;
}