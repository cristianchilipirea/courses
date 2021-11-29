===== Lab 04 Liste=====
Pentru o listă dublu înlănțuită, circulară:
  - Implementați afișarea unei liste. ''printList'' (Afișarea va avea forma ''[element1, element2]''). Pentru moment se va afișa o listă goală (''[]'')
  - Implementați inserarea unui element în capul de listă. ''insertNodeHeadOfList''
  - Implementați accesarea unui element. ''getNode''
  - Implementați inserarea unui element în orice loc din listă. ''insertNodeInList''
  - Implementați ștergerea unui element din capul de listă. ''removeNodeHeadOfList''
  - Implementați ștergerea unui element din orice loc din listă. ''removeNodeFromList''
  - Implementați și adăugați apelul pentru căutarea unui element din listă.
  - Implementați și adăugați apelul pentru o funcție care să printeze lista în ordine inversă folosind pointerii prev.

<code c schelet.c>
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    char* element;
    struct node* next;
    struct node* prev;
}listNode;

void insertNodeHeadOfList(listNode** listStart, char* element) {

}

listNode* getNode(listNode* listNode, int poz) {
    return NULL;
}

void insertNodeInList(listNode** listStart, char* element, int poz) {

}

void printList(listNode* listStart) {

}

void removeNodeHeadOfList(listNode** listStart) {

}

void removeNodeFromList(listNode** listStart, int poz) {

}

int main()
{
    listNode* list = NULL;
    insertNodeHeadOfList(&list, (char*)"Ana");
    printList(list);
    insertNodeHeadOfList(&list, (char*)"Bob");
    printList(list);
    insertNodeHeadOfList(&list, (char*)"Cris");
    printList(list);
    insertNodeInList(&list, (char*)"Start",0);
    printList(list);
    insertNodeInList(&list, (char*)"mid", 3);
    printList(list);
    printList(getNode(list, 3));
    removeNodeHeadOfList(&list);
    printList(list);
    removeNodeFromList(&list,2);
    printList(list);
    removeNodeFromList(&list, 10);
    printList(list);
    removeNodeFromList(&list, 2);
    printList(list);
}
</code>

Output dorit:
<code>
[Ana]
[Bob,Ana]
[Cris,Bob,Ana]
[Start,Cris,Bob,Ana]
[Start,Cris,Bob,mid,Ana]
[mid,Ana]
[Cris,Bob,mid,Ana]
[Cris,Bob,Ana]
[Cris,Bob,Ana]
[Cris,Bob]
</code>