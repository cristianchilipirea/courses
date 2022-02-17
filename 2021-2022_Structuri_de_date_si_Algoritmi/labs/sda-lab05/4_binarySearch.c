#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Need to run with a parameter N, in VsCode you can configure to run in launch.json on the args line\n");
		return 1;
	}
	int N = atoi(argv[1]);
	printf("Hello World! N is %i\n", N);
	return 0;
}

/*
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
*/