#include <stdio.h>

typedef int valueType;
typedef int keyType;
int T[100];
int sizeOfHashMap = 11;

valueType search(keyType key)
{
	for (int i = 0; i < sizeOfHashMap; i++) {  // M == sizeOfHashMap
		int j = hash(key, i);
		if (T[j] == NULL)
			return NULL;
		if (T[j] == key)
			return T[j];
	}
}

void insert(keyType key, valueType value)
{
	for (int i = 0; i < sizeOfHashMap; i++) {  // M == sizeOfHashMap
		int j = hash(key, i);
		if (T[j] == NULL) {
			T[j] = value;
			return;
		}
	}
	printf("hashMap full");
}

void delete (keyType key)
{
	T[key] = NULL;
}