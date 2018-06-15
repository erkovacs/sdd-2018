#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
	int year;
	char *title;
};

struct Node {
	Book data;
	Node * next;
};

struct HashTable {
	int size;
	Node ** array;
};


int getHashCode(int key, int size)
{
	return key%size;
}


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
	newNode->next = NULL;
	return newNode;
}

HashTable initHashTable(int size)
{
	HashTable table;
	table.size = size;
	table.array = (Node **)malloc(size * sizeof(Node *));
	for (int i = 0; i < size; i++)
	{
		table.array[i] = NULL;
	}
	return table;
}

void printBook(Book b)
{
	printf("\nYear: %d\nTitle: %s\n", b.year, b.title);
}

void printHashTable(HashTable table)
{
	for (int i = 0; i < table.size; i++)
	{
		Node * current = table.array[i];
		printf("\n[%d]=>{", i);
		while (current != NULL)
		{
			printBook(current->data);
			current = current->next;
		}
		printf("}\n");
	}
}

Node * insertAtEnd(Node * head, Node * n)
{
	if (head != NULL)
	{
		Node * current = head;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = n;
	}
	else {
		head = n;
	}
	return head;
}

HashTable insertIntoHashTable(HashTable table, Book b)
{
	if (table.array != NULL)
	{
		Node * n = createNode(b);
		int hash = getHashCode(b.year, table.size);
		if (table.array[hash] != NULL)
		{
			table.array[hash] = insertAtEnd(table.array[hash], n);
		}
		else {
			table.array[hash] = n;
		}
	}
	return table;
}

Book getByKey(HashTable table, int key)
{
	int hash = getHashCode(key, table.size);
	Node * current = table.array[hash];
	while (current != NULL)
	{
		if (current->data.year == key)
		{
			return createBook(current->data.year, current->data.title);
		}
		current = current->next;
	}
	return createBook(-1, "NOT_FOUND");
}

int main()
{
	HashTable table = initHashTable(5);
	table = insertIntoHashTable(table, createBook(2004, "Asa grait-a Zarathustra"));
	table = insertIntoHashTable(table, createBook(2010, "O zi din viata lui Ivan Denisovici"));
	table = insertIntoHashTable(table, createBook(2005, "1984"));
	table = insertIntoHashTable(table, createBook(2001, "Fahrenheit 451"));
	table = insertIntoHashTable(table, createBook(1999, "Picnic la marginea drumului"));
	table = insertIntoHashTable(table, createBook(2018, "Biblia"));
	printHashTable(table);

	Book orwell = getByKey(table, 2005);
	if (orwell.year > -1)
	{
		printf("Book found:\n");
		printBook(orwell);
	}
	else {
		printf("Book not found.");
	}
	return 0;
}