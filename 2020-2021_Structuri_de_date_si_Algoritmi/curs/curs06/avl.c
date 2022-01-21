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
	if (N == NULL)
		return 0;
	return N->height;
}

int getBalanceFactor(binaryTreeNode* N)
{
	if (N == NULL)
		return 0;
	return getHeight(N->childLeft) - getHeight(N->childRight);
}

binaryTreeNode* rightRotate(binaryTreeNode* y)
{
	binaryTreeNode* x = y->childLeft;
	binaryTreeNode* T2 = x->childRight;

	x->childRight = y;
	y->childLeft = T2;

	y->height = fmax(getHeight(y->childLeft), getHeight(y->childRight)) + 1;
	x->height = fmax(getHeight(x->childLeft), getHeight(x->childRight)) + 1;

	return x;
}

binaryTreeNode* leftRotate(binaryTreeNode* x)
{
	binaryTreeNode* y = x->childRight;
	binaryTreeNode* T2 = y->childLeft;

	y->childLeft = x;
	x->childRight = T2;

	x->height = fmax(getHeight(x->childLeft), getHeight(x->childRight)) + 1;
	y->height = fmax(getHeight(y->childLeft), getHeight(y->childRight)) + 1;

	return y;
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
	if (toInsert == NULL)
		return bstNode;
	if (bstNode == NULL)
		return toInsert;
	if (bstNode->value < toInsert->value)
		bstNode->childRight = bstAVLInsert(bstNode->childRight, toInsert);
	else if (bstNode->value > toInsert->value)
		bstNode->childLeft = bstAVLInsert(bstNode->childLeft, toInsert);
	else
		return bstNode;

	bstNode->height = fmax(getHeight(bstNode->childLeft), getHeight(bstNode->childRight)) + 1;

	int balanceFactor = getBalanceFactor(bstNode);

	int toInsertValue = toInsert->value;

	// Left Left Case
	if (balanceFactor > 1 && toInsertValue < bstNode->childLeft->value)
		return rightRotate(bstNode);

	// Right Right Case
	if (balanceFactor < -1 && toInsertValue > bstNode->childRight->value)
		return leftRotate(bstNode);

	// Left Right Case
	if (balanceFactor > 1 && toInsertValue > bstNode->childLeft->value) {
		bstNode->childLeft = leftRotate(bstNode->childLeft);
		return rightRotate(bstNode);
	}

	// Right Left Case
	if (balanceFactor < -1 && toInsertValue < bstNode->childRight->value) {
		bstNode->childRight = rightRotate(bstNode->childRight);
		return leftRotate(bstNode);
	}

	return bstNode;
}

binaryTreeNode* bstAVLInsertValue(binaryTreeNode* bstNode, int value)
{
	return bstAVLInsert(bstNode, createBSTNode(value));
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

binaryTreeNode* bstAVLRemove(binaryTreeNode* bstNode, int value)
{
	if (bstNode == NULL)
		return NULL;

	if (bstNode->value < value)
		bstNode->childRight = bstAVLRemove(bstNode->childRight, value);
	else if (bstNode->value > value)
		bstNode->childLeft = bstAVLRemove(bstNode->childLeft, value);
	else if (bstNode->value == value) {
		binaryTreeNode* aux = bstAVLInsert(bstNode->childLeft, bstNode->childRight);
		free(bstNode);
		bstNode = aux;
	}

	if (bstNode == NULL)
		return bstNode;

	bstNode->height = fmax(getHeight(bstNode->childLeft), getHeight(bstNode->childRight)) + 1;

	int balanceFactor = getBalanceFactor(bstNode);

	// Left Left Case
	if (balanceFactor > 1 && getBalanceFactor(bstNode->childLeft) >= 0)
		return rightRotate(bstNode);

	// Left Right Case
	if (balanceFactor > 1 && getBalanceFactor(bstNode->childLeft) < 0) {
		bstNode->childLeft = leftRotate(bstNode->childLeft);
		return rightRotate(bstNode);
	}

	// Right Right Case
	if (balanceFactor < -1 && getBalanceFactor(bstNode->childRight) <= 0)
		return leftRotate(bstNode);

	// Right Left Case
	if (balanceFactor < -1 && getBalanceFactor(bstNode->childRight) > 0) {
		bstNode->childRight = rightRotate(bstNode->childRight);
		return leftRotate(bstNode);
	}

	return bstNode;
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