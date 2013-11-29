#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<conio.h>

#include<queue>

using namespace std;


#define TREEKEYTYPE unsigned int

enum NODEN
{
	NODE0,
	NODE1,
	NODE2,
	NODE3,
	NODE4 // 이것은 위로 올려져야 한다.
};

typedef struct _node{
	
	struct _node *left;
	struct _node *middleleft;
	struct _node *middleright;
	struct _node *right;
	struct _node *tempnode;
	struct _node *parent;
	TREEKEYTYPE key1;
	TREEKEYTYPE key2;
	TREEKEYTYPE key3;
	TREEKEYTYPE temp;
	char nodetype;
}node;

/*
typedef struct _tree{
}TREE;
*/

node* HEAD;
int height;


node *newNode()
{
	node *aNode;
	aNode = (node *)malloc(sizeof(node));
	aNode->left = NULL;
	aNode->middleleft = NULL;
	aNode->middleright = NULL;
	aNode->right = NULL;
	aNode->tempnode = NULL;
	aNode->parent = NULL;
	aNode->nodetype = NODE0;
	return aNode;
}

char insert(node *currentNode, TREEKEYTYPE k)
{
	// 2. 몇개가 있냐에 따라 집어 넣는다.
	if (currentNode->nodetype == NODE0){
		currentNode->key1 = k;
		currentNode->nodetype = NODE1;
		return 1;
	}
	if (currentNode->nodetype == NODE1){
		if (currentNode->key1 < k){
			currentNode->key2 = k;
			currentNode->nodetype = NODE2;
			return 2;
		}
		else{
			currentNode->key2 = currentNode->key1;
			currentNode->key1 = k;
			currentNode->nodetype = NODE2;
			return 1;
		}
	}
	if (currentNode->nodetype == NODE2){
		if (currentNode->key1 < k&&currentNode->key2 < k){
			currentNode->key3 = k;
			currentNode->nodetype = NODE3;
			return 3;
		}
		else if (currentNode->key1 < k&&currentNode->key2 > k){
			currentNode->key3 = currentNode->key2;
			currentNode->key2 = k;
			currentNode->nodetype = NODE3;
			return 2;
		}
		else{
			currentNode->key3 = currentNode->key2;
			currentNode->key2 = currentNode->key1;
			currentNode->key1 = k;
			currentNode->nodetype = NODE3;
			return 1;
		}
	}
	if (currentNode->nodetype == NODE3){
		if (currentNode->key1 < k&&currentNode->key2 < k&&currentNode->key3 < k){
			currentNode->temp = k;
			currentNode->nodetype = NODE4;
			return 4;
		}
		else if (currentNode->key1 < k&&currentNode->key3 > k&&currentNode->key2 < k){
			currentNode->temp = currentNode->key3;
			currentNode->key3 = k;
			currentNode->nodetype = NODE4;
			return 3;
		}
		else if (currentNode->key1 < k&&currentNode->key2 > k&&currentNode->key3 > k){
			currentNode->temp = currentNode->key3;
			currentNode->key3 = currentNode->key2;
			currentNode->key2 = k;
			currentNode->nodetype = NODE4;
			return 2;
		}
		else{
			currentNode->temp = currentNode->key3;
			currentNode->key3 = currentNode->key2;
			currentNode->key2 = currentNode->key1;
			currentNode->key1 = k;
			currentNode->nodetype = NODE4;
			return 1;
		}
	}
	return 0;
}

void split(node *currentNode)
{
	char t;
	node *newHEADNode, *aNewNode;
	// 아... 올려야 되는구나.
	while (currentNode->nodetype == NODE4){
		if (currentNode != HEAD){
			// 올리고 분할
			newHEADNode = currentNode->parent;
			aNewNode = newNode();

			t=insert(newHEADNode, currentNode->key3);
			if (t == 1){
				newHEADNode->middleright = newHEADNode->middleleft;
				newHEADNode->left = currentNode;
				newHEADNode->middleleft = aNewNode;
			}
			else if (t == 2){
				newHEADNode->middleleft = currentNode;
				newHEADNode->right = newHEADNode->middleright;
				newHEADNode->middleright = aNewNode;
			}
			else if (t == 3){
				newHEADNode->middleright = currentNode;
				newHEADNode->tempnode = newHEADNode->right;
				newHEADNode->right = aNewNode;
			}
			else if (t == 4){
				newHEADNode->right = currentNode;
				newHEADNode->tempnode = aNewNode;
			}
			currentNode->nodetype = NODE2;

			aNewNode->parent = newHEADNode;
			aNewNode->key1 = currentNode->temp;
			aNewNode->nodetype = NODE1;
			aNewNode->left = currentNode->middleright;
			aNewNode->middleleft = currentNode->tempnode;
			currentNode = currentNode->parent;
		}
		else{
			newHEADNode = newNode();
			aNewNode = newNode();

			newHEADNode->key1 = currentNode->key3;
			newHEADNode->left = currentNode;
			newHEADNode->middleleft = aNewNode;
			newHEADNode->nodetype = NODE1;

			currentNode->parent = newHEADNode;
			currentNode->nodetype = NODE2;

			aNewNode->parent = newHEADNode;
			aNewNode->key1 = currentNode->temp;
			aNewNode->nodetype = NODE1;
			if (currentNode->right){
				aNewNode->left = currentNode->right;
				aNewNode->left->parent = aNewNode;
			}
			if (currentNode->tempnode){
				aNewNode->middleleft = currentNode->tempnode;
				aNewNode->middleleft->parent = aNewNode;
			}
			HEAD = newHEADNode;
			height++;
			break;
		}
	}
}

void push(TREEKEYTYPE k)
{
	// 1. k가 들어갈 자리를 찾아 본다.
	node *currentNode=HEAD;
	
	int currentHeight=0;
	while (currentHeight < height){
		if (currentNode->nodetype == NODE0){
			// 이것은 에러인데
		}
		else if (currentNode->nodetype == NODE1){
			if (currentNode->key1>k){
				currentNode = currentNode->left;
			}
			else{
				currentNode = currentNode->middleleft;
			}
			currentHeight++;
		}
		else if (currentNode->nodetype == NODE2){
			if (currentNode->key1 > k){
				currentNode = currentNode->left;
			}
			else if (currentNode->key2 > k){
				currentNode = currentNode->middleleft;
			}
			else{
				currentNode = currentNode->middleright;
			}
			currentHeight++;
		}
		else if (currentNode->nodetype == NODE3){
			if (currentNode->key1 > k){
				currentNode = currentNode->left;
			}
			else if (currentNode->key2 > k){
				currentNode = currentNode->middleleft;
			}
			else if (currentNode->key3 > k){
				currentNode = currentNode->middleright;
			}
			else{
				currentNode = currentNode->right;
			}
			currentHeight++;
		}
	}

	insert(currentNode, k);

	split(currentNode);
}

node *rightest_child(node *currentNode)
{
	if (currentNode->nodetype == NODE0){
		//이건 에러인데
		return currentNode->left;
	}
	if (currentNode->nodetype == NODE1){
		return currentNode->middleleft;
	}
	if (currentNode->nodetype == NODE2){
		return currentNode->middleright;
	}
	if (currentNode->nodetype == NODE3){
		return currentNode->right;
	}
	if (currentNode->nodetype == NODE4){
		return currentNode->tempnode;
	}
}

node *second_rightest_child(node *currentNode)
{
	if (currentNode->nodetype == NODE0){
		//이건 에러인데
		return currentNode->left;
	}
	if (currentNode->nodetype == NODE1){
		return currentNode->left;
	}
	if (currentNode->nodetype == NODE2){
		return currentNode->middleleft;
	}
	if (currentNode->nodetype == NODE3){
		return currentNode->middleright;
	}
	if (currentNode->nodetype == NODE4){
		return currentNode->right;
	}
}

TREEKEYTYPE rightest_key(node *currentNode)
{
	if (currentNode->nodetype == NODE0){
		//이건 에러인데
		return currentNode->key1;
	}
	if (currentNode->nodetype == NODE1){
		return currentNode->key1;
	}
	if (currentNode->nodetype == NODE2){
		return currentNode->key2;
	}
	if (currentNode->nodetype == NODE3){
		return currentNode->key3;
	}
	if (currentNode->nodetype == NODE4){
		return currentNode->temp;
	}
}

void remove(node *currentNode,TREEKEYTYPE k)
{
	node *tn;
	if (currentNode->nodetype == NODE0){
		insert(currentNode->parent->left, currentNode->parent->key1);
		HEAD = currentNode->parent->left;
		HEAD->middleright = currentNode->left;
		currentNode->left->parent = HEAD;
		free(currentNode);
	}
	else if (currentNode->nodetype == NODE1){
		if (currentNode == HEAD){
			tn = HEAD->left;
			while (rightest_child(tn) != NULL){ 
				tn = rightest_child(tn); 
			}
			currentNode->key1 = rightest_key(tn);
			remove(tn, rightest_key(tn));
		}
		else{
			//빌려와야됭
			if (currentNode == currentNode->parent->left){
				currentNode->key1 = currentNode->parent->key1;
				if (currentNode->parent->middleleft->nodetype > 1){
					currentNode->parent->key1 = currentNode->parent->middleleft->key1;
					remove(currentNode->parent->middleleft, currentNode->parent->middleleft->key1);
				}
				else{
					currentNode->nodetype--;
					insert(currentNode, currentNode->parent->key1);
					insert(currentNode, currentNode->parent->middleleft->key1);
					free(currentNode->parent->middleleft);
					currentNode->parent->nodetype--;
					remove(currentNode->parent, currentNode->parent->key1);
				}
			}
			else{
				insert(second_rightest_child(currentNode->parent), rightest_key(currentNode->parent));
				remove(currentNode->parent, rightest_key(currentNode->parent));
//				currentNode->parent->nodetype--;
				free(currentNode);
			}
		}
	}
	else if (currentNode->nodetype == NODE2){
		//if (currentHeight == height){
		// 대충하면 됨
		if (currentNode->key1 == k){
			currentNode->key1 = currentNode->key2;
		}
		currentNode->nodetype--;
	}
	else if (currentNode->nodetype == NODE3){
		if (currentNode->key1 == k){
			currentNode->key1 = currentNode->key2;
			currentNode->key2 = currentNode->key3;
		}
		else if (currentNode->key2 == k){
			currentNode->key2 = currentNode->key3;
		}
		currentNode->nodetype--;
		return;	
	}
}

void pop(TREEKEYTYPE k)
{
	node *currentNode = HEAD;
	int currentHeight = 0;
	while (currentHeight <= height){
		if (currentNode->nodetype == NODE0){
			// 이것은 에러인데
		}
		else if (currentNode->nodetype == NODE1){
			if (currentNode->key1 == k){
				remove(currentNode, k);
			}
			if (currentNode->key1>k){
				currentNode = currentNode->left;
			}
			else{
				currentNode = currentNode->middleleft;
			}
			currentHeight++;
		}
		else if (currentNode->nodetype == NODE2){
			if (currentNode->key1 == k || currentNode->key2 == k){
				remove(currentNode, k);
			}
			if (currentNode->key1 > k){
				currentNode = currentNode->left;
			}
			else if (currentNode->key2 > k){
				currentNode = currentNode->middleleft;
			}
			else{
				currentNode = currentNode->middleright;
			}
			currentHeight++;
		}
		else if (currentNode->nodetype == NODE3){
			if (currentNode->key1 == k || currentNode->key2 == k || currentNode->key3 == k){
				remove(currentNode, k);
			}
			if (currentNode->key1 > k){
				currentNode = currentNode->left;
			}
			else if (currentNode->key2 > k){
				currentNode = currentNode->middleleft;
			}
			else if (currentNode->key3 > k){
				currentNode = currentNode->middleright;
			}
			else{
				currentNode = currentNode->right;
			}
			currentHeight++;
		}
	}
}

void initialize()
{
	HEAD = newNode();
}

void printNode(node *aNode)
{
	if (aNode == NULL)
		return;
	if (aNode->nodetype == NODE0){
		printf("");
	}
	else if (aNode->nodetype == NODE1){
		printf("(%d) ",aNode->key1);
	}
	else if (aNode->nodetype == NODE2){
		printf("(%d %d) ", aNode->key1, aNode->key2);
	}
	else if (aNode->nodetype == NODE3){
		printf("(%d %d %d) ", aNode->key1, aNode->key2, aNode->key3);
	}
	else if (aNode->nodetype == NODE4){
		printf("(%d %d %d %d) ", aNode->key1, aNode->key2, aNode->key3, aNode->temp);
	}
}


int levelOfNode(node *anode)
{
	int c = 0;
	while (anode != HEAD){
		c++;
		anode = anode->parent;
	}
	return c;
}


void printTree()
{
	int t=0;
	queue<node *> printq;
	printq.push(HEAD);
	while (printq.size() != 0){
		if (NODE1 == printq.front()->nodetype){
			if (printq.front()->left!=NULL)
				printq.push(printq.front()->left);
			if (printq.front()->middleleft != NULL)
				printq.push(printq.front()->middleleft);
		}
		if (NODE2 == printq.front()->nodetype){
			if (printq.front()->left != NULL)
				printq.push(printq.front()->left);
			if (printq.front()->middleleft != NULL)
				printq.push(printq.front()->middleleft);
			if (printq.front()->middleright != NULL)
				printq.push(printq.front()->middleright);
		}
		if (NODE3 == printq.front()->nodetype){
			if (printq.front()->left != NULL)
				printq.push(printq.front()->left);
			if (printq.front()->middleleft != NULL)
				printq.push(printq.front()->middleleft);
			if (printq.front()->middleright != NULL)
				printq.push(printq.front()->middleright);
			if (printq.front()->right != NULL)
				printq.push(printq.front()->right);
		}
		if (NODE4 == printq.front()->nodetype){
			if (printq.front()->left != NULL)
				printq.push(printq.front()->left);
			if (printq.front()->middleleft != NULL)
				printq.push(printq.front()->middleleft);
			if (printq.front()->middleright != NULL)
				printq.push(printq.front()->middleright);
			if (printq.front()->right != NULL)
				printq.push(printq.front()->right);
			if (printq.front()->tempnode != NULL)
				printq.push(printq.front()->tempnode);
		}
		printNode(printq.front());
		printq.pop();
		if (printq.size() != 0 && levelOfNode(printq.front()) != t){
			printf("\n");
			t = levelOfNode(printq.front());
		}
	}
	printf("\n\n");
}

void search(TREEKEYTYPE k)
{
	node *currentNode = HEAD;
	int currentHeight = 0;
	while (currentHeight <= height){
		if (currentNode->nodetype == NODE0){
			// 이것은 에러인데
		}
		else if (currentNode->nodetype == NODE1){
			if (currentNode->key1 == k){
				printf("exist\n");
				return;
			}
			if (currentNode->key1 > k){
				currentNode = currentNode->left;
			}
			else{
				currentNode = currentNode->middleleft;
			}
			currentHeight++;
		}
		else if (currentNode->nodetype == NODE2){
			if (currentNode->key1 == k || currentNode->key2 == k){
				printf("exist\n");
				return;
			}
			if (currentNode->key1 > k){
				currentNode = currentNode->left;
			}
			else if (currentNode->key2 > k){
				currentNode = currentNode->middleleft;
			}
			else{
				currentNode = currentNode->middleright;
			}
			currentHeight++;
		}
		else if (currentNode->nodetype == NODE3){
			if (currentNode->key1 == k || currentNode->key2 == k || currentNode->key3 == k){
				printf("exist\n");
				return;
			}
			if (currentNode->key1 > k){
				currentNode = currentNode->left;
			}
			else if (currentNode->key2 > k){
				currentNode = currentNode->middleleft;
			}
			else if (currentNode->key3 > k){
				currentNode = currentNode->middleright;
			}
			else{
				currentNode = currentNode->right;
			}
			currentHeight++;
		}
	}

	printf("no exist\n");
}

int main(int argc, char *argv[])
{
	char c;
	TREEKEYTYPE ui;
	initialize();

	if (argc < 2){
		push(4);
		push(6);
		push(12);
		push(15);
		printTree();

		push(3);
		push(5);
		printTree();

		push(10);
		push(8);
		printTree();

		push(11);
		push(13);
		push(14);
		printTree();

		push(17);
		printTree();

		pop(3);
		pop(4);
		printTree();

		pop(12);
		printTree();

		pop(13);
		printTree();

		pop(14);
		printTree();
		
	}
	else{
		freopen(argv[1], "r", stdin);
		freopen("output.txt", "w", stdout);
	}
	while (1){
		c = _getch();
		printf("%c",c);
		//scanf("%c",&c);
		if (c == EOF)
			break;
		scanf("%ud",&ui);
		if (c == 'i'){
			push(ui);
		}
		if (c == 'd'){
			pop(ui);
		}
		if (c == 's'){
			search(ui);
		}
		if (c != 's')
			printTree();
	}
	return 0;
}