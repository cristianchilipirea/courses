#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 10

typedef struct listNode {
	char* key;
	char* value;
	listNode* next;
} listNode;

typedef struct hashMap {
	int numElements;
	listNode* buckets[M];
} hashMap;

int hash(const char* str)
{
	int sum = 0;
	for (; *str != '\0'; str++) {
		sum += *str;
		sum %= M;
	}
	return sum % M;
}

void insertNodeHeadOfList(listNode** listStart, char* key, char* value)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (node == NULL) {
		printf("ERROR: CAN NOT ALLOCATE RAM\n");
		return;
	}
	node->next = *listStart;
	node->key = key;
	node->value = value;
	*listStart = node;
}

void removeNodeHeadOfList(listNode** listStart)
{
	if (*listStart == NULL)
		return;
	listNode* aux = (*listStart);
	*listStart = (*listStart)->next;
	free(aux);
}

listNode* getNode(listNode* listNode, int poz)
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

void insertKeyValue(hashMap* HM, char* key, char* value)
{
}

char* getValue(hashMap HM, const char* key)
{
}

void removeKey(hashMap* HM, const char* key)
{
}

int getSize(hashMap HM)
{
	return HM.numElements;
}

int isEmpty(hashMap HM)
{
	return HM.numElements == 0;
}

void initHashMap(hashMap* HM)
{
	HM->numElements = 0;
	for (int i = 0; i < M; i++)
		HM->buckets[i] = NULL;
}

int main(int argc, char* argv[])
{
	hashMap HM;
	initHashMap(&HM);
	insertKeyValue(&HM, (char*)"cheia0", (char*)"valoare0");
	insertKeyValue(&HM, (char*)"cheia1", (char*)"valoare1");
	insertKeyValue(&HM, (char*)"cheia2", (char*)"valoare2");
	insertKeyValue(&HM, (char*)"cheia3", (char*)"valoare3");
	insertKeyValue(&HM, (char*)"cheia4", (char*)"valoare4");
	insertKeyValue(&HM, (char*)"cheia5", (char*)"valoare5");
	insertKeyValue(&HM, (char*)"cheia6", (char*)"valoare6");
	insertKeyValue(&HM, (char*)"cheia7", (char*)"valoare7");
	insertKeyValue(&HM, (char*)"cheia8", (char*)"valoare8");
	insertKeyValue(&HM, (char*)"cheia9", (char*)"valoare9");
	insertKeyValue(&HM, (char*)"cheia10", (char*)"valoare10");
	insertKeyValue(&HM, (char*)"cheia11", (char*)"valoare11");
	insertKeyValue(&HM, (char*)"cheia12", (char*)"valoare12");
	insertKeyValue(&HM, (char*)"cheia13", (char*)"valoare13");
	insertKeyValue(&HM, (char*)"cheia14", (char*)"valoare14");
	insertKeyValue(&HM, (char*)"cheia15", (char*)"valoare15");
	printf("%s\n", getValue(HM, "cheia0"));
	printf("%s\n", getValue(HM, "cheia1"));
	printf("%s\n", getValue(HM, "cheia2"));
	printf("%s\n", getValue(HM, "cheia6"));
	removeKey(&HM, "cheia0");
	insertKeyValue(&HM, (char*)"cheia1", (char*)"valoareNOUA");
	removeKey(&HM, "cheia6");
	printf("%s\n", getValue(HM, "cheia0"));
	printf("%s\n", getValue(HM, "cheia1"));
	printf("%s\n", getValue(HM, "cheia2"));
	printf("%s\n", getValue(HM, "cheia6"));

	return 0;
}