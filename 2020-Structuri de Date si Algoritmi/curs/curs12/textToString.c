#include <stdio.h>
#include <string.h>

int textToInteger(char* text, int MAX)
{
	int l = strlen(text);
	int rez = 0;
	for (int i = 0; i < l; i++) {
		rez = rez * 256 + text[i];
		rez %= MAX;
	}
	return rez;  // numere între 0 şi MAX-1
}

int sizeOfHashMap = 11; // M
int h(int val)
{
	return val % sizeOfHashMap;
}

int hashString(char* text)
{
	int val = textToInteger(text, 256);
	return h(val);
}

int main(int argc, char* argv[])
{
	printf("%i\n", textToInteger("ABC", 256));
	return 0;
}
