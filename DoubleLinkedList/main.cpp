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
	b.title = (char *)malloc(sizeof(char) * strlen(title) + 1);
	strcpy(b.title, title);
	return b;
}

void printBook(Book b)
{
	printf("Year: %d\nTitle: %s\n", b.year, b.title);
}

int main()
{
	return 0;
}