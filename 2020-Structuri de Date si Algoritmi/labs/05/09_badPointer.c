#include <stdio.h>
#include <stdlib.h>

int* func(int update)
{
	int a;
	if (update)
		a = 3;
	printf("%i\n", a);
	return &a;
}

int main(int argc, char* argv[])
{
	int* a = func(1);
	*a = 600;
	func(0);
	printf("%i\n", *a);
	return 0;
}