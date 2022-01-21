#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char* element;
	struct node* next;
	struct node* prev;
} listNode;

void insertNodeHeadOfList(listNode** listStart, char* element)
{
}

listNode* getNode(listNode* listNode, int poz)
{
	return NULL;
}

void insertNodeInList(listNode** listStart, char* element, int poz)
{
}

void printList(listNode* listStart)
{
	printf(">");
}

void printListRev(listNode* listStart)
{
	printf("<<");
}

void removeNodeHeadOfList(listNode** listStart)
{
}

void removeNodeFromList(listNode** listStart, int poz)
{
}

int main()
{
	listNode* list = NULL;
	insertNodeHeadOfList(&list, (char*)"Ana");
	printList(list);
	printListRev(list);
	insertNodeHeadOfList(&list, (char*)"Bob");
	printList(list);
	printListRev(list);
	insertNodeHeadOfList(&list, (char*)"Cris");
	printList(list);
	printListRev(list);
	insertNodeInList(&list, (char*)"Start", 0);
	printList(list);
	printListRev(list);
	insertNodeInList(&list, (char*)"mid", 3);
	printList(list);
	printListRev(list);
	printf("========================\n");
	printList(getNode(list, 3));
	removeNodeHeadOfList(&list);
	printList(list);
	printListRev(list);
	removeNodeFromList(&list, 2);
	printList(list);
	printListRev(list);
	removeNodeFromList(&list, 10);
	printList(list);
	printListRev(list);
	removeNodeFromList(&list, 2);
	printList(list);
	printListRev(list);
	printf("========================\n");
	printf("Search:\n");
	//search();
}
