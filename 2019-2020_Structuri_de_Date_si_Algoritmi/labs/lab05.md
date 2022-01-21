===== Lab 05 Liste =====

  - Implementați funcția ''copyVector'' care să creeze o nouă listă și să adauge toate elementele unui vector acesteia. Atenție la ordinea elementelor.
  - Implementați funcția ''getMid'' care printr-o singură parcurgere să returneze elementul din centrul listei.
  - Implementați funcția ''joinLists'' care să primească două liste și să le unească punând elementele unei liste după elementele celeilalte liste. [1,2,3] și [4,5] rezultă în [1,2,3,4,5]. Listele inițiale **NU** vor fi păstrate. Nu ștergeți sau alocați memorie.
  - Implementați funcția ''mergeLists'' care să primească două liste sortate și să le unească păstrând ordinea elementelor (Operația de merge din merge sort). [1,3,5] și [2,3] rezultă în [1,2,3,4,5]. Listele inițiale vor fi păstrate.
  - Implementați funcția ''copyBits'' care primește un număr întreg și creează o listă cu valorile biților acestuia. A se folosi operații pe biți.

Pentru rezolvarea exercițiilor puteți pornii de la codul următor:
<code c linkedList.c>
#include <stdio.h>
#include <stdlib.h>
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
    for (int i = 0; i < poz; i++) {
        listNode = listNode->next;
        if (listNode->next == NULL)
            break;
    }
    return listNode;
}

void insertNodeInList(listNode** listStart, int element, int poz) {
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
    listNode* aux = getNode(*listStart, poz-1);
    if (aux->next != NULL) {
        listNode* aux1 = aux->next;
        aux->next = aux->next->next;
        free(aux1);
    }
}

void copyVector(listNode** out, int* in, int numElVector) {

}

int getMid(listNode* listStart) {

}

void joinLists(listNode** out, listNode** a, listNode** b) {

}

void mergeLists(listNode** out, listNode** a, listNode** b) {

}

void copyBits(listNode** out, int bits) {

}

int main()
{

}
</code>