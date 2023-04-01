#include "MyLinkedList.h"
#include <stdio.h>
void initList(Node*& head)
{
	head = NULL;
}
bool isEmptyList(Node* head)
{
	return head == NULL;
}

Node* createNode(int key, int value)
{
	Node* p = new Node;
	p->key = key;
	p->value = value;
	p->next = NULL;
	return p;
}
void addHead(Node*& head, int key, int value)
{
	Node* p = createNode(key, value);
	if (isEmptyList(head))
	{
		head = p;
	}
	else
	{
		p->next = head;
		head = p;
	}
}
void removeHead(Node*& head)
{
	if (!isEmptyList(head))
	{
		Node* tmp = head;
		head = tmp->next;
		delete tmp;
	}
}
void removeAfter(Node*& q)
{
	if (q != NULL)
	{
		Node* p = q->next;
		q->next = p->next;
		delete p;
	}
}
void removeAllList(Node*& head)
{
	while (!isEmptyList(head))
	{
		removeHead(head);
	}
}

void removeNodeList(Node*& head, int key)
{
	if (isEmptyList(head)) return;
	else
	{
		Node* p = head;
		Node* q = NULL;// q la node truoc p
		while (p != NULL && p->key != key)
		{
			q = p;
			p = p->next;
		}
		if (p == NULL)
		{
			printf("Khong ton tai khoa %d!\n", key);
			return;
		}	
		else //p->key == key
		{
			if (q == NULL) //p == head
				removeHead(head);
			else
				removeAfter(q);
		}
	}
}

Node* searchList(Node* head, int key)
{
	for (Node* p = head; p != NULL; p = p->next)
	{
		if (p->key == key)
			return p;
	}
	return NULL;
}

void traverseList(Node* head)
{
	for (Node* p = head; p != NULL; p = p->next)
	{
		printf("%d \n", p->key);
		//printNode(p);
	}
	//printf("\n");
}
