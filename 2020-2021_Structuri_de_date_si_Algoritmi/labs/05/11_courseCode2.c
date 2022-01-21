#include <stdio.h>
#define N 5

void fun1()
{
	int v[N];
	int i;
	for (i = 0; i < N; i++) {
		v[i] = i;
		printf("fun1: %p %i\n", v + i, v[i]);
	}
}

void fun2()
{
	int z[N];
	int i;
	for (i = 0; i < N; i++) {
		printf("fun2: %p %i\n", z + i, z[i]);
		z[i] = 0;
	}
}

int main()
{
	fun1();
	fun2();
	return 0;
}
