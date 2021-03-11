=====Lab 03=====

Scrieți cod pentru a putea rula următoarele programe (unul câte unul). (Vor fi necesare alocări, inițializări, șamd). **Nu faceți printări**. Folosiți ''#define N 10'' și alocați toate matricile vectorii global.

Măsurați timpul de execuție al fiecărui program folosind diverse valori pentru N (în general 10, 100, 500, 1000). Notați valorile obținute și desenați un graf aferent fiecărui program în Excel (google spreadsheets).

Timpi de execuție vor fi puși într-o tabelă de forma:

^ ^Factorial^Matrix^BubbleSort^BinarySearch^...^
|10 | | | | |
|100 | | | | |
|500 | | | | |
|1000| | | | |

<WRAP center round important 90%>
Măsurarea timpului de execuție: \\
Din LINUX \\
Mergeți la directorul în care aveți salvat codul \\ ''cd numedirector'' \\
''gcc cod.c -o executabil'' pentru compilare \\
''time ./executabil'' timpul relevant este **real** \\
</WRAP>
<WRAP center round important 90%>
Din Windows Porniți Powershell \\
Mergeți la directorul în care aveți salvat codul \\ ''cd numedirector'' \\
''Measure-Command { .\Program.exe }''
</WRAP>

<code c factorial.c>
// O(N)
long factorial(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}
</code>

<code c matrixMultiply.c>
// O(N^3)
for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		for (int k = 0; k < N; k++)
			c[i][j] += a[i][k] * b[k][j];
</code>

<code c bubbleSort.c>
// O(N^2)
for (int i = 0; i < N - 1; i++)
	for (int j = 0; j < N - i - 1; j++)
	{
		if (a[j] > a[j + 1])
		{
			aux = a[j];
			a[j] = a[j + 1];
			a[j + 1] = aux;
		}
	}
</code>

<code c binarySearch.c>
// O(log(N))
int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}
</code> 

<code cpp dirty.c>
// O(N^2)
int i = N;
while (i > 0)
{
    int Sum = 0;
    int j;
    for (j = 0; j < i; j++)
        Sum++;
        
    cout<< Sum << endl;
    i--;
}
</code>

<code c strangeCount.c>
// O(N log(N))
int counter = 0;
for (int i = 0; i < N; i++)
	for (int j = 1; j < N; j*=2)
			counter++;
printf("%i\n", counter);
</code>

<code c strangeCount3.c>
// O(N^5)
int counter = 0;
for (int i = 0; i < N; i++)
	for (int j = 1; j < pow(i, 2); j++)
		for (int k = 0; k < j; k++)
			counter++;
</code>

<code c strangeCount4.c>
//O(log(N)^3)
int counter = 0;
int i = 1;
while (i <= N) {
	i = i * 2;
	for (int j = 1; j < log10(i)/log10(2); j++)
		for(int k=1; k<=j;k++)
			counter++;
}
</code>