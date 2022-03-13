#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct binaryTreeNode {
	int value;
	struct binaryTreeNode* childLeft;
	struct binaryTreeNode* childRight;
	int height;
	// struct binaryTreeNode *parent;
} binaryTreeNode;

void printBinaryTree(binaryTreeNode* bTreeNode)
{
	if (bTreeNode == NULL)
		return;
	printf("(");
	printBinaryTree(bTreeNode->childLeft);
	printf("%i", bTreeNode->value);
	printBinaryTree(bTreeNode->childRight);
	printf(")");
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
	newBSTNode->height = 1;
	return newBSTNode;
}

int getHeight(binaryTreeNode* N)
{
}

int getBalanceFactor(binaryTreeNode* N)
{
}

binaryTreeNode* rightRotate(binaryTreeNode* y)
{
}

binaryTreeNode* leftRotate(binaryTreeNode* x)
{
}

binaryTreeNode* bstInsert(binaryTreeNode* bstNode, binaryTreeNode* toInsert)
{
	if (toInsert == NULL)
		return bstNode;
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

binaryTreeNode* bstAVLInsert(binaryTreeNode* bstNode, binaryTreeNode* toInsert)
{
}

binaryTreeNode* bstAVLInsertValue(binaryTreeNode* bstNode, int value)
{
	return bstAVLInsert(bstNode, createBSTNode(value));
}

binaryTreeNode* bstRemove(binaryTreeNode* bstNode, int value)
{
}

binaryTreeNode* bstAVLRemove(binaryTreeNode* bstNode, int value)
{
}

// clang-format off
int main(int argc, char* argv[])
{
	binaryTreeNode* root = NULL;
	root = bstAVLInsertValue(root, 1);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 2);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 3);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 4);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 5);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 6);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 7);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 8);
	printBinaryTree(root); printf("\n");
	root = bstAVLInsertValue(root, 9);
	printBinaryTree(root); printf("\n");
	root = bstAVLRemove(root, 3);
	printBinaryTree(root); printf("\n");
	root = bstAVLRemove(root, 2);
	printBinaryTree(root); printf("\n");
	root = bstAVLRemove(root, 1);
	printBinaryTree(root); printf("\n");
	root = bstAVLRemove(root, 4);
	printBinaryTree(root); printf("\n");
	root = bstAVLRemove(root, 5);
	printBinaryTree(root); printf("\n");
	return 0;
}
//clang-format on