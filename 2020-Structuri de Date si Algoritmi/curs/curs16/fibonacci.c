#include <stdio.h>
#include <stdlib.h>

int fiborec(int n)
{
	if (n <= 1)
		return n;
	return fiborec(n - 1) + fiborec(n - 2);
}

int F[1000];
int fibo(int n)
{
	F[0] = 0;
	F[1] = 1;
	for (int i = 2; i <= n; i++)
		F[i] = F[i - 1] + F[i - 2];
	return F[n];
}

int main(int argc, char* argv[])
{
	if (argc < 2)
		return 1;
	int n = atoi(argv[1]);
	//printf("%d\n", fiborec(n));
	printf("%d\n", fibo(n));
}