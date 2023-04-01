#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int ItemType;

struct SNode
{
	ItemType info;
	SNode* next;

};

struct SList
{

	SNode* head;
	SNode* tail;

};

SNode* CreateSNode(ItemType x)
{
	SNode* p = new SNode;
	if (p == NULL)
	{
		printf("\nKhong The cap phat nut moi!");
		getch();
		return NULL;
	}
	p->info = x;
	p->next = NULL;
	return p;


}

void TaoSListRong(SList &sl)
{
	sl.head = NULL;

	sl.tail = NULL;


}

int KTRong(SList sl)
{
	if (sl.head == NULL)
		return 1;
	else return 0;


}

int ThemDau(SList &sl, SNode* &p)
{

	if (p == NULL)
		return 0;
	if (KTRong(sl) == 1)
	{
		sl.head = p;
		sl.tail = p;
	}
	else
	{
		p->next = sl.head;
		sl.head = p;

	}return 1;



}

int ThemDuoi(SList &sl, SNode* p)
{

	if (p == NULL)
		return 0;
	if (KTRong(sl) == 1)
	{
		sl.head = p;
		sl.tail = p;
	}
	else
	{
		sl.tail->next = p;
		sl.tail = p;
	}return 1;
}



void XuatSNode(SNode*p)
{

	printf("%5d", p->info);


}

void XuatSList(SList sl)
{
	printf("\nDanh Sach Lien Ket Don:\n");
	for (SNode*p = sl.head; p != NULL; p = p->next)
	{
		XuatSNode(p);
	}


}


void CreateSList_NhapTuBanPhim(SList &sl)
{

	int n;
	ItemType x;
	TaoSListRong(sl);
	do
	{
		printf("So Phan Tu cua danh sach (n>0):");
		scanf("%d", &n);
	} while (n <= 0);

	for (int i = 1; i <= n; i++)
	{
		printf("Nhap Phan Tu Thu %d la: ", i);
		scanf("%d", &x);
		SNode* p = CreateSNode(x);
		ThemDuoi(sl, p);

	}


}

void CreateAutoList(SList &sl)
{
	int n;
	ItemType x;
	TaoSListRong(sl);
	do
	{
		printf("So Phan tu cua mang: ");
		scanf("%d", &n);


	} while (n <= 0);

	srand(time(NULL));
	for (int i = 1; i <= n; i++)
	{
		x = (rand() % 100) - 50;
		SNode* p = CreateSNode(x);
		ThemDau(sl, p);
	}



}

void DocFile(SList &sl)
{

	sl.head = sl.tail = NULL;
	int n;
	KTRong(sl);
	FILE* f;
	f = fopen("input.txt", "r");
	if (f == NULL)
	{
		printf("Loi FILE!!!");
		getch();
		exit(1);

	}

	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++)
	{

		int x;
		fscanf(f, "%d", &x);
		SNode*p = CreateSNode(x);
		ThemDuoi(sl, p);

	}
	fclose(f);

}


void ThemPhanTuVaoCuoiDS(SList &sl)
{
	int x;
	printf("Nhap Phan Tu Can them vao ds: ");
	scanf("%d", &x);
	SNode*p = CreateSNode(x);
	ThemDuoi(sl, p);


}


SNode* FindNode_Y(SList sl,ItemType x)
{
	SNode*p;
	for (p = sl.head; p != NULL; p = p->next)
	{
		if (p->info == x)
			return p;

	}return NULL;

	
}

int ThemPtSauPt(SList &sl, SNode*p, SNode*q)
{

	if (q == NULL || p == NULL)
		return 0;
	p->next = q->next;
	q->next = p;
	if (sl.tail == q)
		sl.tail = p;
	return 1;

}



void ThemX_TruocY(SList &sl, int x, int y)
{
	SNode*p = CreateSNode(x);
	SNode*q = FindNode_Y(sl, y);
	
	if (q == NULL)
	{
		printf("Khong ton tai %d trong ds!!!\n", y);
		return;
	}

	
	if (q == sl.head)
	{
		ThemDau(sl,p);

	}
	else
	{

		SNode*t = sl.head;
		while (t->next != q)
		{
			t = t->next;
		}
		p->next = t->next;
		t->next = p;
	}
}


int deleteHead(SList &sl, ItemType x)
{

	if (KTRong(sl) == 1) return 0;
	SNode*p = sl.head;
	sl.head = sl.head->next;
	if (sl.head == NULL)
		sl.tail == NULL;
	x = p->info;
	delete p;
	return 1;

}

int deleteSauPt(SList &sl, SNode* q, ItemType &x)
{

	if (q == NULL || q->next == NULL) return 0;
	SNode*p = q->next;
	if (sl.tail == p)
		sl.tail = q;
	x = p->info;
	delete p;
	return 1;


}


SNode* TimPtNhoHonX(SList sl, int x)
{

	for (SNode*i = sl.head; i != NULL; i = i->next)
	{
		if (i->info > x)
			return i;
		
	}
	return NULL;
}

int XoaPt(SList &sl, ItemType &x)
{
	SNode*p = TimPtNhoHonX(sl, x);
	
	if (p == NULL)
		return 0;
	if (p == sl.head)
		deleteHead(sl, x);
	else
	{
		SNode* q = sl.head;
		while (q->next !=p)
		{
			q = q->next;
			deleteSauPt(sl, q, x);
			
		}
	
	}return 1;




}



void main()
{
	SList sl;
	ItemType x;
	int chon;
	
	/*CreateSList_NhapTuBanPhim(sl);*/
	/*CreateAutoList(sl);*/
	DocFile(sl);
	XuatSList(sl);

	printf("\n\n>>>>>>>>>>>>>>>>>Menu<<<<<<<<<<<<<<<<<<<<");
	printf("\n1: Them Phan Tu moi vao cuoi ds\n2:Them PT X vao sau PT Y\n3:Xoa Phan Tu Lon Hon X");

	do
	{
		printf("\nChon Bai Tap:");
		scanf("%d", &chon);

		switch (chon)
		{

		case 1:
		{
				 
				  ThemPhanTuVaoCuoiDS(sl);
				  XuatSList(sl);

		}break;

		case 2:
		{		  
				  int x,y;
				  printf("Nhap Phan tu can tim:");
				  scanf("%d", &y);
				  printf("Nhap Phan Tu Can them vao ds: ");
				  scanf("%d", &x);

				  ThemX_TruocY(sl, x, y);


				 /* SNode*p = CreateSNode(x);
				  SNode*q = FindNode_Y(sl, y);
				  ThemPtSauPt(sl, p, q);*/
				  XuatSList(sl);

		}break;


		case 3:
		{
				  int x;
				  printf("Nhap Phan Tu Can them vao ds: ");
				  scanf("%d", &x);
				  TimPtNhoHonX_VaXoaNo(sl, x);

				  
				  XuatSList(sl);

		}


		default:
			break;
		}

	} while (chon != 0);








	getch();

}