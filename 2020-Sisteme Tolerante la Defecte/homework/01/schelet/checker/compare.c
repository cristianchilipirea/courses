#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	unsigned char a, b;
	char magicNumberA[3] = { 0 }, magicNumberB[3] = { 0 };
	unsigned char dataA, dataB;

	if(argc < 3)
		return 1;
	FILE * fA = fopen(argv[1], "rb");
	FILE * fB = fopen(argv[2], "rb");
	
	if(fA==NULL || fB==NULL)
		return 1;

	fscanf(fA, "%s\n", magicNumberA);
	fscanf(fB, "%s\n", magicNumberB);

	if(strcmp(magicNumberA, magicNumberB) != 0)
		return 1;

	int widthA, heightA, maxvalA, widthB, heightB, maxvalB;
	fscanf(fA, "%d %d\n", &widthA, &heightA);
	fscanf(fA, "%d\n", &maxvalA);
	fscanf(fB, "%d %d\n", &widthB, &heightB);
	fscanf(fB, "%d\n", &maxvalB);

	if(widthA != widthB || heightA != heightB || maxvalA != maxvalB)
		return 1;

	if (strcmp(magicNumberA, "P5") == 0)
	{
		for(int i = 0; i < heightA; i++)
		{
			for(int j = 0; j < widthA; j++)
			{
				size_t a = fread(&dataA, sizeof(unsigned char), 1, fA);
				size_t b = fread(&dataB, sizeof(unsigned char), 1, fB);

				if(a != b || a <= 0 || b <= 0)
					return 1;
				
				if(fabs(dataA - dataB) > 2)
					return 1;
			}
		}
	}
	else
	{
		for(int i = 0; i < heightA; i++)
		{
			for(int j = 0; j < widthA; j++)
			{
				for(int k = 0; k < 3; k++)
				{
					size_t a = fread(&dataA, sizeof(unsigned char), 1, fA);
					size_t b = fread(&dataB, sizeof(unsigned char), 1, fB);
					
					if(a != b || a <= 0 || b <= 0)
						return 1;

					if(fabs(dataA - dataB) > 2)
						return 1;
				}
			}
		}
	}

	return 0;
}