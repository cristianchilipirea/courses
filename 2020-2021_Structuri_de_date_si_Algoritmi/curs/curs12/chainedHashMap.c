#include <stdio.h>

typedef int valueType;
typedef int keyType;
int T[100];

valueType search(keyType key)
{
	return listSearch(T[hash(key)], key);
}

void insert(keyType key, valueType value)
{
	listInsertHead(T[hash(key)], key, value);
}

void delete (keyType key)
{
	listDelete(T[hash(key)], key);
}