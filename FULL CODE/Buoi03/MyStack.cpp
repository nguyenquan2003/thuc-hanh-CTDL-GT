#include "MyStack.h"
#include <stdio.h>

//khoi tao stack
void init(Stack &s)
{
	s.top = NULL;
}
//kiem tra stack rong
bool isEmpty(Stack s)
{
	return s.top == NULL;
}
//cap phat vung nho
Node* createNode(int value)
{
	Node* p = new Node;
	if (p != NULL)
	{
		p->info = value;
		p->next = NULL;
	}
	return p;
}
//them du lieu vao Stack (add head)
void push(Stack& s, int value)
{
	Node* p = createNode(value);
	if (isEmpty(s))
	{
		s.top = p;
	}
	else
	{
		p->next = s.top;
		s.top = p;
	}
}

//lay du lieu tu Stack (removeHead)
void pop(Stack& s)
{
	if (isEmpty(s)) return;
	else
	{
		Node* p = s.top;
		s.top = p->next;
		delete p;
	}
}

//tra ve gia tri tren dinh stack (top/peek)
int getTop(Stack s)
{
	if (isEmpty(s))
		return -1;
	else
		return s.top->info;
}
