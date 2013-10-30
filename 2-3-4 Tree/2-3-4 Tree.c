#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
	
	struct _node *left;
	struct _node *middle;
	struct _node *right;
}node;

node HEAD;

node *newNode()
{
	node *aNode;
	aNode = malloc(sizeof(node));
	aNode->left = NULL;
	aNode->middle = NULL;
	aNode->right = NULL;
}

void insert()
{

}

void remove()
{

}

int main()
{
	HEAD = newNode();
	return 0;
}