#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Factura {
	int numar;
	char * data;
	char * client;
	float valoare;
	int nrProduse;
};

struct Node {
	Factura data;
	Node * left;
	Node * right;
};

struct AVLTree {
	Node * root;
};


Factura createFactura(int numar, char * data, char * client, float valoare, int nrProduse)
{
	Factura f;
	f.numar = numar;
	f.data = (char *)malloc(strlen(data)+1);
	strcpy(f.data, data);
	f.client = (char *)malloc(strlen(client) + 1);
	strcpy(f.client, client);
	f.valoare = valoare;
	f.nrProduse = nrProduse;
	return f;
}

Node * createNode(Factura f)
{
	Node * node = (Node *)malloc(sizeof(Node));
	node->data = f;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void printFactura(Factura f)
{
	printf("\nFactura nr.: %d; Data: %s; Client: %s; Valoare: %.2f; Numar produse: %d;\n", f.numar, f.data, f.client, f.valoare, f.nrProduse);
}

int getHeight(Node * root)
{
	if (root != NULL)
	{
		int left  = getHeight(root->left);
		int right = getHeight(root->right);
		return (left > right ? left : right) + 1;
	}
	else {
		return 0;
	}
}

int getBalanceFactor(Node * root)
{
	return getHeight(root->right) - getHeight(root->left);
}

void printAVLTree(Node * root)
{
	if (root != NULL)
	{
		printAVLTree(root->left);
		printFactura(root->data);
		printAVLTree(root->right);
	}
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

Node * insertAVLTree(Node * root, Factura f)
{
	if (root != NULL)
	{
		if (f.numar < root->data.numar)
		{
			root->left = insertAVLTree(root->left, f);
		}
		else {
			root->right = insertAVLTree(root->right, f);
		}

		int bf = getBalanceFactor(root);
		if (bf == 2)
		{
			if(getBalanceFactor(root->right) == 1)
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
			if (getBalanceFactor(root->right) == -1)
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
		root = createNode(f);
	}
	return root;
}

void printAVLTreeByLevel(Node * root, int level)
{
	if (root != NULL) {
		if (level == 1)
		{
			printFactura(root->data);
		}
		else {
			printAVLTreeByLevel(root->left, level - 1);
			printAVLTreeByLevel(root->right, level - 1);
		}
	}
}

int parseDate(char * date)
{
	char buffer[100];
	int parts[3];
	strcpy(buffer, date);
	char * pch;
	pch = strtok(buffer, ".");
	int i = 0;
	while (pch != NULL)
	{
		parts[i] = atoi(pch);
		pch = strtok(NULL, ".");
		i++;
	}
	int timestamp = 0;
	// convert to minutes -- !!!VERY!!! approximate
	timestamp += (parts[0] * 1440) + (parts[1] * 1440 * 30) + (parts[2] * 1440 * 365);
	return timestamp;
}

float getSumFacturiAfterDate(Node * root, char * date)
{
	float retval = 0;
	if (root != NULL)
	{
		if (parseDate(root->data.data) > parseDate(date))
		{
			retval += root->data.valoare;
		}
		retval += getSumFacturiAfterDate(root->left, date);
		retval += getSumFacturiAfterDate(root->right, date);
	}
	return retval;
}

int getFacturiClient(Node * root, char * client)
{
	int retval = 0;
	if (root != NULL)
	{
		if (strcmp(root->data.client, client) == 0)
		{
			retval++;
		}
		retval += getFacturiClient(root->left, client);
		retval += getFacturiClient(root->right, client);
	}
	return retval;
}

void addCommission(Node * root, float commission)
{
	if (root != NULL)
	{
		addCommission(root->left, commission);
		root->data.valoare += commission;
		addCommission(root->right, commission);
	}
}

int main()
{
	Factura f = createFactura(1, "1.1.1999", "Ionescu SRL", 10000, 3);
	printFactura(f);

	AVLTree tree;
	tree.root = NULL;
	tree.root = insertAVLTree(tree.root, f);
	tree.root = insertAVLTree(tree.root, createFactura(2, "9.1.1999", "Ionescu SRL", 12000, 10));
	tree.root = insertAVLTree(tree.root, createFactura(3, "10.2.2000", "Popescu SRL", 1500, 2));
	tree.root = insertAVLTree(tree.root, createFactura(4, "22.3.2002", "Grigore SRL", 1550, 4));
	tree.root = insertAVLTree(tree.root, createFactura(5, "16.4.2010", "Vasile SRL", 200000, 31));
	tree.root = insertAVLTree(tree.root, createFactura(6, "15.5.2001", "Toma SRL", 7200, 6));
	tree.root = insertAVLTree(tree.root, createFactura(7, "12.6.2011", "Barbu SRL", 150, 2));
	tree.root = insertAVLTree(tree.root, createFactura(8, "21.7.1998", "Mircea SRL", 12000, 3));
	printAVLTree(tree.root);

	int height = getHeight(tree.root);
	printf("%d", height);
	for (int i = 1; i <= height; i++)
	{
		printf("\nLevel %d\n", i);
		printAVLTreeByLevel(tree.root, i);
	}

	char * client = "Barbu SRL";
	printf("Clientul %s are %d facturi.\n", client, getFacturiClient(tree.root, client));

	addCommission(tree.root, 2.50);
	printf("\nComision de 2.50 um adaugat:\n");
	printAVLTree(tree.root);

	char * date = "22.3.2002";
	printf("\nSuma facturilor de dupa data de %s este: %.2f\n", date, getSumFacturiAfterDate(tree.root, date));
	return 0;
}