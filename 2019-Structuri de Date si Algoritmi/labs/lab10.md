===== Lab 10 Grafuri =====

  - Pentru un graf memorat ca o matrice de costuri determinați nodul cu grad maxim și afișați gradul acestuia.
  - Având un graf memorat ca o matrice de costuri implementați algoritul Floyd-Warshal pentru determinarea drumului minim între oricare două noduri.
  - Având matricea de costuri generată mai devreme afișați [[https://en.wikipedia.org/wiki/Distance_(graph_theory)|diametrul grafului]]. (diameter d, mai jos in pagină)
  - Pentru același graf implementați algoritmul lui Dijsktra. 
**Pentru curajoși** 
  - Rezolvați Dijsktra pe [[https://www.infoarena.ro/problema/dijkstra|infoarena]].
  - Pentru același graf implementați algoritmul Kruskal.

<code c schelet.c>
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define inf 1000

typedef struct graphMatrix {
    int** costMatrix;
    int numNodes;
}graphMatrix;

int tempMatrix[][10]= {{  0,   1, inf, inf, inf, inf, inf, inf, inf,  20},
                       {  1,   0, inf,   1,   2, inf, inf, inf, inf, inf},
                       {inf, inf,   0,   1,   1,   1, inf, inf, inf, inf},
                       {inf,   1,   1,   0,   3, inf, inf, inf, inf, inf},
                       {inf,   2,   1,   3,   0, inf, inf, inf, inf, inf},
                       {inf, inf,   1, inf, inf,   0, inf,   1, inf, inf},
                       {inf, inf, inf, inf, inf, inf,   0, inf, inf, inf},
                       {inf, inf, inf, inf, inf,   1, inf,   0,   1,   1},
                       {inf, inf, inf, inf, inf, inf, inf,   1,   0,   1},
                       { 20, inf, inf, inf, inf, inf, inf,   1,   1,   0}};

graphMatrix initGraphMatrix() {
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

void printMaxDegree(graphMatrix graph) {
    int maxDegree=0;
    int maxDegreeNode=-1;
    
    //TODO
    
    printf("Node %i has maximum degree %i\n", maxDegreeNode, maxDegree);
}

graphMatrix floydWarshall(graphMatrix graph) {
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

int getGraphDiameter(graphMatrix graph) {
    int max = 0;
    //TODO
    return max;
}

typedef struct nodeDP {
    int node;
    int d;
    int parent;
}nodeDP;

int cmpNDP(const void* a, const void* b) {
    nodeDP* A = (nodeDP*)a;
    nodeDP* B = (nodeDP*)b;
    return (A->d - B->d);
}

void printNDP(nodeDP* NDP, int n) {
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
nodeDP* dijsktra(graphMatrix graph, int source) {
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
}edge;

void printEdges(edge* edges, int n) {
    for (int i = 0; i < n; i++) {
        if(edges[i].selected)
            printf("%i -%i-> %i\n", edges[i].leftNode, edges[i].w, edges[i].rightNode);
    }
}

int countEdges(graphMatrix graph) {
    int numEdges = 0;
    for (int i = 0; i < graph.numNodes; i++)
        for (int j = 0; j < graph.numNodes; j++)
            if (i < j && graph.costMatrix[i][j] < inf)
                numEdges++;
    return numEdges;
}

int cmpEdge(const void* a, const void* b) {
    //TODO
}

edge* kruskal(graphMatrix graph) {
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
    
    nodeDP * NDP = dijsktra(graphM, 0);
    printf("\nDijsktra rezult:\n");
    printNDP(NDP, graphM.numNodes);
    edge * treeEdges = kruskal(graphM);
    printf("\nKruskal rezult:\n");
    printEdges(treeEdges, countEdges(graphM));
    printf("\n");
    return 0;
}
</code>

<code c output>

Node 1 has maximum degree 3

   0    1    3    2    3    4 1000    5    6    6
   1    0    2    1    2    3 1000    4    5    5
   3    2    0    1    1    1 1000    2    3    3
   2    1    1    0    2    2 1000    3    4    4
   3    2    1    2    0    2 1000    3    4    4
   4    3    1    2    2    0 1000    1    2    2
1000 1000 1000 1000 1000 1000    0 1000 1000 1000
   5    4    2    3    3    1 1000    0    1    1
   6    5    3    4    4    2 1000    1    0    1
   6    5    3    4    4    2 1000    1    1    0

Diameter of the graph is 6

Dijsktra rezult:
  Node:     0    1    3    2    4    5    7    8    9    6
     D:     0    1    2    3    3    4    5    6    6 1000
Parent:    -1    0    1    3    1    2    5    7    7   -1

Kruskal rezult:
0 -1-> 1
7 -1-> 9
1 -1-> 3
7 -1-> 8
2 -1-> 3
2 -1-> 4
2 -1-> 5
5 -1-> 7
</code>