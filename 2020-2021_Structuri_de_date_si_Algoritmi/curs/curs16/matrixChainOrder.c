#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define n 6

int p[7] = {30, 35, 15, 5, 10, 20, 25};
int m[n + 1][n + 1];
int s[n + 1][n + 1];

void matrixChainOrder()
{
	for (int i = 1; i <= n; i++)
		m[i][i] = 0;
	for (int l = 2; l <= n; l++)
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			m[i][j] = 10000000;
			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
}

int main(int argc, char* argv[])
{
	matrixChainOrder();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			printf("%10d ", m[i][j]);
		printf("\n");
	}
}
