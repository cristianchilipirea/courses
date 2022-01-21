#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char b[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
int main(int argc, char* argv[])
{
	char a[4] = {'a', 'b', 'c', 'd'};
	int i_a = 0xffffffff;
	int v[4] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
	int i_b = 0xffffffff;
	printf("%i %i %i\n", strlen(a), strlen(b), i_a, i_b);
	printf("%p %p %p %p\n", a, b, &i_a, &i_b);
	return 0;
}