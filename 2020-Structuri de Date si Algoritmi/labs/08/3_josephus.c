#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char* element;
	struct node* next;
} listNode;

void insertNodeHeadOfList(listNode** listStart, char* element)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) {
		printf("ERROR: CAN NOT ALLOCATE RAM\n");
		return;
	}
	node->next = *listStart;
	node->element = element;
	*listStart = node;
}

listNode* getNode(listNode* listNode, int poz)
{
	for (int i = 0; i < poz; i++) {
		listNode = listNode->next;
		if (listNode->next == NULL)
			break;
	}
	return listNode;
}

void insertNodeInList(listNode** listStart, char* element, int poz)
{
	if (poz == 0) {
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

void printList(listNode* listStart)
{
	printf("[");
	for (; listStart != NULL; listStart = listStart->next) {
		printf("%i", listStart->element);
		if (listStart->next != NULL)
			printf(",");
	}
	printf("]\n");
}

void removeNodeHeadOfList(listNode** listStart)
{
	if (*listStart == NULL)
		return;
	listNode* aux = (*listStart);
	*listStart = (*listStart)->next;
	free(aux);
}

void removeNodeFromList(listNode** listStart, int poz)
{
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

void playJosephus(listNode** listStart, int k)
{
}

int main(int argc, char* argv[])
{
	listNode* list = NULL;
	insertNodeHeadOfList(&list, (char*)"Gabriela");
	insertNodeHeadOfList(&list, (char*)"Florin");
	insertNodeHeadOfList(&list, (char*)"Elena");
	insertNodeHeadOfList(&list, (char*)"Dan");
	insertNodeHeadOfList(&list, (char*)"Cris");
	insertNodeHeadOfList(&list, (char*)"Bob");
	insertNodeHeadOfList(&list, (char*)"Ana");

	printList(list);

	playJosephus(&list, 2);

	printList(list);

	return 0;
}