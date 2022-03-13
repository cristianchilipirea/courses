#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char *element;
	struct node *next;
} listNode;

listNode *getNode(listNode *listNode, int poz)
{
	for (int i = 0; i < poz && listNode != NULL; i++) {
		listNode = listNode->next;
	}
	return listNode;
}

void insertNodeInList(listNode **headNode, char *element, int poz)
{
	listNode *newNode = (listNode *)malloc(sizeof(listNode));
	newNode->element = element;
	newNode->next = *headNode;
	*headNode = newNode;
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
	listNode *aux = *listStart;
	*listStart = (*listStart)->next;
	free(aux);
}

int main()
{
	listNode *list = NULL;
	printList(list);  // afiseaza []
	insertNodeInList(&list, "Ana", 0);
	printList(list);  // afiseaza [Ana]
	insertNodeInList(&list, "Vacanta", 0);
	printList(list);  // afiseaza [Vacanta,Ana]
	removeNodeFromList(&list, 0);
	printList(list);  // afiseaza [Ana]
	insertNodeInList(&list, "Bob", 0);
	insertNodeInList(&list, "CCC", 0);
	insertNodeInList(&list, "EEEE", 2);
	printList(list);  // afiseaza [CCC,Bob,EEEE,Ana]
	listNode *l = getNode(list, 2);
	printList(l); // afiseaza [Bob,Ana]
}
