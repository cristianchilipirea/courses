int sum(int *v, int n)
{
	int s = 0;
	int i = 0;
	while (i < n)
	{
		s += v[i];
		i++;
	}
	return s;
}
