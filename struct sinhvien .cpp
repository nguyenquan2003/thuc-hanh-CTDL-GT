#include<conio.h>
#include<stdio.h>
#include<iostream>
using namespace std;
struct SV
{
	char MaSV[12];
	char HoLot[30];
	char Ten[8];
	int namsinh;
	float diem;
};
typedef SV item;
struct Node
{
	item info;
	Node* next;
};
struct List
{
	Node *head,*tail;
};
Node*CreateNode(item x)
{
	Node *p=new Node;
	if(p==NULL)
		return NULL;
	p->info=x;
	p->next=NULL;
	return p;
}
void initList(List &l)
{
	l.head=l.tail=NULL;
}
int len(List l)
{
	int dem=0;
	for(Node *p=l.head;p!=NULL;p=p->next)
		dem++;
	return dem;
}
int len_while(List l)
{
	int dem=0;
	Node *p=l.head;
	while(p!=NULL)
	{
		dem++;
		p=p->next;
		
	}
	return dem;
}
void Nhaplieu(item &x)
{
	printf("Nhap maSV:");
	fflush(stdin);
	gets(x.MaSV);
	printf("Nhap ho lot:");
	fflush(stdin);
	gets(x.HoLot);
	printf("Nhap ten:");
	fflush(stdin);
	gets(x.Ten);
	printf("Nhap nam sinh:");
	scanf("%d",&x.namsinh);
	printf("Nhap diem:");
	scanf("%f",&x.diem);
}
//thêm đầu
void insertHead(List &l,Node*p)
{
	if(p==NULL)
		return;
	if(l.head==NULL)//danh sach rong
		l.head=l.tail=p;
	else
	{
		p->next=l.head;
		l.head=p;
	}
}
void insertTail(List &l,Node*p)
{
	if(p==NULL)
		return;
	if(l.head==NULL)//danh sach rong
		l.head=l.tail=p;
	else
	{
		l.tail->next=p;
		l.tail=p;
	}
}
void ShowNode(Node *p)
{
	printf("%-14s",p->info.MaSV);
	printf("%-32s",p->info.HoLot);
	printf("%-10s",p->info.Ten);
	printf("%-6d",p->info.namsinh);
	printf("%-2.2f",p->info.diem);
}
void showList(List l)
{
	for(Node *p=l.head;p!=NULL;p=p->next)
	{
		ShowNode(p);
		printf("\n");
	}
}
void CreateList(List &l,int n)
{
	item x;
	initList(l);
	for(int i=0;i<n;i++)
	{
		printf("\nhap phan tu thu %d: ",i+1);
		Nhaplieu(x);
		insertTail(l,CreateNode(x));
	}
}
//tim theo ma sv
Node *Search(List l,char masv[])
{
	for(Node*p=l.head;p!=NULL;p=p->next)
		if(strcmp(p->info.MaSV,masv)==0)
			return p;
	return NULL;
}

void insertAfter (List &l, Node* q, Node* p)
{
	if(p==NULL || q==NULL)
		return;
	else
		if(l.head==NULL)// 
			l.head = l.tail = p;
		else
			if(q==l.tail)
				insertTail(l,p);
			else						
			{
				p->next = q->next;
				q->next = p;
			}
}

void delHead (List &l)
{
	if(l.head==NULL)
		return ;
	else
		{
			Node* p=l.head;
			l.head = p->next;
			p->next = NULL;
			delete p;
		}
}
void delTail (List &l)
{
	if(l.head==NULL)
		return;
	else
	{
		Node* p = l.tail;
		Node *q = l.head;
		while(q->next!=l.tail)
			q=q->next;
		l.tail = q;
		l.tail->next = NULL;
		delete p;
	}


}


void Menu()
{
}
void process()
{
	List l;
	int n,chon;
	item x;
	Node *p,*q;
	initList(l);
	do
	{
		Menu();
		printf("\nChon gia tri de tinh: ");
		scanf("%d",&chon);
		switch(chon)
		{
		case 1:
			Nhaplieu(x);
			p=CreateNode(x);
			insertHead(l,p);
			showList(l);
			break;
		case 2:
			Nhaplieu(x);
			insertTail(l,CreateNode(x));
			showList(l);
			break;
		case 3:
			printf("Nhap so phan tu cho danh sach:");
			scanf("%d",&n);
			CreateList(l,n);
			showList(l);
			break;
		/*case 4:
			printf("Nhap phan tu can tim:");
			scanf("%d",&x);
			p=Search(l,x);
			if(p)
				printf("\nTim thay");
			else
				printf("\nKhong Tim thay");
			break;
		case 5:
			printf("Nhap gia tri can them:");
			scanf("%d",&x);
			p=CreateNode(x);
			printf("Nhap gia tri nut q:");
			scanf("%d",&x);
			q=Search(l,x);
			insertAfter(l,q,p);
			showList(l);
			break;
		case 6:
			printf("Nhap gia tri can them:");
			scanf("%d",&x);
			p=CreateNode(x);
			printf("Nhap gia tri nut q:");
			scanf("%d",&x);
			q=Search(l,x);
			insertBefore(l,q,p);
			showList(l);
			break;
		case 7:
			printf("Nhap phan tu can tim:");
			scanf("%d",&x);
			n=Search_x(l,x);
			if(n>=0)
				printf("\nTim thay tai %d",n);
			else
				printf("\nKhong Tim thay");
			break;
		case 8:
			printf("Nhap gia tri phan tu can them:");
			scanf("%d",&x);
			p=CreateNode(x);
			printf("Nhap vi tri can them:");
			scanf("%d",&x);
			insertAt(l,p,x);
			showList(l);
			break;
		case 9:
			delHead(l);
			showList(l);
			break;
		case 10:
			delTail(l);
			showList(l);
			break;
		case 11:
			printf("Nhap gia tri node q:");
			scanf("%d",&x);
			q=Search(l,x);
			delAfter(l,q);
			showList(l);
			break;
		case 12:
			printf("Nhap gia tri node q:");
			scanf("%d",&x);
			q=Search(l,x);
			delBefore(l,q);
			showList(l);
			break;
		case 13:
			printf("Nhap vi tri can xoa:");
			scanf("%d",&x);
			del_At(l,x);
			showList(l);
			break;
		case 14:
			printf("Nhap gia tri can xoa:");
			scanf("%d",&x);
			del_All_x(l,x);
			showList(l);
			break;*/
		}
	}while(chon!=0);
}
int main()
{
	
	process();

}