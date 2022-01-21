int hash(char *str, int M)
{
	int sum = 0;
	for (; *str; str++) {
		sum += *str;
		sum %= M;
	}
	return sum % M;
}

unsigned long djb2(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

static unsigned long sdbm(unsigned char *str)
{
	unsigned long hash = 0;
	int c;

	while (c = *str++)
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}