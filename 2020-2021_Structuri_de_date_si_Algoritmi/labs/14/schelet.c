#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define inf 999

typedef struct graphMatrix {
	int** costMatrix;
	int numNodes;
} graphMatrix;

// clang-format off
int tempMatrix[][10] = {{0, 1, inf, inf, inf, inf, inf, inf, inf, 20},
                        {1, 0, inf, 1, 2, inf, inf, inf, inf, inf},
                        {inf, inf, 0, 1, 1, 1, inf, inf, inf, inf},
                        {inf, 1, 1, 0, 3, inf, inf, inf, inf, inf},
                        {inf, 2, 1, 3, 0, inf, inf, inf, inf, inf},
                        {inf, inf, 1, inf, inf, 0, inf, 1, inf, inf},
                        {inf, inf, inf, inf, inf, inf, 0, inf, inf, inf},
                        {inf, inf, inf, inf, inf, 1, inf, 0, 1, 1},
                        {inf, inf, inf, inf, inf, inf, inf, 1, 0, 1},
                        {20, inf, inf, inf, inf, inf, inf, 1, 1, 0}};
// clang-format on

graphMatrix initGraphMatrix()
{
	graphMatrix graph;
	graph.numNodes = 10;
	graph.costMatrix = (int**)malloc(sizeof(int*) * graph.numNodes);
	for (int i = 0; i < graph.numNodes; i++) {
		graph.costMatrix[i] = (int*)malloc(sizeof(int) * graph.numNodes);
		for (int j = 0; j < graph.numNodes; j++)
			graph.costMatrix[i][j] = tempMatrix[i][j];
	}
	return graph;
}

void printMaxDegree(graphMatrix graph)
{
	int maxDegree = 0;
	int maxDegreeNode = -1;

	//TODO

	printf("Node %i has maximum degree %i\n", maxDegreeNode, maxDegree);
}

graphMatrix floydWarshall(graphMatrix graph)
{
	graphMatrix pathCosts;
	pathCosts.numNodes = graph.numNodes;
	pathCosts.costMatrix = (int**)malloc(sizeof(int*) * pathCosts.numNodes);
	for (int i = 0; i < pathCosts.numNodes; i++) {
		pathCosts.costMatrix[i] = (int*)malloc(sizeof(int) * pathCosts.numNodes);
		for (int j = 0; j < pathCosts.numNodes; j++)
			pathCosts.costMatrix[i][j] = graph.costMatrix[i][j];
	}

	//TODO

	return pathCosts;
}

int getGraphDiameter(graphMatrix graph)
{
	int max = 0;
	//TODO
	return max;
}

typedef struct nodeDP {
	int node;
	int d;
	int parent;
} nodeDP;

int cmpNDP(const void* a, const void* b)
{
	nodeDP* A = (nodeDP*)a;
	nodeDP* B = (nodeDP*)b;
	return (A->d - B->d);
}

void printNDP(nodeDP* NDP, int n)
{
	printf("  Node: ");
	for (int i = 0; i < n; i++)
		printf("%5i", NDP[i].node);
	printf("\n");
	printf("     D: ");
	for (int i = 0; i < n; i++)
		printf("%5i", NDP[i].d);
	printf("\n");
	printf("Parent: ");
	for (int i = 0; i < n; i++)
		printf("%5i", NDP[i].parent);
	printf("\n");
}
nodeDP* dijsktra(graphMatrix graph, int source)
{
	nodeDP* NDP = (nodeDP*)malloc(sizeof(nodeDP) * graph.numNodes);
	if (NDP == NULL)
		return NULL;
	for (int i = 0; i < graph.numNodes; i++) {
		NDP[i].node = i;
		NDP[i].d = inf;
		NDP[i].parent = -1;
	}
	NDP[source].d = 0;
	int position = 0;
	//TODO
	//Helper for sort: qsort(NDP, graph.numNodes, sizeof(nodeDP), cmpNDP);
	return NDP;
}

typedef struct edge {
	int leftNode;
	int rightNode;
	int w;
	int selected;
} edge;

void printEdges(edge* edges, int n)
{
	for (int i = 0; i < n; i++) {
		if (edges[i].selected)
			printf("%i -%i-> %i\n", edges[i].leftNode, edges[i].w, edges[i].rightNode);
	}
}

int countEdges(graphMatrix graph)
{
	int numEdges = 0;
	for (int i = 0; i < graph.numNodes; i++)
		for (int j = 0; j < graph.numNodes; j++)
			if (i < j && graph.costMatrix[i][j] < inf)
				numEdges++;
	return numEdges;
}

int cmpEdge(const void* a, const void* b)
{
	//TODO
}

edge* kruskal(graphMatrix graph)
{
	int numEdges = countEdges(graph);
	edge* edges = (edge*)malloc(sizeof(edge) * numEdges);
	numEdges = 0;
	for (int i = 0; i < graph.numNodes; i++)
		for (int j = 0; j < graph.numNodes; j++)
			if (i < j && graph.costMatrix[i][j] < inf) {
				edges[numEdges].leftNode = i;
				edges[numEdges].rightNode = j;
				edges[numEdges].w = graph.costMatrix[i][j];
				edges[numEdges].selected = 0;
				numEdges++;
			}
	qsort(edges, numEdges, sizeof(edge), cmpEdge);
	int* treeTag = (int*)malloc(sizeof(int) * graph.numNodes);
	for (int i = 0; i < graph.numNodes; i++)
		treeTag[i] = i;

	//TODO

	return edges;
}

int main()
{
	graphMatrix graphM = initGraphMatrix();
	printMaxDegree(graphM);
	printf("\n");
	graphMatrix pathCosts = floydWarshall(graphM);
	for (int i = 0; i < pathCosts.numNodes; i++) {
		for (int j = 0; j < pathCosts.numNodes; j++)
			printf("%4i ", pathCosts.costMatrix[i][j]);
		printf("\n");
	}
	printf("\n");
	printf("Diameter of the graph is %i\n", getGraphDiameter(pathCosts));

	nodeDP* NDP = dijsktra(graphM, 0);
	printf("\nDijsktra rezult:\n");
	printNDP(NDP, graphM.numNodes);
	edge* treeEdges = kruskal(graphM);
	printf("\nKruskal rezult:\n");
	printEdges(treeEdges, countEdges(graphM));
	printf("\n");
	return 0;
}