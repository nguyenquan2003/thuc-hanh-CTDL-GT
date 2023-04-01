#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define NULLKEY -1
#define TRUE 1
#define FALSE 0
int  M = 15;

int N; //biến toàn cục, chỉ số nut hiện có trên bảng băm
struct Taikhoan
{
	char Username[12];
	char Fullname[50];
	char Pass[10];
	int Account;
};
typedef Taikhoan Itemtype;
struct Node
{
	Itemtype key;
};
//khai bao bang băm
Node* Hashtable;

int HashFunction(char k[])
{
	int b = 0, i;
	for (i = 1; i <= strlen(k); i++)
		b = b + (int)k[i];
	return (b % M);
}
int IsEmpty()
{
	return (N == 0 ? TRUE : FALSE);
}
void Initializa()
{
	Hashtable = new Node[M];
	for (int i = 0; i < M; i++)
	{
		strcpy(Hashtable[i].key.Username, "");
		strcpy(Hashtable[i].key.Fullname, "");
		strcpy(Hashtable[i].key.Pass, "");
		Hashtable[i].key.Account = NULLKEY;
	}
	N = 0;
}
int IsFull()
{
	return (N == M - 1 ? TRUE : FALSE);
}
int Search(char k[])
{

	for (int i = 0; i < M; i++)
	{
		int b = (HashFunction(k) + i) % M;
		if (strcmp(Hashtable[b].key.Fullname, k) == 0)
		{
			return b;
			break;
		}
	}

	return (M);
}
int kiemtra(char k[], char h[])
{

	for (int i = 0; i < M; i++)
	{
		int b = (HashFunction(k) + i) % M;
		if (strcmp(Hashtable[b].key.Username, k) == 0 && strcmp(Hashtable[b].key.Pass, h) == 0)
		{
			return b;
			break;
		}
	}

	return (M);
}
void resize()
{
	int i;
	int cu = M;
	M = M * 2;
	Node* moi = new Node[M];
	for (i = 0; i < M; i++)
	{
		strcpy(moi[i].key.Username, "");
		strcpy(moi[i].key.Fullname, "");
		strcpy(moi[i].key.Pass, "");
		moi[i].key.Account = NULLKEY;
	}
	for (i = 0; i < cu; i++)
		moi[i].key = Hashtable[i].key;
	delete Hashtable;
	Hashtable = moi;
}
void Insert(Itemtype k)
{
	/*if(IsFull())
	{

	printf("\n bang bam daykhong them nut co khoa %d duoc",k);
	return ;
	}*/
	if (N >= M * 0.6)
		resize();
	for (int i = 0; i < M; i++)
	{
		int b = (HashFunction(k.Username) + i) % M;
		if (strcmp(Hashtable[b].key.Username, "") == 0)
		{
			Hashtable[b].key = k;
			N = N + 1;
			break;
		}
	}

}
void ViewTable()
{
	for (int i = 0; i < M; i++)
		if (strcmp(Hashtable[i].key.Username, "") != 0)
			printf("\n Table [%d]: %s , %s , %s, %d ", i, Hashtable[i].key.Username, Hashtable[i].key.Fullname, Hashtable[i].key.Pass, Hashtable[i].key.Account);
}
void themnut()
{
	int n;
	Itemtype key;
	printf("so nut moi:");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Username: ");
		fflush(stdin);
		gets_s(key.Username);
		printf("Fullname: ");
		fflush(stdin);
		gets_s(key.Fullname);
		printf("Password: ");
		fflush(stdin);
		gets_s(key.Pass);
		printf("AccountType");
		scanf_s("%d", &key.Account);
		Insert(key);
	}
}

void Docfile()
{
	int n;
	Itemtype key;
	FILE* f = fopen("data.txt", "r+");
	if (!f)
	{
		printf("Loi doc file");
		return;
	}
	while (!feof(f))
	{
		fscanf(f, "%[^#]# %[^#]# %[^#]# %d\n", &key.Username, &key.Fullname, &key.Pass, &key.Account);
		Insert(key);
	}
	fclose(f);
}
void Menu()
{
	printf("\n------------------------------");
	printf("\n1. Them tai khoan moi vao danh sach.");
	printf("\n2. Xuat thong tin: ");
	printf("\n3. Tim thong tin tai khoan bang fullnam. ");
	printf("\n4. Kiem tra pass va usename.");
	printf("\n---------------------------");
}
void process()
{
	int i;
	int key, chon;
	char u[12];
	char p[10];
	char ms[30];
	char c;
	Initializa();
	do
	{
		Menu();
		printf("\n chon chuc nang:");
		scanf_s("%d", &chon);
		switch (chon)
		{
		case 1:
			themnut();
			ViewTable();
			break;
		case 2:
			Docfile();
			ViewTable();
			break;
		case 3:
			printf("Nhap Fullname tim Username:");
			fflush(stdin);
			gets_s(ms);
			i = Search(ms);
			if (i != M)
				printf("\n Table [%d]: %s , %s , %s , %d ", i, Hashtable[i].key.Username, Hashtable[i].key.Fullname, Hashtable[i].key.Pass, Hashtable[i].key.Account);
			else
				printf("khong tim thay:");
			break;
		case 4:
			printf("nhap usename cua tai khoan can tim: ");
			fflush(stdin);
			gets_s(u);
			i = kiemtra(u, p);
			printf("nhap pass cua tai khoan can tim: ");
			fflush(stdin);
			gets_s(p);
			i = kiemtra(u, p);
			if (i != M)
				printf("Co tai khoan cua ban !!!");
			else
				printf("");
			break;

		}
	} while (chon != 0);
}
void main()
{
	process();
}