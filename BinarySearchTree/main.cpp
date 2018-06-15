#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
	int year;
	char *title;
};

struct Node {
	Book data;
	Node * left;
	Node * right;
};

struct BinarySearchTree {
	Node * root;
};

Book createBook(int year, char * title)
{
	Book b;
	b.year = year;
	b.title = (char *)malloc(sizeof(char) * strlen(title) + 1);
	strcpy(b.title, title);
	return b;
}

// returns a pointer to Node that containss data about Book b
Node * createNode(Book b)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = b;
	newNode->left  = NULL;
	newNode->right = NULL;
	return newNode;
}

void printBook(Book b)
{
	printf("Year: %d\nTitle: %s\n", b.year, b.title);
}

BinarySearchTree addNode(BinarySearchTree tree, Node * node)
{
	if (tree.root == NULL)
	{
		tree.root = node;
	}
	else {
		/* 
			This is the tricky part. In a BST all nodes have lower keys on the lh side. We need to figure out where 
			to fit our new node. So what we do is we loop until we find an empty space to fit our data, choosing which
			direction to go during every iteration but also remembering the parent of the (possibly null) node. Once a 
			free space is found, we attach the node and break out of the infinite loop.
		*/
		Node * current = tree.root;
		Node * parent;
		while (true)
		{
			parent = current;
			if (node->data.year < current->data.year)
			{
				current = current->left;
				if (current == NULL)
				{
					parent->left = node;
					break;
				}
			}
			else {
				current = current->right;
				if (current == NULL)
				{
					parent->right = node;
					break;
				}
			}
		}
	}
	return tree;
}

// These have always confused the hell out of me, mostly because of the idiotic names.
// In order means that we traverse from lowest key to highest in ascending order
void inOrderPrintTree(Node * node)
{
	if (node != NULL)
	{
		inOrderPrintTree(node->left);
		printBook(node->data);
		inOrderPrintTree(node->right);
	}
}

// Post order means that we traverse the left subtree of each node first, then the right, and the also
// visit the node itself
void postOrderPrintTree(Node * node)
{
	if (node != NULL)
	{
		postOrderPrintTree(node->left);
		postOrderPrintTree(node->right);
		printBook(node->data);
	}
}

// Pre order means that we visit the node itself, then the left subtree, then the right subtree
void preOrderPrintTree(Node * node)
{
	if (node != NULL)
	{
		printBook(node->data);
		preOrderPrintTree(node->left);
		preOrderPrintTree(node->right);
	}
}

// Search for a key -- if we know we haven't found it, bubble up the error. If 
// we have found it, just return the relevant node and bubble it up. Else 
// recursively traverse the tree looking for the data on basis of the comparisons
Book search(Node * node, int year)
{
	if (node == NULL || node->data.year == -1)
	{
		return createBook(-1, "NOT_FOUND");
	}
	else if (node->data.year == year)
	{
		// Again, we might need to modify this so return a deep copy
		return createBook(node->data.year, node->data.title);
	}
	else if(year < node->data.year)
	{
		return search(node->left, year);
	}
	else {
		return search(node->right, year);
	}
}

int main()
{
	BinarySearchTree tree;
	tree.root = NULL;
	tree = addNode(tree, createNode(createBook(2004, "Asa grait-a Zarathustra")));
	tree = addNode(tree, createNode(createBook(2010, "O zi din viata lui Ivan Denisovici")));
	tree = addNode(tree, createNode(createBook(2005, "1984")));
	tree = addNode(tree, createNode(createBook(2001, "Fahrenheit 451")));
	tree = addNode(tree, createNode(createBook(1999, "Picnic la marginea drumului")));
	tree = addNode(tree, createNode(createBook(2018, "Biblia")));
	printf("\nIn order: \n\n");
	inOrderPrintTree(tree.root);
	printf("\nPre order: \n\n");
	preOrderPrintTree(tree.root);
	printf("\nPost order: \n\n");
	postOrderPrintTree(tree.root);
	Book biblia = search(tree.root, 2018);
	if (biblia.year > -1)
	{
		printf("\nBook was found: \n\n");
		printBook(biblia);
	}
	else {
		printf("\nBook was not found.\n");
	}
	return 0;
}