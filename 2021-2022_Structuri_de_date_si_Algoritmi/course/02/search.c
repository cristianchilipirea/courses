int search(int *v, int n, int a)
{
	int i = 0;
	while (i < n)
	{
		if (v[i] == a)
		{
			return i;
		}
		i++;
	}
	return -1;
}
