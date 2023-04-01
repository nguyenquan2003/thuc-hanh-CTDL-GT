#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

typedef int ItemType;

struct HashNode
{
	ItemType Key;
	HashNode* Next;
};
//HashNode* bucket[KEYSIZE];
typedef HashNode* NodePtr;
NodePtr* bucket;//=new NodePtr[KEYSIZE];
//const float threshold=0.6;
//int count=0;
//int countMax=KEYSIZE*threshold;
int KEYSIZE = 10;
//hàm băm
int HashFuntion(int key)
{
	return key % KEYSIZE;
}
//phép toán khởi tạo
void InitBucket()
{
	bucket = new NodePtr[KEYSIZE];
	for (int i = 0; i < KEYSIZE; i++)
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
	for (int i = 0; i < KEYSIZE; i++)
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
	HashNode* p, * q;
	q = NULL;
	for (p = bucket[b]; p != NULL && k > p->Key; p = p->Next)
		q = p;
	if (q == NULL)
		Push(b, k);
	else
		InsertAfter(q, k);

}
//chèn phần tử có khóa k vào bảng băm
void Insert(ItemType k)
{
	int b = HashFuntion(k);
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
	k = p->Key;
	bucket[b] = p->Next;
	delete p;
	return k;

}
//xóa nút ngay sau nút p
int DeleteAfter(HashNode* p)
{
	HashNode* q;
	int k;
	if (p == NULL || p->Next == NULL)
	{
		printf("\n khong xoa node duoc");
		return 0;
	}
	q = p->Next;
	k = q->Key;
	p->Next = q->Next;
	delete q;
	return k;
}

void Remove(ItemType k) {
	HashNode* q, * p;
	q = new HashNode;
	int b = HashFuntion(k); 	//tìm vị trí trong bảng băm
	p = bucket[b]; //gán giá trị đầu tiên cuả phần từ thứ i trong bảng băm
	while (p != NULL && p->Key != k)
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
			DeleteAfter(q);
	}//xoa nut
}

//xóa bucket trong bang băm
void ClearBucket(int b)
{
	HashNode* p, * q; //q nút truoc1, p nút sau
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
	for (int i = 0; i < KEYSIZE; i++)
		ClearBucket(i);
}
//duyệt các phần tử trong bucket
void TraverseBucket(int b)
{
	HashNode* p = bucket[b];
	while (p != NULL)
	{
		printf("[%d]-> ", p->Key);
		p = p->Next;
	}
	if (!p)
		printf("null");
}
//duyệt toàn bộ  bảng băm
void Traverse()
{
	for (int b = 0; b < KEYSIZE; b++)
	{
		if (bucket[b] != NULL)
		{
			printf("Bucket thu %d: ", b);
			TraverseBucket(b);
			printf("\n");
		}
	}

}
//tìm kiếm  một phần tử trong Bảng băm
HashNode* Search(ItemType k)
{
	int b = HashFuntion(k);
	HashNode* p = bucket[b];
	while (p)
	{
		if (p->Key == k)
			return p;
		p = p->Next;
	}
	return NULL;
}
void resize()
{
	int cu = KEYSIZE;
	KEYSIZE = KEYSIZE * 2;
	NodePtr* moi = new NodePtr[KEYSIZE];
	for (int i = 0; i < KEYSIZE; i++)
		moi[i] = NULL;
	for (int b = 0; b < cu; b++)
	{
		NodePtr p = bucket[b];
		while (p != NULL)
		{
			int x = p->Key;
			int bb = HashFuntion(x);
			//NodePtr *pp=new HashNode;

		}
	}

}
void nhapdulieu()
{
	int n, x;
	printf("Nhap so phan tu: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("nhap gia tri thu %d", i);
		scanf_s("%d", &x);
		Insert(x);
	}
}
void Docfile()
{
	FILE* f = fopen("data.txt", "r+");
	if (f == NULL)
	{
		printf("\nLoi doc file!");
		return;
	}
	int x;
	while (!feof(f))
	{
		fscanf(f, "%d", &x);
		Insert(x);
	}
	fclose(f);
}
void Taongaunhien()
{
	int n;
	int x;
	printf("cho biet so PT: ");
	scanf_s("%d", &n);
	srand((unsigned)time(NULL));//Tạo số mới sau mỗi lần thực hiện
	for (int i = 1; i <= n; i++)
	{
		x = (rand() % 100) + 1; //Tạo 1 số ngẫu nhiên trong [1, 199]
		Insert(x);
	}
}
void freeNode(HashNode*& p)
{
	delete p;
}
void tinh(int n)
{
	HashNode* p, * q;
	int b, a;
	for (int i = 0; i < KEYSIZE; i++)
	{
		if (bucket[i] != NULL)
		{
			p = bucket[i];
			while (p)
			{
				//n=a[i]+a[j] k=50
				a = n - p->Key;
				if (a < 0)
					break;
				else
				{
					b = HashFuntion(a);
					if (b > i && bucket[b] != NULL)//không cho quay ngược lên
					{
						q = bucket[b];
						while (q && (p->Key + q->Key) != n)
							q = q->Next;
						if (q)
							printf("[ %d, %d]", p->Key, q->Key);
					}
					else if (b = i && bucket[b] != NULL)//không cho quay ngược lên
					{
						q = p->Next;//không cho q chay ngược ra
						while (q && (p->Key + q->Key) != n)
							q = q->Next;
						if (q)
							printf("[ %d, %d]", p->Key, q->Key);
					}
					p = p->Next;
				}

			}
		}
	}
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
	HashNode* p;
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
			Taongaunhien();
			printf("\nXem bang bam:\n");
			Traverse();
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
			printf("nhap x:");
			scanf_s("%d", &x);
			Remove(x);
			printf("Xem bang bam:\n");
			Traverse();
			break;
		case 6:
			printf("nhap gia tri k:");
			scanf_s("%d", &x);
			tinh(x);
			cout << endl;
		}
	} while (chon != 0);
}
int main()
{
	Process();
}