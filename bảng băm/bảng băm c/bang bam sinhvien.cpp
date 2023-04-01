#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<string.h>
using namespace std;
struct sinhvien
{
	char masv[10];
	char hoten[30];
	int namsinh, diem;
};
typedef sinhvien ItemType;

struct HashNode
{
	ItemType Key;
	HashNode* Next;
};

typedef HashNode *NodePtr;
NodePtr* bucket;//=new NodePtr[KEYSIZE];

int KEYSIZE = 100;
//hàm băm
int HashFuntion(int key)
{
	return key%KEYSIZE;
}
//phép toán khởi tạo
void InitBucket()
{
	bucket = new NodePtr[KEYSIZE];
	for (int i = 0; i<KEYSIZE; i++)
		bucket[i] = NULL;
}
//kiểm tra bucket rỗng
int IsEmptyBucket(int b)
{
	return (bucket[b] == NULL ? 1 : 0);
}
//kiểm tra bảng băm rỗng
int IsEmpty()
{
	for (int i = 0; i<KEYSIZE; i++)
	if (bucket[i] != NULL)
		return false;
	return true;
}

//Thêm một node vào đầu bucket
void Push(int b, ItemType x)
{
	HashNode* p = new HashNode;
	p->Key = x;
	p->Next = bucket[b];
	bucket[b] = p;
}

//thêm vào bucket một node mới sau p
void InsertAfter(HashNode* p, ItemType k)
{
	if (p == NULL)
		printf("Khong them vao node moi");
	else
	{
		HashNode* q = new HashNode;
		q->Key = k;
		q->Next = p->Next;
		p->Next = q;
	}
}
//phép toán chèn khóa k vào danh sách liên kết
void Place(int b, ItemType k)
{
	HashNode* p, *q;
	q = NULL;
	for (p = bucket[b]; p != NULL && _strcmpi(k.hoten,p->Key.hoten)>0; p = p->Next)
		q = p;
	if (q == NULL)
		Push(b, k);
	else
		InsertAfter(q, k);

}
//chèn phần tử có khóa k vào bảng băm
void Insert(ItemType k)
{
	int b = HashFuntion(k.diem);
	Place(b, k);

}

//xóa nút ở đầu bucket
int pop(int b)
{
	HashNode* p;
	int k;
	if (IsEmptyBucket(b))
	{
		printf("Bucket %d rong, Khong xoa duoc", b);
		return 0;
	}
	p = bucket[b];
	k = p->Key.diem;
	bucket[b] = p->Next;
	delete p;
	return k;

}
//xóa nút ngay sau nút p
int DeleteAfter(HashNode *p)
{
	HashNode *q;
	int k;
	if (p == NULL || p->Next == NULL)
	{
		printf("\n khong xoa node duoc");
		return 0;
	}
	q = p->Next;
	k = q->Key.diem;
	p->Next = q->Next;
	delete q;
	return k;
}

void Remove(ItemType k) {
	NodePtr p, q;
	q = new HashNode;
	int b = HashFuntion(k.diem); 	//tìm vị trí trong bảng băm
	p = bucket[b]; //gán giá trị đầu tiên cuả phần từ thứ i trong bảng băm
	while (p != NULL && _strcmpi(p->Key.hoten ,k.hoten)!=0)
	{
		q = p;
		p = p->Next;
	}
	if (p == NULL)
		printf("\n khong co nut co khoa %d", k);
	else
	{
		///count--;
		if (p == bucket[b])
			pop(b);
		else
			DeleteAfter(p);
	}//xoa nut
}

//xóa bucket trong bang băm
void ClearBucket(int b)
{
	HashNode *p, *q; //q nút truoc1, p nút sau
	q = NULL;
	p = bucket[b];
	while (p != NULL)
	{
		q = p;
		p = p->Next;
		delete q;
	}
	bucket[b] = NULL;//khoi động lại bucket b
}
//xóa tất cả phần tử trong bảng băm
void CLear()
{
	for (int i = 0; i<KEYSIZE; i++)
		ClearBucket(i);
}
void xuat1sv(sinhvien x)
{
	printf("%-10s%-30s%-5d%-5d\n", x.masv, x.hoten, x.namsinh, x.diem);
}
//duyệt các phần tử trong bucket
void TraverseBucket(int b)
{
	HashNode* p = bucket[b];
	while (p != NULL)
	{
		xuat1sv(p->Key);
		p = p->Next;
	}
	if (!p)
		printf("null");
}
//duyệt toàn bộ  bảng băm
void Traverse()
{
	for (int b = 0; b<KEYSIZE; b++)
	{
		if (bucket[b] != NULL)//in bucket co du lieu
		{
			printf("Bucket thu %d: ", b);
			TraverseBucket(b);
			printf("\n");
		}
	}

}
//tìm kiếm  theo diem
HashNode* Search(int k)
{
	int b = HashFuntion(k);
	HashNode* p = bucket[b];
	while (p)
	{
		if (p->Key.diem == k)
			return p;
		p = p->Next;
	}
	return NULL;
}
HashNode* Searchten(int k,char ten[])
{
	int b = HashFuntion(k);
	HashNode* p = bucket[b];
	while (p)
	{
		if (_strcmpi(p->Key.hoten,ten)==0)
			return p;
		p = p->Next;
	}
	return NULL;
}
void nhap1sv(sinhvien &x)
{
	printf("Nhap ma sv: ");
	fflush(stdin);
	gets(x.masv);
	printf("Nhap ho ten: ");
	fflush(stdin);
	gets(x.hoten);
	printf("Nhap nam sinh:");
	scanf("%d", &x.namsinh);
	printf("Nhap diem:");
	scanf("%d", &x.diem);
}

void nhapdulieu()
{
	int n;
	sinhvien x;
	printf("Nhap so phan tu: ");
	scanf_s("%d", &n);
	for (int i = 0; i<n; i++)
	{
		printf("nhap gia tri thu %d: ", i);
		scanf_s("%d", &x);
		Insert(x);
		//Sleep(150);
	}
}
void Docfile()
{
	FILE *f = fopen("data1.txt", "r+");
	if (f == NULL)
	{
		printf("\nLoi doc file!");
		return;
	}
	int n;
	char a[5] = "", b[5] = "";
	fscanf(f, "%[^\n]%*c", &a);
	n = atoi(a);
	for (int i = 0; i < n;i++)
	{
		sinhvien x;
		
		fscanf(f, "%[^#]%*c %[^#]%*c %[^#]%*c %[^\n]%*c", &x.masv,x.hoten,&a,&b);
		x.namsinh = atoi(a);
		x.diem = atoi(b);
		Insert(x);
		//Sleep(100);
	}
	fclose(f);
}

void freeNode(HashNode* &p)
{
	delete p;
}

void Menu()
{
	cout << "-----------------MENU---------------\n";
	cout << "1. Tao bang bam tu nhap.\n";
	cout << "2. Tao bang bam tu file.\n";
	cout << "3. Tao ngau nhien.\n";
	cout << "4. Tim phan tu.\n";
	cout << "5. Xoa X.\n";
	cout << "6. Xuat cap so k=a[i]+a[j]:\n";
	cout << "------------------------------------\n";
}
void Process()
{
	int x, chon;
	HashNode *p;
	InitBucket();
	do
	{
		Menu();
		printf("Chon chuc nang: ");
		scanf_s("%d", &chon);
		switch (chon)
		{
		case 1:
			nhapdulieu();
			printf("\nXem bang bam:\n");
			Traverse();
			break;
		case 2:
			Docfile();
			printf("\nXem bang bam\n");
			Traverse();
			break;
		case 3:
		
			break;
		case 4:
			printf("Nhap  phan tu can tim: ");
			scanf_s("%d", &x);
			p = Search(x);
			if (p)
				printf("tim thay phan tu [%d ]\n", p->Key);
			else
				printf("Khong tim  thay\n ");
			break;
		case 5:
			/*printf("nhap x:");
			scanf_s("%d", &x);
			Remove(x);
			printf("Xem bang bam:\n");
			Traverse();*/
			break;
		case 6:
			break;
		}
	} while (chon != 0);
}
void main()
{
	Process();
}