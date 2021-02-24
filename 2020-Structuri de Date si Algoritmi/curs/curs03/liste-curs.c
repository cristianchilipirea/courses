#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char *element;
    struct node *next;
} listNode;

void printList(listNode *listStart)
{
}

void insertNodeHeadOfList(listNode **listStart, char *element)
{
}

void insertNodeInList(listNode **listStart, char *element, int poz)
{
}

listNode *getNode(listNode *listNode, int poz)
{
}

void removeNodeHeadOfList(listNode **listStart)
{
}

void removeNodeFromList(listNode **listStart, int poz)
{
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
