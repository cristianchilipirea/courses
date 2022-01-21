#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

int dpcutrod(int n)
{
	int r[11];
	r[0] = 0;
	for (int j = 1; j <= n; j++) {
		int q = -1;
		for (int i = 1; i <= j; i++)
			q = fmax(q, p[i] + r[j - i]);
		r[j] = q;
	}
	return r[n];
}

int cutrod(int n)
{
	if (n == 0)
		return 0;
	int q = -1;
	for (int i = 1; i <= n; i++)
		q = fmax(q, p[i] + cutrod(n - i));
	return q;
}

int r[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int memoizedcutrod(int n)
{
	if (r[n] >= 0)
		return r[n];
	int q;
	if (n == 0)
		q = 0;
	else {
		q = -1;
		for (int i = 1; i <= n; i++)
			q = fmax(q, p[i] + memoizedcutrod(n - i));
	}
	r[n] = q;
	return q;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
		return 1;
	int n = atoi(argv[1]);
	//printf("%d\n", cutrod(n));
	printf("%d\n", dpcutrod(n));
}