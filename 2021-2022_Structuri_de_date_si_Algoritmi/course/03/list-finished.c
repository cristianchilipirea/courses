#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char *element;
	struct node *next;
} listNode;

listNode *getNode(listNode *listNode, int poz)
{
	if (poz < 0) return NULL;
	if (listNode == NULL) return NULL;

	for (int i = 0; i < poz; i++) {
		if (listNode->next == NULL)
			break;
		listNode = listNode->next;
	}
	return listNode;
}

void insertNodeInList(listNode **headNode, char *element, int poz)
{
	if (headNode == NULL) return;
	if (poz < 0) return;

	listNode *newNode = (listNode *)malloc(sizeof(listNode));
	if (newNode == NULL) return;

	newNode->element = element;

	listNode *prevNode = getNode(*headNode, poz - 1);
	if (prevNode == NULL) {
		newNode->next = *headNode;  //headNode may be NULL
		*headNode = newNode;
	} else {
		newNode->next = prevNode->next;
		prevNode->next = newNode;
	}
}

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

void removeNodeFromList(listNode **listStart, int poz)
{
	if (listStart == NULL) return;
	if (*listStart == NULL) return;
	if (poz < 0) return;

	listNode *prevNode = getNode(*listStart, poz - 1);
	if (prevNode == NULL) {
		listNode *aux = (*listStart);
		*listStart = (*listStart)->next;
		free(aux);
		return;
	} else if (prevNode->next == NULL) {  // poz is beyond end of list
		return;
	} else {
		listNode *aux = prevNode->next;
		prevNode->next = prevNode->next->next;
		// free(aux->element);
		free(aux);
	}
}

int main()
{
	listNode *list = NULL;
	insertNodeInList(&list, (char *)"Ana", 0);
	printList(list);
	insertNodeInList(&list, (char *)"Bob", 0);
	printList(list);
	insertNodeInList(&list, (char *)"Cris", 0);
	printList(list);
	insertNodeInList(&list, (char *)"Start", 0);
	printList(list);
	insertNodeInList(&list, (char *)"mid", 3);
	printList(list);
	printList(getNode(list, 3));
	removeNodeFromList(&list, 0);
	printList(list);
	removeNodeFromList(&list, 2);
	printList(list);
	removeNodeFromList(&list, 10);
	printList(list);
	removeNodeFromList(&list, 2);
	printList(list);
	int a, v[100];
	v[7];
}
