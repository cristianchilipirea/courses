#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char value;
	struct node* childLeft;
	struct node* childRight;
} node;

node* readTree(FILE* f)
{
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
		//TODO trebuie completat resul nodului expression.
		//     aici va fi macar un apel recursiv
	} else {
		//TODO
	}
	return expression;
}

node* readTreeFromFile(const char* fileName)
{
	FILE* f = fopen(fileName, "r");
	if (f == NULL)
		return NULL;
	node* expression = readTree(f);
	fclose(f);
	return expression;
}

void printPolish(node* expresion)
{
}

void printNormal(node* expresion)
{
}

int evaluate(node* expression)
{
}

int getHight(node* expression)
{
}

int getLeafs(node* expression)
{
}

int areEqual(node* a, node* b)
{
}

int main()
{
	node* expression1 = readTreeFromFile("expresie.txt");
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