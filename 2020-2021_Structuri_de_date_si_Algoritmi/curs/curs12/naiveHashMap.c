#include <stdio.h>

typedef int valueType;
typedef int keyType;
int T[100];

valueType search(keyType key)
{
	return T[key];
}

void insert(keyType key, valueType value)
{
	T[key] = value;
}

void delete (keyType key)
{
	T[key] = NULL;
}