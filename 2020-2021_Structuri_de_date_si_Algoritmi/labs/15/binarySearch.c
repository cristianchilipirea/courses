#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binarySearch(int* values, int needle, int start, int end)
{
}

int main(int argc, char* argv[])
{
	printf("\n");
	int values[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
	printf("Binary search position of 2 is %i\n", binarySearch(values, 2, 0, 10));
	printf("Binary search position of 1 is %i\n", binarySearch(values, 1, 0, 10));
}