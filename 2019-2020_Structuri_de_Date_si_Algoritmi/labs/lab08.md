===== Lab 08 Arbori =====

Arbori binari de căutare:

  - Implementați afișarea unui arbore binar de căutare. Atenție numerele trebuiesc afișate sortate crescător.
  - Implementați funcția pentru inserarea unui element într-un arbore binar de căutare.
  - Implementați funcția pentru căutarea unui element într-un arbore binar de căutare.

Construcție [[https://en.wikipedia.org/wiki/Trie|Trie]]. Fiecare nod va conține o literă. Rădăcina va conține caracterul 'space'. Parcurgând arborele de la rădăcină la o frunză vom putea afișa un cuvânt. Un nod nu poate avea doi copii cu aceeași literă:

  - Implementați afișarea unui arbore în care fiecare nod poate să aibă oricâți copii. Recursiv, parcurgere în adâncime.
  - Implementați afișarea unui arbore de tip trie care să printeze pe fiecare linie câte un cuvânt introdus în trie. Hint: Puteți folosi un string pe care să îl trimiteți în recursivitate alăruti de mărimea sa.
  - Implementați introducere unui cuvânt în trie. Atenție ca un nod să nu aibă 2 copii cu aceeași literă.
  - Implementați căutarea unui cuvânt intr-un trie.

**Pentru curajoși**: Arbori [[https://en.wikipedia.org/wiki/Shannon%E2%80%93Fano_coding|Shannon–Fano]]

  - Implementați funcția care creează un arbore Shannon–Fano.
    - Dintr-un fișer se citesc caracterele.
    - Pentru fiecare caracter se numără câte apariții are în fișer (vector structură numă apariții și caracter).
    - Se sortează după numărul de apariții.
    - Se crează arborele Shannon–Fano împărțind vector în două bucăți în mod recursiv. Inițial rădăcina va avea tot vectorul, apoi cei 2 copii vor avea fiecare câte jumate, și tot așa până ce fiecare nod va avea maxim un caracter. Împărțirea se va face nu după numărul de elemente ci după suma probabilităților. (Hint reprezentare: căutare binară)
  - Implementați funcția care să afișeze un arbore Shannon–Fano.

<code c schelet.c>
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>

typedef struct bstNode {
	int value;
	struct bstNode* childLeft;
	struct bstNode* childRight;
}bstNode;

bstNode* bstInsert(bstNode* currentNode, int value) { 
        //codul ajutator de mai jos e recursiv dar se poate sa fie mai usor implementare iterativa
	if (currentNode == NULL) {
		//cream nodul pentru a fi inserat
		return toInsert;
	}

	if (currentNode->value < value) {
		//apel recursiv reconectare unul din copii
	} else if (currentNode->value >= value) {
		//apel recursiv reconectare unul din copii
	}

	return currentNode;
}

void bstPrint(bstNode* currentNode) {
	
}

int bstSearch(bstNode* currentNode, int value) {
	
}


typedef struct trieNode {
	char letter;
	struct trieNode** children;
	int numChildren;
}trieNode;

void trieInsert(trieNode* currentNode, const char * word) {
        //ghidul e pentru implementare recursiva, s-ar putea sa va vina mai usor una iterativa
	//verifica daca prima litera e deja in trie

        //daca nu este adauga un nod
        //apeleaza recursiv cu noul nod si (word+1)

	//creeaza o noua lista de copii si adauga noul nod la aceasta, va trebui copiata lista
        //a se adauga si nod pentru '\0'
}

void triePrintWords(trieNode* currentNode, const char * word) {
        //ghidul e pentru implementare recursiva, s-ar putea sa va vina mai usor una iterativa
        //daca ai ajuns la \0 afiseaza word
	
        //pentru toate literele de nivel copil apeleaza recursiv unde word este strcat intre el si litera curenta
        //va trebui copiat word intr-un vector de char auxiliar
        //strcpy, strcat
}

void triePrint(trieNode* currentNode) {
	
}

int trieSearch(trieNode* currentNode, const char* word) {
	
}

int main()
{
	//BINARY SEARCH TREE (BST)
	bstNode* bstRoot = NULL;
	bstRoot = bstInsert(bstRoot, 5);
	bstPrint(bstRoot);
	printf("\n");
	bstRoot = bstInsert(bstRoot, 3);
	bstPrint(bstRoot);
	printf("\n");
	bstRoot = bstInsert(bstRoot, 7);
	bstPrint(bstRoot);
	printf("\n");
	bstRoot = bstInsert(bstRoot, 1);
	bstPrint(bstRoot);
	printf("\n");
	bstRoot = bstInsert(bstRoot, 9);
	bstPrint(bstRoot);
	printf("\n");
	bstRoot = bstInsert(bstRoot, 2);
	bstPrint(bstRoot);
	printf("\n");
	bstRoot = bstInsert(bstRoot, 6);
	bstPrint(bstRoot);
	printf("\n");
	if (bstSearch(bstRoot, 2))
		printf("Element 2 exists\n");
	else
		printf("Element 2 does NOT exist\n");
	if (bstSearch(bstRoot, 4))
		printf("Element 4 exists\n");
	else
		printf("Element 4 does NOT exist\n");

	//TRIE
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
	return 0;
}
</code>

<code c output>
5
3 5
3 5 7
1 3 5 7
1 3 5 7 9
1 2 3 5 7 9
1 2 3 5 6 7 9
Element 2 exists
Element 4 does NOT exist
 bob ina canc
 bob
 bobina
 bocanc

boca is NOT in the trie
bob is in the trie
bocanc is in the trie
</code>