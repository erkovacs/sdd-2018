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

struct AVLTree {
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

Node * createNode(Book b)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = b;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void printBook(Book b)
{
	printf("Year: %d\nTitle: %s\n", b.year, b.title);
}

int calculateHeight(Node * root) {
	if (root) {
		int left = calculateHeight(root->left);
		int right = calculateHeight(root->right);
		// get max 
		return (left > right ? left : right) + 1;
	}
	else {
		return 0;
	}
}

int balanceFactor(Node * root) {
	return calculateHeight(root->right) - calculateHeight(root->left);
}

Node * rotateToLeft(Node * root) {
	Node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	return temp;
}

Node * rotateToRight(Node * root) {
	Node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	return temp;
}

Node * insertInAVLTree(Node * root, Book book)
{
	if (root != NULL)
	{
		if (book.year < root->data.year)
		{
			root->left  = insertInAVLTree(root->left, book);
		}
		else {
			root->right = insertInAVLTree(root->right, book);
		}

		int bf = balanceFactor(root);
		if (bf == 2)
		{
			if (balanceFactor(root->right) == 1)
			{
				root = rotateToLeft(root);
			}
			else {
				root->right = rotateToRight(root->right);
				root = rotateToLeft(root);
			}
		}
		if (bf == -2)
		{
			if (balanceFactor(root->left) == -1)
			{
				root = rotateToRight(root);
			}
			else {
				root->left = rotateToLeft(root->left);
				root = rotateToRight(root);
			}
		}
	}
	else {
		root = createNode(book);
	}
	return root;
}

void inOrderPrintTree(Node * root)
{
	if (root != NULL)
	{
		inOrderPrintTree(root->left);
		printBook(root->data);
		inOrderPrintTree(root->right);
	}
}

Book * getBooksAtLevel(Node * root, int level)
{
	if (root != NULL) {
		if (level == 1) {
			printBook(root->data);
		}
		else {
			printByLevel(root->left, level - 1);
			printByLevel(root->right, level - 1);
		}
	}
}

void printByLevel(Node * root, int level) {
	if (root != NULL) {
		if (level == 1) {
			printBook(root->data);
		}
		else {
			printByLevel(root->left, level - 1);
			printByLevel(root->right, level - 1);
		}
	}
}


int main()
{
	Book b = createBook(2011, "Fratii Karamazov");
	AVLTree tree;
	tree.root = NULL;
	tree.root = insertInAVLTree(tree.root, b);
	tree.root = insertInAVLTree(tree.root, createBook(2004, "Asa grait-a Zarathustra"));
	tree.root = insertInAVLTree(tree.root, createBook(2010, "O zi din viata lui Ivan Denisovici"));
	tree.root = insertInAVLTree(tree.root, createBook(2005, "1984"));
	tree.root = insertInAVLTree(tree.root, createBook(2001, "Fahrenheit 451"));
	tree.root = insertInAVLTree(tree.root, createBook(1999, "Picnic la marginea drumului"));
	tree.root = insertInAVLTree(tree.root, createBook(2018, "Biblia"));
	inOrderPrintTree(tree.root);

	int treeHeight = calculateHeight(tree.root);
	printf("\nHeight: %d\n", treeHeight);
	printf("\Balance factor: %d\n", balanceFactor(tree.root));
	for (int i = 1; i <= treeHeight; i++)
	{
		printf("\nLevel: %d\n", i);
		printByLevel(tree.root, i);
	}

	return 0;
}