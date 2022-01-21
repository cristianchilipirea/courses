#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack[100];
int indexStack = 0;

void push(int value)
{
	if (indexStack < 100) {
		stack[indexStack] = value;
		indexStack++;
	} else {
		printf("Dimensiune stiva depasita!\n");
	}
}

int pop()
{
	if (0 < indexStack) {
		indexStack--;
		int value = stack[indexStack];
		stack[indexStack] = 0;
		return value;
	}
	printf("Stiva este goala!\n");
	return 0;
}

typedef struct bstNode {
	int value;
	struct bstNode* childLeft;
	struct bstNode* childRight;
} bstNode;

bstNode* bstInsert(bstNode* startNode, int value)
{
	// Implement sequentially NOT recursively
	return startNode;
}

void bstPrint(bstNode* startNode)
{
	// Implement sequentially NOT recursively
}

int bstSearch(bstNode* startNode, int value)
{
	// Implement sequentially NOT recursively
	return 0;
}

void bstDelete(bstNode* startNode, int value)
{
	// Implement sequentially NOT recursively
}

int bstHeight(bstNode* startNode)
{
	// Implement sequentially NOT recursively
	return 0;
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

	printf("*** Search node test: ***\n");
	if (bstSearch(bstRoot, 2))
		printf("Element 2 exists\n");
	else
		printf("Element 2 does NOT exist\n");
	if (bstSearch(bstRoot, 4))
		printf("Element 4 exists\n");
	else
		printf("Element 4 does NOT exist\n");

	printf("*** Delete node test: ***\n");
	bstDelete(bstRoot, 2);
	bstPrint(bstRoot);
	printf("\n");
	bstDelete(bstRoot, 4);
	bstPrint(bstRoot);
	printf("\n");

	printf("*** Get height test: ***\n");
	printf("Inaltimea arborelui este %d.\n", bstHeight(bstRoot));

	return 0;
}