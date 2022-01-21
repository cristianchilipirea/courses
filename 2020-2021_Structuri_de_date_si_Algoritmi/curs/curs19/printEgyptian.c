/*
void printEgyptian(int nr, int dr)
{
	if (dr == 0 || nr == 0)
		return;
	if (dr % nr == 0) {
		printf("1/%d", dr / nr);
		return;
	}
	if (nr % dr == 0) {
		printf("%d", nr / dr);
		return;
	}
	if (nr > dr) {
		printf("%d + ", nr / dr);
		printEgyptian(nr % dr, dr);
		return;
	}
	int n = dr / nr + 1;
	printf("1/%d +", n);
	printEgyptian(nr * n - dr, dr * n);
}
*/
void printEgyptian(int nr, int dr)
{
	while (dr != 0 && nr != 0) {
		if (dr % nr == 0) {
			printf("1/%d", dr / nr);
			return;
		}
		int n = dr / nr + 1;
		printf("1/%d +", n);
		nr = nr * n - dr;
		dr = dr * n;
	}
}

int main()
{
	int nr = 6, dr = 14;
	printf("Egyptian Fraction Representation of %d/%d is \n", nr, dr);
	printEgyptian(nr, dr);
	return 0;
}