#include <stdio.h>
/*
int subsecmax(int* v, int n)
{
	int max = -1000, i, j, k;
	for (i = 0; i < n; i++) {      // indexul de început
		for (j = i; j < n; j++) {  // indexul de final
			int sum = 0;
			for (k = i; k <= j; k++)
				sum += v[k];  // suma subsecvenţei
			if (sum > max) max = sum;
		}
	}
	return max;
}
*/
/*
int subsecmax(int* v, int n)
{
	int max = -1000, i, j;
	for (i = 0; i < n; i++) {  // indexul de început
		int sum = 0;
		for (j = i; j < n; j++) {  // indexul de final
			sum += v[j];
			if (sum > max)
				max = sum;
		}
	}
	return max;
}
*/
/*
int subsecmaxd(int* v, int l, int r)
{
	if (l == r)
		return v[l];
	int max1 = subsecmaxd(v, l, r - 1);
	int max2 = subsecmaxd(v, l + 1, r);
	int max = max1 > max2 ? max1 : max2;
	int sum = 0, i;
	for (i = l; i <= r; i++) sum += v[i];
	if (sum > max)
		return sum;
	else
		return max;
}
*/
/*
int subsecmaxd(int* v, int l, int r)
{
	if (l == r) return v[l];
	int m = (l + r) / 2;
	int max1 = subsecmaxd(v, l, m);
	int max2 = subsecmaxd(v, m + 1, r);
	int sum1 = v[m], sumLeft = v[m], i;
	for (i = m - 1; i >= l; i--) {
		sum1 += v[i];
		if (sum1 > sumLeft) sumLeft = sum1;
	}
	int sum2 = v[m + 1], sumRight = v[m + 1];
	for (i = m + 2; i <= r; i++) {
		sum2 += v[i];
		if (sum2 > sumRight) sumRight = sum2;
	}
	int max = max1 > max2 ? max1 : max2;
	if (sumLeft + sumRight < max) return max;
	return sumLeft + sumRight;
}

int subsecmax(int* v, int n)
{
	return subsecmaxd(v, 0, n);
}*/

int subsecmax(int* v, int n)
{
	int sumArray = v[0];     // suma maximă a unui subşir
	int sumMaxIndex = v[0];  // suma maximă pt. indexul i
	int i;
	for (i = 1; i < n; i++) {
		if (sumMaxIndex > 0)
			sumMaxIndex += v[i];
		else
			sumMaxIndex = v[i];
		if (sumMaxIndex > sumArray)
			sumArray = sumMaxIndex;
	}
	return sumArray;
}

int main(int argc, char* argv[])
{
	int v[7] = {5, -6, 3, 4, -2, 3, -3};
	printf("%d\n", subsecmax(v, 7));
	return 0;
}