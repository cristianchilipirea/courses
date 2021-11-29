===== Lab 09 Grafuri =====

  - Implementați citirea dintr-un fișer și construcția unui graf folosind matrice de adiacență.
  - Parcurgere BFS matrice de adiacență cu afișare.
  - Parcurgere DFS matrice de adiacență cu afișare.
  - Implementați citirea dintr-un fișer și construcția unui graf folosind listă de muchii.
  - Parcurgere BFS listă de muchii cu afișare.
  - Parcurgere DFS listă de muchii cu afișare.
**Pentru curajoși**
  - Implementați citirea dintr-un fișer și construcția unui graf folosind structuri de noduri unde pointerii sunt muchii.
  - Parcurgere BFS structuri de noduri unde pointerii sunt muchiicu afișare.
  - Parcurgere DFS matstructuri de noduri unde pointerii sunt muchii cu determinare dacă graful este connex.

**Pentru curajoși**: Implemntați [[https://www.infoarena.ro/problema/bfs|BFS]] și [[https://www.infoarena.ro/problema/dfs|DFS]] pe infoarena.

<code c schelet.c>
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//ADJACENCY MATRIX
typedef struct graphMatrix {
    int** adjacencyMatrix;
    int numNodes;
}graphMatrix;

//EDGES
typedef struct edge {
	int leftNode;
	int rightNode;
}edge;

typedef struct graphEdges {
    edge* edges;
    int numNodes;
    int numEdges;
}graphEdges;

//POINTERS
typedef struct vertex {
	int name;
	struct vertex** neighbors;
	int numNeighbors;
	int* weights;
}vertex;

typedef struct graphPointers {
    int numNodes;
    int numEdges;
    vertex* nodes;
}graphPointers;

// ==== QUEUE IMPLEMENTATION ====
typedef struct node {
    int element;
    struct node* next;
}listNode;

void insertNodeHeadOfList(listNode** listStart, int element) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
    if (node == NULL) {
        printf("ERROR: CAN NOT ALLOCATE RAM\n");
        return;
    }
    node->next = *listStart;
    node->element = element;
    *listStart = node;
}

listNode* getNode(listNode* listNode, int poz) {
    if (listNode == NULL)
        return NULL;
    for (int i = 0; i < poz; i++) {
        if (listNode->next == NULL)
            break;
        listNode = listNode->next;
    }
    return listNode;
}

void insertNodeInList(listNode** listStart, int element, int poz) {
    if (poz == 0) {
        insertNodeHeadOfList(listStart, element);
        return;
    }
    if ((*listStart) == NULL) {
        insertNodeHeadOfList(listStart, element);
        return;
    }
    listNode* node = (listNode*)malloc(sizeof(listNode));
    if (node == NULL) {
        printf("ERROR: CAN NOT ALLOCATE RAM\n");
        return;
    }

    listNode* aux = getNode(*listStart, poz - 1);

    node->next = aux->next;
    node->element = element;
    aux->next = node;
}

void printList(listNode* listStart) {
    printf("[");
    for (; listStart != NULL; listStart = listStart->next) {
        printf("%i", listStart->element);
        if (listStart->next != NULL)
            printf(",");
    }
    printf("]\n");
}

void removeNodeHeadOfList(listNode** listStart) {
    if (*listStart == NULL)
        return;
    listNode* aux = (*listStart);
    *listStart = (*listStart)->next;
    free(aux);
}

void removeNodeFromList(listNode** listStart, int poz) {
    if (poz == 0) {
        removeNodeHeadOfList(listStart);
        return;
    }
    listNode* aux = getNode(*listStart, poz - 1);
    if (aux->next != NULL) {
        listNode* aux1 = aux->next;
        aux->next = aux->next->next;
        free(aux1);
    }
}

void push_queue(listNode** listStart, int value) {
    insertNodeInList(listStart, value, 1000); // we assume the queue will never have more than 1000 elements
}

int pop_queue(listNode** listStart) {
    int aux = (*listStart)->element;
    removeNodeHeadOfList(listStart);
    return aux;
}
// ==== QUEUE IMPLEMENTATION ====


void bfs_matrix(graphMatrix graph, int startNode, int* visited) {
    
}


void dfs_matrix(graphMatrix graph, int currentNode, int* visited) {
	
}

graphMatrix readGraphMatrix(const char* fileName) {
    FILE* f = fopen(fileName, "r");
    graphMatrix graph;
    graph.numNodes = 0;
    if (f == NULL)
	return graph;
	
    //TODO
    fclose(f);
    return graph;
}

void bfs_edges(graphEdges graph, int startNode, int* visited) {

}


void dfs_edges(graphEdges graph, int currentNode, int* visited) {

}

graphEdges readGraphEdgeList(const char* fileName) {
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

void bfs_pointers(graphPointers graph, int startNode, int* visited) {

}


void dfs_pointers(graphPointers graph, int currentNode, int* visited) {

}

graphPointers readGraphPointers(const char* fileName) {
    graphPointers graph;
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
    int visited[100] = { 0 }; //we assume fewer than 100 nodes
    dfs_matrix(graphM, 0, visited);
    printf("\n");
    int visited1[100] = { 0 }; //we assume fewer than 100 nodes
    bfs_matrix(graphM, 0, visited1);
    printf("\n");
    //EDGES
    graphEdges graphE = readGraphEdgeList("graphEdges.txt");
    int visited2[100] = { 0 }; //we assume fewer than 100 nodes
    dfs_edges(graphE, 0, visited2);
    printf("\n");
    int visited3[100] = { 0 }; //we assume fewer than 100 nodes
    bfs_edges(graphE, 0, visited3);
    printf("\n");
    //POINTERS
    graphPointers graphP = readGraphPointers("graphEdges.txt");
    int visited4[100] = { 0 }; //we assume fewer than 100 nodes
    dfs_pointers(graphP, 0, visited4);
    printf("\n");
    int visited5[100] = { 0 }; //we assume fewer than 100 nodes
    bfs_pointers(graphP, 0, visited5);
    printf("\n");
    return 0;
}
</code>

<code c graphMatrix.txt>
10
0 1 0 0 0 0 0 0 0 1
1 0 0 1 1 0 0 0 0 0
0 0 0 1 1 1 0 0 0 0
0 1 1 0 1 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0
0 0 1 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 1 1
0 0 0 0 0 0 0 1 0 1
1 0 0 0 0 0 0 1 1 0
</code>

<code c graphEdges.txt>
10 24
0 1
0 9
1 0
1 3
1 4
2 3
2 4
2 5
3 1
3 2
3 4
4 1
4 2
4 3
5 2
5 7
7 5
7 8
7 9
8 7
8 9
9 0
9 7
9 8
</code>

<code c output>
0 1 3 2 4 5 7 8 9
0 1 9 3 4 7 8 2 5
0 1 3 2 4 5 7 8 9
0 1 9 3 4 7 8 2 5
0 1 3 2 4 5 7 8 9
0 1 9 3 4 7 8 2 5
</code>