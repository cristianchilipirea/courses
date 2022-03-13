#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct binaryTreeNode {
	int value;
	struct binaryTreeNode* childLeft;
	struct binaryTreeNode* childRight;
	// struct binaryTreeNode *parent;
} binaryTreeNode;

int getHeight(binaryTreeNode* node)
{
	if (NULL == node)
		return 0;
	int heightLeft = getHeight(node->childLeft);
	int heightRight = getHeight(node->childRight);
	return 1 + fmax(heightLeft, heightRight);
}

void printBinaryTree(binaryTreeNode* bTreeNode)
{
	if (bTreeNode == NULL)
		return;
	// printf("(");
	printBinaryTree(bTreeNode->childLeft);
	printf("%i", bTreeNode->value);
	printBinaryTree(bTreeNode->childRight);
	// printf(")");
}

int bstSearch(binaryTreeNode* bstNode, int needle)
{
	if (bstNode == NULL)
		return 0;
	if (bstNode->value == needle)
		return 1;
	if (bstNode->value < needle)
		return bstSearch(bstNode->childRight, needle);
	return bstSearch(bstNode->childLeft, needle);
}

binaryTreeNode* createBSTNode(int value)
{
	binaryTreeNode* newBSTNode = (binaryTreeNode*)malloc(sizeof(binaryTreeNode));
	if (newBSTNode == NULL)
		return NULL;
	newBSTNode->value = value;
	newBSTNode->childLeft = NULL;
	newBSTNode->childRight = NULL;
	return newBSTNode;
}

binaryTreeNode* bstInsert(binaryTreeNode* bstNode, binaryTreeNode* toInsert)
{
	if (bstNode == NULL)
		return toInsert;
	if (bstNode->value < toInsert->value)
		bstNode->childRight = bstInsert(bstNode->childRight, toInsert);
	else if (bstNode->value >= toInsert->value)
		bstNode->childLeft = bstInsert(bstNode->childLeft, toInsert);
	return bstNode;
}

binaryTreeNode* bstInsertValue(binaryTreeNode* bstNode, int value)
{
	return bstInsert(bstNode, createBSTNode(value));
}

binaryTreeNode* bstRemove(binaryTreeNode* bstNode, int value)
{
	if (bstNode == NULL)
		return NULL;
	if (bstNode->value == value) {
		binaryTreeNode* aux = bstInsert(bstNode->childLeft, bstNode->childRight);
		free(bstNode);
		return aux;
	}
	if (bstNode->value < value)
		bstNode->childRight = bstRemove(bstNode->childRight, value);
	else if (bstNode->value > value)
		bstNode->childLeft = bstRemove(bstNode->childLeft, value);
	return bstNode;
}

// clang-format off
int main(int argc, char* argv[])
{
	binaryTreeNode* root = NULL;
	root = bstInsertValue(root, 5);
	root = bstInsertValue(root, 3);
	root = bstInsertValue(root, 2);
	root = bstInsertValue(root, 1);
	root = bstInsertValue(root, 7);
	root = bstInsertValue(root, 9);
	root = bstInsertValue(root, 8);
	root = bstInsertValue(root, 4);
	printf(">>>>%i<<<<<\n",getHeight(root));
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 3);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 7);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 5);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 1);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 2);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 4);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 8);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 9);
	printBinaryTree(root); printf("\n");
	root = bstInsertValue(root, 3);
	printBinaryTree(root); printf("\n");
	root = bstRemove(root, 3);
	printBinaryTree(root); printf("\n");
	return 0;
}
//clang-format on