#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
struct HashNode
{
	int key;
	HashNode* next;
};
HashNode** bucket;//=new NodePtr[KEYSIZE];
int keysize = 10;
int HashFuntion(int key) //hàm băm
{
	return key % keysize;
}
//phép toán khởi tạo
void InitBucket()
{
	bucket = new HashNode*[keysize];
	for (int i = 0; i < keysize; i++)
	{
		bucket[i] = NULL;
	}
}
int IsEmptyBucket(int b) //kiểm tra bucket rỗng
{
	return (bucket[b] == NULL ? 1 : 0);
}
int IsEmpty() //kiểm tra bảng băm rỗng
{
	for (int i = 0; i < keysize; i++)
	{
		if (bucket[i] != NULL)
		{
			return false;
		}
	}
	return true;
}
void Push(int b, int x) //Thêm một node vào đầu bucket
{
	HashNode* p = new HashNode;
	p->key = x;
	p->next = bucket[b];
	bucket[b] = p;
}
void InsertAfter(HashNode* p, int k) //thêm vào bucket một node mới sau p
{
	if (p == NULL)
	{
		cout<<"khong them vao node moi";
	}
	else
	{
		HashNode* q = new HashNode;
		q->key = k;
		q->next = p->next;
		p->next = q;
	}
}
void Place(int b, int k) //phép toán chèn khóa k vào danh sách liên kết
{
	HashNode* p, * q;
	q = NULL;
	for (p = bucket[b]; p != NULL && k > p->key; p = p->next)
		q = p;
	if (q == NULL)
	{
		Push(b, k);
	}
	else
	{
		InsertAfter(q, k);
	}

}
void Insert(int k) //chèn phần tử có khóa k vào bảng bă
{
	int b = HashFuntion(k);
	Place(b, k);
}
int pop(int b) //xóa nút ở đầu bucket
{
	HashNode* p;
	int k;
	if (IsEmptyBucket(b))
	{
		cout<<"Bucket " <<b <<"rong, Khong xoa duoc ";
		return 0;
	}
	p = bucket[b];
	k = p->key;
	bucket[b] = p->next;
	delete p;
	return k;
}
int DeleteAfter(HashNode* p) //xóa nút ngay sau nút p
{
	HashNode* q;
	int k;
	if (p == NULL || p->next == NULL)
	{
		cout<<"khong xoa node duoc";
		return 0;
	}
	q = p->next;
	k = q->key;
	p->next = q->next;
	delete q;
	return k;
}
void Remove(int k)
{
	HashNode* q, * p;
	q = new HashNode;
	int b = HashFuntion(k); 	//tìm vị trí trong bảng băm
	p = bucket[b]; //gán giá trị đầu tiên cuả phần từ thứ i trong bảng băm
	while (p != NULL && p->key != k)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL)
		cout << "khong co nut co khoa " << k;
	else
	{
		///count--;
		if (p == bucket[b])
			pop(b);
		else
			DeleteAfter(q);
	}//xoa nut
}
void ClearBucket(int b) //xóa bucket trong bang băm
{
	HashNode* p, * q; //q nút truoc1, p nút sau
	q = NULL;
	p = bucket[b];
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q;
	}
	bucket[b] = NULL;//khoi động lại bucket b
}
void CLear() //xóa tất cả phần tử trong bảng băm
{
	for (int i = 0; i < keysize; i++)
	{
		ClearBucket(i);
	}
}
void TraverseBucket(int b) //duyệt các phần tử trong bucket
{
	HashNode* p = bucket[b];
	while (p != NULL)
	{
		cout << "[" << p->key << "]" << "-> ";
		p = p->next;
	}
	if (!p)
	{
		cout<<"null";
	}
}
void Traverse() //duyệt toàn bộ  bảng băm
{
	for (int b = 0; b < keysize; b++)
	{
		if (bucket[b] != NULL)
		{
			cout<<"bucket thu "<< b<<" : ";
			TraverseBucket(b);
			cout<<endl;
		}
	}
}
HashNode* Search(int k) //tìm kiếm  một phần tử trong Bảng băm
{
	int b = HashFuntion(k);
	HashNode* p = bucket[b];
	while (p)
	{
		if (p->key == k)
		{
			return p;
		}
		p = p->next;
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

	for (int b = 0; b < cu; b++) {
		NodePtr p = bucket[b];
		while (p != NULL) {
			int x = p->Key;
			int bb = HashFuntion(x);
			NodePtr pp = new HashNode;
			pp->Key = x;
			pp->Next = moi[bb];
			moi[bb] = pp;
			p = p->Next;
		}
		ClearBucket(b);
	}
	delete bucket;
	bucket = moi;
}
void nhapdulieu()
{
	int n, x;
	cout<<"nhap so phan tu : ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout<<"nhap gia tri thu ["<< i<<"] = ";
		cin >> x;
		Insert(x);
	}
}
void Docfile()
{
	FILE* f = fopen("data.txt", "r+");
	if (f == NULL)
	{
		cout<<"\nloi doc file!";
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
	int n,x;
	cout<<"cho biet so PT : ";
	cin >> n;
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
	for (int i = 0; i < keysize; i++)
	{
		if (bucket[i] != NULL)
		{
			p = bucket[i];
			while (p)
			{
				//n=a[i]+a[j] k=50
				a = n - p->key;
				if (a < 0)
					break;
				else
				{
					b = HashFuntion(a);
					if (b > i && bucket[b] != NULL)//không cho quay ngược lên
					{
						q = bucket[b];
						while (q && (p->key + q->key) != n)
							q = q->next;
						if (q)
						{
							cout << "[" << p->key << "," << q->key << "]";
						}
					}
					else if (b = i && bucket[b] != NULL)//không cho quay ngược lên
					{
						q = p->next;//không cho q chay ngược ra
						while (q && (p->key + q->key) != n)
							q = q->next;
						if (q)
						{
							cout << "[" << p->key<<","<< q->key << "]";
						}
					}
					p = p->next;
				}

			}
		}
	}
}
int main()
{
	int x, chon;
	HashNode* p;
	InitBucket();
	cout << "-----------------MENU---------------" << endl;
	cout << "1. Tao bang bam tu nhap " << endl;
	cout << "2. Tao bang bam tu file " << endl;
	cout << "3. Tao ngau nhien " << endl;
	cout << "4. Tim phan tu " << endl;
	cout << "5. Xoa X " << endl;
	cout << "6. Xuat cap so k=a[i]+a[j] " << endl;
	cout << "------------------------------------"<<endl;
	cout << "moi bn chon bai : ";
	cin >> chon;
	switch (chon)
	{
	case 1:
		nhapdulieu();
		cout << "\nXem bang bam:\n";
		Traverse();
		break;
	case 2:
		Docfile();
		cout<<"\nXem bang bam:\n ";
		Traverse();
		break;
	case 3:
		Taongaunhien();
		cout << "\nXem bang bam:\n";
		Traverse();
		break;
	case 4:
		nhapdulieu();
		cout << "\nXem bang bam:\n";
		Traverse();
		cout << "nhap phan tu can tim: ";
		cin >> x;
		p = Search(x);
		if (p)
			cout << "tim thay phan tu " << p->key;
		else
			cout << "khong tim thay ";
		break;
	case 5:
		nhapdulieu();
		cout << "\nXem bang bam:\n";
		Traverse();
		cout << "nhap x : ";
		cin >> x;
		Remove(x);
		cout << "\nXem bang bam:\n";
		Traverse();
		break;
	case 6:
		nhapdulieu();
		cout << "\nXem bang bam:\n";
		Traverse();
		cout << "nhap gia tri k : ";
		cin >> x;
		cout << "cap so k=a[i]+a[j] : ";
		tinh(x);
		cout << endl;
		break;
	default: cout << "bn nhap sai cu phap. Vui long chay lai ";
		break;
	}
}