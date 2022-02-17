#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char *element;
	struct node *next;
} listNode;

void printList(listNode *listStart)
{
	printf("[");
	while (listStart != NULL) {
		printf("%s, ", listStart->element);
		listStart = listStart->next;
	}
	printf("]\n");
}

listNode *getNode(listNode *listNode, int poz)
{
	if (listNode == NULL)
		return NULL;
	for (int i = 0; i < poz; i++) {
		if (listNode->next == NULL)
			break;
		listNode = listNode->next;
	}
	return listNode;
}

void insertNodeHeadOfList(listNode **listStart, char *element)
{
	listNode *aux = (listNode *)malloc(sizeof(listNode));
	if (aux == NULL)
		return;
	aux->element = element;
	aux->next = *listStart;
	*listStart = aux;
}

void insertNodeInList(listNode **listStart, char *element, int poz)
{
	if (poz < 0) {
		printf("Te rugam sa inserezi doar pozitii numere naturale pozitive");
		return;
	}
	if (poz == 0) {
		insertNodeHeadOfList(listStart, element);
		return;
	}
	listNode *prevNode = getNode(*listStart, poz - 1);
	if (prevNode->next == NULL)
		return;
	listNode *aux = (listNode *)malloc(sizeof(listNode));
	if (aux == NULL)
		return;
	aux->element = element;
	aux->next = prevNode->next;
	prevNode->next = aux;
}

void removeNodeHeadOfList(listNode **listStart)
{
	listNode *aux = *listStart;
	*listStart = (*listStart)->next;
	free(aux);
}

void removeNodeFromList(listNode **listStart, int poz)
{
	if (poz == 0) {
		removeNodeHeadOfList(listStart);
		return;
	}
	listNode *prevNode = getNode(*listStart, poz - 1);
	if (prevNode == NULL)
		return;
	listNode *aux = prevNode->next;
	prevNode->next = prevNode->next->next;
	free(aux);
}

int main()
{
	listNode *list = NULL;
	insertNodeHeadOfList(&list, (char *)"Ana");
	printList(list);
	printList(list);
	insertNodeHeadOfList(&list, (char *)"Bob");
	printList(list);
	insertNodeHeadOfList(&list, (char *)"Cris");
	printList(list);
	insertNodeInList(&list, (char *)"Start", 0);
	printList(list);
	insertNodeInList(&list, (char *)"mid", 15);
	printList(list);
	printList(getNode(list, 3));
	printList(list);
	removeNodeHeadOfList(&list);
	printList(list);
	removeNodeFromList(&list, 2);
	printList(list);
	removeNodeFromList(&list, 10);
	printList(list);
	removeNodeFromList(&list, 2);
	printList(list);
}