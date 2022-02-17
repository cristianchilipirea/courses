#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char b[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
int main(int argc, char* argv[])
{
	char* a = malloc(sizeof(char) * 8);
	int i_a = 0xffffffff;
	int v[4] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
	a[0] = 'a';
	a[1] = 'b';
	a[2] = 'c';
	a[3] = 'd';
	a[4] = 'e';
	a[5] = 'f';
	a[6] = 'g';
	a[7] = 'h';
	int i_b = 0xffffffff;
	printf("%i %i %i\n", strlen(a), strlen(b), i_a, i_b);
	printf("%p %p %p %p\n", &a, b, &i_a, &i_b);
	free(a);
	return 0;
}