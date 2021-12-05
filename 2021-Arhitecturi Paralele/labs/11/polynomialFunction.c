#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	if(argc<3) {
		printf("Program started with missing paramters. a file and x file missing.\n");
		MPI_Finalize();
		return 1;
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	if(rank==0) { // This code is run by a single process
		int polynomialSize;
		int xSize;

		FILE * coeficientsFile = fopen(argv[1],"rt");
		fscanf(coeficientsFile, "%i", &polynomialSize);
		float * a = malloc(sizeof(float)*polynomialSize);
		for(int i=0;i<polynomialSize;i++) {
			fscanf(coeficientsFile, "%f", a+i);
			// TODO send to each process the a coeficient it is responsible for during pipeline init
		}
		fclose(coeficientsFile);
		if(polynomialSize!=nProcesses) {
			//TODO when writing the pipeline make sure process 0 is responsible of a[0] and the first part of the computation.
			printf("Program started with wrong number of processes\n");
			return 2;
		}

		FILE * xFile = fopen(argv[2],"rt");
		fscanf(xFile, "%i", &xSize);
		float * x = malloc(sizeof(float)*xSize); 
		// TODO send xSize to all processes during pipeline init
		for(int i=0; i < xSize;i++) {
			fscanf(xFile, "%f", x+i);
		}
		fclose(xFile);

		for(int i=0; i<xSize; i++) {
			float partialPolynom = 0;
			float xPowI = 1;
			for(int j=0;j<polynomialSize;j++) { // TODO Replace for with pipeline
				partialPolynom += xPowI * a[j];
				xPowI *= x[i]; // more efficient than pow(x,i);
			}
			printf("%f ", partialPolynom); //TODO only the last process can print
		}
		printf("\n");
	}

	MPI_Finalize();
	return 0;
}