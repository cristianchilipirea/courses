===== Lab 07 Arbori =====

Pentru acest laborator veți construi și folosi arbori binari ce reprezintă expresii matematice.

**Simplificare:** În expresie pot apărea doar +,-,*,/ și cifre (nu numere). Este mult mai simplu dacă implementați fiecare exercițiu recursiv (tratezi subarbore stâng, tratezi subarbore drept, combini rezultatul folosind informații despre nodul curent și întorci rezultatul pentru arborele părinte). Ca să obțineți dintr-un caracter ''c'' un număr de o cifră puteți scrie '' c - '0' ''.

  - Se citește dintr-un fișier o expresie matematică cu [[https://en.wikipedia.org/wiki/Polish_notation|notație Poloneză]] (formă prefixată). Să se creeze [[https://en.wikipedia.org/wiki/Binary_expression_tree|arborele binar aferent expresiei]].
  - Implementați funcția pentru afișarea arborelui obținut anterior. Afișare identică cu fișierul de intrare.
  - Implementați funcția pentru afișarea arborelui în formă matematică normală. Nu uitați de paranteze.
  - Implementați funcția pentru evaluarea arborelui obținut anterior.
  - Implementați o funcție care să afișeze care este înălțimea arborelui.
  - Implementați o funcție care să determine numărul de constante (cifre) (Hint: Numărul de frunze).
  - Să se scrie un program care să determine dacă 2 arbori sunt echivalenți (aceeași structură și aceleași valori ca noduri).

Pentru cei curajoși implementați un program care să permită folosirea de numere și chiar variabile (litere) în expresia Poloneză.

<code c expresie.txt>
+ 3 * 2 - 9 5
</code>

<code c expresie1.txt>
+ 3 3
</code>


<code c schelet.c>
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<string.h>

typedef struct node {
	char value;
	struct node* childLeft;
	struct node* childRight;
}node;

node* readTree(FILE* f) {
	char aux;
	if (feof(f))
		return NULL;
	fscanf(f, "%c", &aux);
	if (aux == ' ')
		return readTree(f);
	node* expression = (node*)malloc(sizeof(node));
	if (expression == NULL)
		return NULL;
	expression->value = aux;
	if (aux == '+' || aux == '-' || aux == '*' || aux == '/') {
//TODO aici va fi macar un apel recursiv
	} else {
//TODO
	}
	return expression;
}

node * readTreeFromFile(const char* fileName) {
	FILE* f = fopen(fileName, "r");
	if (f == NULL)
		return NULL;
	node* expression = readTree(f);
	fclose(f);
	return expression;
}

void printPolish(node* expresion) {

}

void printNormal(node* expresion) {

}

int evaluate(node* expression) {

}

int getHight(node* expression) {

}

int getLeafs(node* expression) {

}

int areEqual(node* a, node* b) {

}

int main() 
{
	node * expression1 = readTreeFromFile("expresie.txt");
	printPolish(expression1);
	printf("\n");
	printNormal(expression1);
	printf("\n");
	int rezult = evaluate(expression1);
	printf("%i\n", rezult);
	int hight = getHight(expression1);
	printf("%i\n", hight);
	int leafs = getLeafs(expression1);
	printf("%i\n", leafs);
	node* expression2 = readTreeFromFile("expresie.txt");
	node* expression3 = readTreeFromFile("expresie1.txt");
	int equality = areEqual(expression1, expression2);
	if (equality)
		printf("Arborele din expresie.txt este identic cu cel din expresie.txt\n");
	else
		printf("Arborele din expresie.txt este DIFERIT de cel din expresie.txt\n");
	equality = areEqual(expression2, expression3);
	if (equality)
		printf("Arborele din expresie.txt este identic cu cel din expresie1.txt\n");
	else
		printf("Arborele din expresie.txt este DIFERIT de cel din expresie1.txt\n");
	return 0;
}
</code>

<code c output>
+ 3 * 2 - 9 5
(3+(2*(9-5)))
11
4
4
Arborele din expresie.txt este identic cu cel din expresie.txt
Arborele din expresie.txt este DIFERIT de cel din expresie1.txt
</code>