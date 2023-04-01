#include <stdio.h>
#include <conio.h>
#include <stack>
using namespace std;

struct StackNode
{
	int info;
	StackNode *next;
};
struct Stack
{
	StackNode *top;
};

void initStack(Stack &st)
{
	st.top = NULL;
}

StackNode *createStackNode(int x)
{
	StackNode *p = new StackNode;
	if (p == NULL)
	{
		printf("\nKhong du bo nho.\n");
		getch();
		return NULL;
	}
	p->info = x;
	p->next = NULL;
	return p;
}

int isEmpty(Stack st)
{
	if (st.top == NULL)
		return 1;
	return 0;
}

int push(Stack &st, StackNode *p)
{
	if (p == NULL) return 0;
	if (isEmpty(st) == 1)
	{
		st.top = p;
		return 1;
	}
	p->next = st.top;
	st.top = p;
	return 1;
}

int pop(Stack &st, int &x)
{
	if (isEmpty(st) == 1)
		return 0;
	StackNode *p = st.top;
	st.top = st.top->next;
	x = p->info;
	delete p;
	return 1;
}
int tinhGT2(int n)
{
	int kq = 1;
	for (int i = 2; i <= n; i++)
	{
		kq *= i;
	}
	return kq;
}
int tinhGT(int n)
{
	if (n <= 1) 
		return 1;
	else
		return n * tinhGT(n-1);
}

int tinhGiaiThua(int n)
{
	stack<int> st;

	for (int i = n; i > 0; i--)
	{
		st.push(i);
	}

	int giaithua = 1, i;
	while (!st.empty())
	{
		int t = st.top(); st.pop();
		giaithua *= t;
	}
	return giaithua;
}

void main()
{

	int n;
	printf("Nhap vao so de tinh giai thua: ");
	scanf("%d", &n);
	int kq = tinhGiaiThua(n);
	if (kq == 0)
		printf("\n\tKhong co giai thua cua %d", n);
	else printf("\n\t%d! = %d", n, kq);
	getch();
}