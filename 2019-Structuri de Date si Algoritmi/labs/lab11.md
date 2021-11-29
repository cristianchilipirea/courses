===== Lab 11 Hash + Divide et Impera =====

  - Implementați un hashmap
    - Funcția de inserție în hashmap
    - Funcția de extragere a unei valori dânduse cheia
    - Funcția de ștergere a unei valori din hashmap
  - Implementați algoritmul de căutare binară folosind vectori.
  - Implementați algoritmul merge sort folosind vectori.
**Pentru curajoși:**
  - Implementați căutare binară folosind liste.
  - Implementați merge sort folosind liste.

<code c schelet.c>
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define M 10

typedef struct listNode {
	char* key;
	char* value;
	listNode* next;
}listNode;

typedef struct hashMap {
	int numElements;
	listNode* buckets[M];
}hashMap;

int hash(const char* str) {
	int sum = 0;
	for (; *str != '\0'; str++) {
		sum += *str;
		sum %= M;
	}
	return sum % M;
}

void insertNodeHeadOfList(listNode** listStart, char* key, char* value) {
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

void removeNodeHeadOfList(listNode** listStart) {
	if (*listStart == NULL)
		return;
	listNode* aux = (*listStart);
	*listStart = (*listStart)->next;
	free(aux);
}

listNode* getNode(listNode* listNode, int poz) {
	if (listNode == NULL)
		return NULL;
	for (int i = 0; i < poz; i++) {
		if (listNode->next == NULL)
			break;
		listNode = listNode->next;
	}
	return listNode;
}

void removeNodeFromList(listNode** listStart, int poz) {
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

void insertKeyValue(hashMap* HM, char* key, char* value) {
	
}

char* getValue(hashMap HM, const char* key) {
	
}

void removeKey(hashMap* HM, const char* key) {
	
}

int getSize(hashMap HM) {
	return HM.numElements;
}

int isEmpty(hashMap HM) {
	return HM.numElements == 0;
}

void initHashMap(hashMap* HM) {
	HM->numElements = 0;
	for (int i = 0; i < M; i++)
		HM->buckets[i] = NULL;
}

int binarySearch(int* values, int needle, int start, int end) {
	
}

int cmp(const void* a, const void* b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

void merge(int source[], int start, int mid, int end, int destination[]) {
	
}

void mergeSort(int** v, int start, int end) {
	
}


int main()
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

	printf("\n");
	int values[] = { 0,2,4,6,8,10,12,14,16,18 };
	printf("Binary search position of 2 is %i\n", binarySearch(values, 2, 0, 10));
	printf("Binary search position of 1 is %i\n", binarySearch(values, 1, 0, 10));

	int N = 64;
	int *v, *vQSort;
	v = (int*)malloc(sizeof(int) * N);
	vQSort = (int*)malloc(sizeof(int) * N);
	if (v == NULL || vQSort == NULL)
		return 0;
	srand(42);
	for (int i = 0; i < N; i++) {
		v[i] = rand() % N;
		vQSort[i] = v[i];
	}

	qsort(vQSort, N, sizeof(int), cmp);
	for (int i = 0; i < N; i++)
		printf("%3i ",vQSort[i]);
	printf("\n");
	
	mergeSort(&v, 0, N);
	int isSorted = 1;
	for (int i = 0; i < N; i++) {
		printf("%3i ", v[i]);
		if (vQSort[i] != v[i])
			isSorted = 0;
	}
	printf("\n");

	if (isSorted)
		printf("Este sortat corect\n");
	else
		printf("NU este sortat corect\n");

	return 0;
}
</code>

<code c output>
valoare0
valoare1
valoare2
valoare6
(null)
valoareNOUA
valoare2
(null)

Binary search position of 2 is 1
Binary search position of 1 is -1
  0   0   0   1   1   3   3   4   4   6   7  11  11  13  13  13  15  15  15  16  16  16  16  19  20  21  21  24  25  25  26  28  28  28  31  31  32  34  35  35  35  37  38  38  39  40  41  41  42  43  43  43  47  47  48  53  53  54  54  54  57  59  62  63
  0   0   0   1   1   3   3   4   4   6   7  11  11  13  13  13  15  15  15  16  16  16  16  19  20  21  21  24  25  25  26  28  28  28  31  31  32  34  35  35  35  37  38  38  39  40  41  41  42  43  43  43  47  47  48  53  53  54  54  54  57  59  62  63
Este sortat corect
</code>