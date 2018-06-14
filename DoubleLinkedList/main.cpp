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
	Node * prev;
};

/*
*	Now this can be done two ways - either you expose both head and tail, or you expose just the head
*	and then all you have over a simple linked list is that you can traverse backwards once you get 
*   to the tail. The better way is this, but it's more complicated
*
*/
struct LinkedList {
	Node * head;
	Node * tail;
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
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

LinkedList addAtHead(LinkedList list, Node * n)
{
	if (list.head == NULL)
	{
		list.tail = n;
	}
	else {
		n->next = list.head;
		n->prev = NULL;
		list.head->prev = n;
	}
	list.head = n;
	return list;
}

LinkedList addAtTail(LinkedList list, Node * n)
{
	if (list.tail == NULL)
	{
		list.head = n;
	}
	else {
		n->prev = list.tail;
		n->next = NULL;
		list.tail->next = n;
	}
	list.tail = n;
	return list;
}


void printBook(Book b)
{
	printf("Year: %d\nTitle: %s\n", b.year, b.title);
}


void printList(LinkedList list)
{
	Node * current = list.head;
	while (current != NULL)
	{
		printBook(current->data);
		current = current->next;
	}
	current = list.tail;
	while (current != NULL)
	{
		printBook(current->data);
		current = current->prev;
	}
}

Book extractBook(LinkedList list, int year)
{
	Node * current = list.head;
	while (current != NULL)
	{
		if (current->data.year == year)
		{
			// return a deep copy because we might need to modify this
			return createBook(current->data.year, current->data.title);
		}
		current = current->next;
	}
	return createBook(-1, "NOT_FOUND");
}

int main()
{
	LinkedList list;
	list.head = list.tail = NULL;
	list = addAtHead(list, createNode(createBook(2011, "Fratii Karamazov")));
	list = addAtHead(list, createNode(createBook(2004, "Asa grait-a Zarathustra")));
	list = addAtHead(list, createNode(createBook(2010, "O zi din viata lui Ivan Denisovici")));
	list = addAtHead(list, createNode(createBook(2005, "1984")));
	list = addAtTail(list, createNode(createBook(2009, "Picnic la marginea drumului")));
	printList(list);
	Book karamazov = extractBook(list, 2011);
	if (karamazov.year > -1)
	{
		printf("Book found:\n");
		printBook(karamazov);
	}
	else {
		printf("Book was not found in list.");
	}
	return 0;
}