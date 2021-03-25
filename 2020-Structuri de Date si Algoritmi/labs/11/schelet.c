#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trieNode {
	char letter;
	struct trieNode** children;
	int numChildren;
} trieNode;

void trieInsert(trieNode* currentNode, const char* word)
{
	//ghidul e pentru implementare recursiva, s-ar putea sa va vina mai usor una iterativa

	//verifica daca prima litera e deja in trie

	//daca nu este adauga un nod
	//apeleaza recursiv cu noul nod si (word+1)

	//creeaza o noua lista de copii si adauga noul nod la aceasta, va trebui copiata lista
	//a se adauga si nod pentru '\0'
}

void triePrintWords(trieNode* currentNode, const char* word)
{
	//ghidul e pentru implementare recursiva, s-ar putea sa va vina mai usor una iterativa
	//daca ai ajuns la \0 afiseaza word

	//pentru toate literele de nivel copil apeleaza recursiv unde word este strcat intre el si litera curenta
	//va trebui copiat word intr-un vector de char auxiliar
	//strcpy, strcat
}

void triePrint(trieNode* currentNode)
{
}

int trieSearch(trieNode* currentNode, const char* word)
{
	return 0;
}

int getSizeLongestWord(trieNode* currentNode)
{
	return 0;
}

int main(int argc, char* argv[])
{
	trieNode* trieRoot = (trieNode*)malloc(sizeof(trieNode));
	if (trieRoot == NULL)
		return 1;
	trieRoot->numChildren = 0;
	trieRoot->children = NULL;
	trieRoot->letter = ' ';
	trieInsert(trieRoot, "bob");
	trieInsert(trieRoot, "bocanc");
	trieInsert(trieRoot, "bobina");
	triePrint(trieRoot);
	printf("\n");
	triePrintWords(trieRoot, "");
	printf("\n");
	if (trieSearch(trieRoot, "boca"))
		printf("boca is in the trie\n");
	else
		printf("boca is NOT in the trie\n");
	if (trieSearch(trieRoot, "bob"))
		printf("bob is in the trie\n");
	else
		printf("bob is NOT in the trie\n");
	if (trieSearch(trieRoot, "bocanc"))
		printf("bocanc is in the trie\n");
	else
		printf("bocanc is NOT in the trie\n");

	printf("\nLongest Word has %i characters\n", getSizeLongestWord(trieRoot));

	return 0;
}