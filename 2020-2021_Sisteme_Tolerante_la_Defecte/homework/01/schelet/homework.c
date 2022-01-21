#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc < 4) {
		printf("ERROR: Not enough arguments: <inputFileName> <outputFileName> <filter1> ... <filterK>\n");
		exit(-1);
	}

    return 0;
}