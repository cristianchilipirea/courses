#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char *element;
	struct node *next;
} listNode;

void printList(listNode *listStart)
{
	printf("[");
	for (; listStart != NULL; listStart = listStart->next) {
		printf("%s", listStart->element);
		if (listStart->next != NULL)
			printf(",");
	}
	printf("]\n");
}

listNode *getNode(listNode *listNode, int poz)
{
	for (int i = 0; i < poz; i++) {
		listNode = listNode->next;
		if (listNode->next == NULL)
			break;
	}
	return listNode;
}

void insertNodeHeadOfList(listNode **listStart, char *element)
{
	listNode *node = (listNode *)malloc(sizeof(listNode));
	if (node == NULL) {
		printf("ERROR: CAN NOT ALLOCATE RAM\n");
		return;
	}
	node->next = *listStart;
	node->element = element;
	*listStart = node;
}

void insertNodeInList(listNode **listStart, char *element, int poz)
{
	if (poz == 0) {
		insertNodeHeadOfList(listStart, element);
		return;
	}
	listNode *node = (listNode *)malloc(sizeof(listNode));
	if (node == NULL) {
		printf("ERROR: CAN NOT ALLOCATE RAM\n");
		return;
	}

	listNode *aux = getNode(*listStart, poz - 1);

	node->next = aux->next;
	node->element = element;
	aux->next = node;
}

void removeNodeHeadOfList(listNode **listStart)
{
	// free((*listStart)->element);
	if (*listStart == NULL)
		return;
	listNode *aux = (*listStart);
	*listStart = (*listStart)->next;
	free(aux);
}

void removeNodeFromList(listNode **listStart, int poz)
{
	if (poz == 0) {
		removeNodeHeadOfList(listStart);
		return;
	}
	listNode *aux = getNode(*listStart, poz - 1);
	if (aux->next != NULL) {
		listNode *aux1 = aux->next;
		aux->next = aux->next->next;
		// free(aux1->element);
		free(aux1);
	}
}

int main()
{
	listNode *list = NULL;
	insertNodeHeadOfList(&list, (char *)"Ana");
	printList(list);
	insertNodeHeadOfList(&list, (char *)"Bob");
	printList(list);
	insertNodeHeadOfList(&list, (char *)"Cris");
	printList(list);
	insertNodeInList(&list, (char *)"Start", 0);
	printList(list);
	insertNodeInList(&list, (char *)"mid", 3);
	printList(list);
	printList(getNode(list, 3));
	removeNodeHeadOfList(&list);
	printList(list);
	removeNodeFromList(&list, 2);
	printList(list);
	removeNodeFromList(&list, 10);
	printList(list);
	removeNodeFromList(&list, 2);
	printList(list);
}
