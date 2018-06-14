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

struct LinkedList {
	Node * head;
};

Book createBook(int year, char * title)
{
	Book b;
	b.year = year;
	b.title = (char *)malloc(sizeof(char) * strlen(title)+1);
	strcpy(b.title, title);
	return b;
}

// returns a pointer to Node that containss data about Book b
Node * createNode(Book b)
{
	Node * newNode  = (Node*)malloc(sizeof(Node));
	newNode->data = b;
	newNode->next = NULL;
	return newNode;
}

void printBook(Book b)
{
	printf("Year: %d\nTitle: %s\n", b.year, b.title);
}

Node * traverseList(LinkedList list)
{
	Node *current = list.head;
	Node *prev;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}
	return prev;
}

LinkedList addNodeAtHead(LinkedList list, Node *n)
{
	if (list.head == NULL)
	{
		list.head = n;
	}
	else {
		Node * temp = list.head;
		list.head = n;
		list.head->next = temp;
	}

	return list;
}

LinkedList addNodeAtEnd(LinkedList list, Node *n)
{
	if (list.head == NULL)
	{
		list.head = n;
	}
	else {
		Node * current = traverseList(list);
		current->next = n;
	}

	return list;
}

LinkedList addNodeSorted(LinkedList list, Node *n)
{
	if (list.head == NULL)
	{
		list.head = n;
	}
	else {
		if (n->data.year < list.head->data.year)
		{
			list = addNodeAtHead(list, n);
		}
		else {
			// This is the tricky part. You have to traverse the list till you get a next element
			// with a publication year higher than your current or you get to the tail of the list
			Node * current = list.head;
			while (current->next != NULL && current->next->data.year < n->data.year)
			{
				current = current->next;
			}
			// if you are at the tail, attach a new node
			if (current->next == NULL)
			{
				current->next = n;
			}
			// if not, insert a node between the last node with year less or equal to yours and repair the list
			else {
				Node * temp = current->next;
				current->next = n;
				current->next->next = temp;
			}
		}
	}
	return list;
}

void printList(LinkedList list)
{
	Node *current = list.head;
	while (current != NULL)
	{
		printBook(current->data);
		current = current->next;
	}
}

int main()
{
	Book b = createBook(2011, "Fratii Karamazov");
	LinkedList list;
	list.head = NULL;
	list = addNodeAtHead(list, createNode(b));
	list = addNodeAtHead(list, createNode(createBook(2004, "Asa grait-a Zarathustra")));
	list = addNodeAtHead(list, createNode(createBook(2010, "O zi din viata lui Ivan Denisovici")));
	list = addNodeAtHead(list, createNode(createBook(2005, "1984")));
	list = addNodeSorted(list, createNode(createBook(2001, "Fahrenheit 451")));
	list = addNodeSorted(list, createNode(createBook(1999, "Picnic la marginea drumului")));
	list = addNodeSorted(list, createNode(createBook(2018, "Biblia")));
	printList(list);
}