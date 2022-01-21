#include <stdlib.h>

int fun1()
{
	return 1;
}

void fun2()
{
	int d = 0;
	fun1();
	return;
}

int main()
{
	int a = 5;
	int v[4] = {0, 1, 2, 3};
	int* vv = (int*)malloc(5);
	vv[3] = 5;
	fun2();
	a = fun1();
	return 0;
}
