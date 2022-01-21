#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int aux;
	sscanf("123 a", "%i", aux);
	printf("%i\n", aux);
	return 0;
}