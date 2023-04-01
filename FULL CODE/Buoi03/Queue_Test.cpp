//#include <stdio.h>
//#include <stdlib.h>
//
//struct Node
//{
//	int info;
//	Node* next;
//};
//struct Queue
//{
//	Node* head;
//	Node* tail;
//};
//void init(Queue &q)
//{
//	q.head = q.tail = NULL;
//}
//bool isEmpty(Queue q)
//{
//	return q.head == NULL;
//}
//Node* createNode(int value)
//{
//	Node* p = new Node;
//	if (p != NULL)
//	{
//		p->info = value;
//		p->next = NULL;
//	}
//	return p;
//}
//them du lieu vao queue
//enQueue (addTail)
//void addTail(Queue& q, int value)
//{
//	Node* p = createNode(value);
//	if (isEmpty(q))
//	{
//		q.head = q.tail = p;
//	}
//	else
//	{
//		q.tail->next = p;
//		q.tail = p;
//	}
//}
//
//lay du lieu tu queue
//deQueue (removeHead)
//void removeHead(Queue& q)
//{
//	if (isEmpty(q)) return;
//	else
//	{
//		Node* p = q.head;
//		q.head = p->next;
//
//		if (q.head == NULL)
//			q.tail = NULL;
//		delete p;
//	}
//}
//
//tra ve gia tri dau
//int getHead(Queue q)
//{
//	if (isEmpty(q))
//		return -1;
//	else
//		return q.head->info;
//}
//tra ve gia tri cuoi
//int getTail(Queue q)
//{
//	if (isEmpty(q))
//		return -1;
//	else
//		return q.tail->info;
//}
//
//void main()
//{
//	Queue q;
//	init(q);
//	int n = 5;
//	for (int i = 0; i < n; i++)
//	{
//		addTail(q, i);
//	}
//
//
//	int t;
//	while (!isEmpty(q))
//	{
//		t = getHead(q); removeHead(q);
//
//		xu ly
//		printf("%d\n", t);
//	}
//	
//	system("pause");
//}