#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int* aux = (int*)5;
	free(aux);
	return 0;
}