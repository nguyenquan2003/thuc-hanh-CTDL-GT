#include <conio.h>
#include <stdio.h>

typedef int Itemtype;

struct StackNode
{
	Itemtype info;
	StackNode*next;
};

struct Stack
{

	StackNode*top;

};


StackNode*CreateStackNode(int x)
{

	StackNode*p = new StackNode;
	if (p == NULL)
	{
		printf("Khoong du bo nho!!!");
		getch();
		return NULL;

	}
	p->info=x;
	p->next = NULL;
	return p;

}

void TaoStackRong(Stack &s)
{

	s.top = NULL;

}

int KT_Rong(Stack &s)
{
	if (s.top == NULL)
		return 1;
	return 0;

}

void Push(Stack &s, StackNode*p)
{

	if (p == NULL)
		return;
	if (s.top == NULL)
	{
		s.top = p;
	}
	else
	{
		p->next = s.top;
		s.top = p;
	}
}


int Pop(Stack&s, int &x)
{

	if (KT_Rong(s) == 1)
		return 1;
	else {

			StackNode*p = s.top;
			s.top = s.top->next;
			x = p->info;
			delete p;
			
		}
}

void ChangeCoSo(int n, int a)
{

	int sodu, x, cn = n;
	Stack stack;
	TaoStackRong(stack);
	while (n!=0)
	{
		sodu = n%a;
		n /= a;
		StackNode*p = CreateStackNode(sodu);
		Push(stack, p);
	}
	printf("ket qua: %ld = ", cn);
	while (KT_Rong(stack)==0)
	{
		Pop(stack, x);
		printf("%3d", x);
	}
}


void main()
{
	int n,coso, x;
	do
	{
		printf("Nhap he co so 10: ");
		scanf("%d", &n);

	} while (n<=0);
	do
	{
		printf("Nhap co so muon doi: ");
		scanf("%d", &coso);

	} while (coso<=0);
	ChangeCoSo(n, coso);


	getch();
}