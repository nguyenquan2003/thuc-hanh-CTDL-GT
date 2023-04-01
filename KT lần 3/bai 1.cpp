#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
struct HashNode
{
	int key;
	HashNode* next;
};
HashNode* HashTable;
struct HashTable
{
	HashNode* bucket; //su dung mang dong
	int size; //kich thuoc bang bam (so bucket)
	int count; //so luong phan tu tren bang bam
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
	bucket = new HashNode * [keysize];
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
		cout << "khong them vao node moi";
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
		cout << "null";
	}
}
void Traverse() //duyệt toàn bộ  bảng băm
{
	for (int b = 0; b < keysize; b++)
	{
		if (bucket[b] != NULL)
		{
			cout << "bucket thu " << b << " : ";
			TraverseBucket(b);
			cout << endl;
		}
	}
}
void nhapdulieu()
{
	int n = 17, x;
	for (int i = 0; i < 17; i++)
	{
		cout << "nhap gia tri thu [" << i << "] = ";
		cin >> x;
		Insert(x);
	}
}
void Taongaunhien()
{
	int n, x;
	cout << "cho biet so PT : ";
	cin >> n;
	srand((unsigned)time(NULL));//Tạo số mới sau mỗi lần thực hiện
	for (int i = 1; i <= n; i++)
	{
		x = (rand() % 90) + 1;
		Insert(x);
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
int DeleteAfter(HashNode* p) //xóa nút ngay sau nút p
{
	HashNode* q;
	int k;
	if (p == NULL || p->next == NULL)
	{
		cout << "khong xoa node duoc";
		return 0;
	}
	q = p->next;
	k = q->key;
	p->next = q->next;
	delete q;
	return k;
}
int pop(int b) //xóa nút ở đầu bucket
{
	HashNode* p;
	int k;
	if (IsEmptyBucket(b))
	{
		cout << "Bucket " << b << "rong, Khong xoa duoc ";
		return 0;
	}
	p = bucket[b];
	k = p->key;
	bucket[b] = p->next;
	delete p;
	return k;
}
void Remove()
{
	for (int b = 0; b < keysize; ++b)
	{
		HashNode* p = bucket[b];
		HashNode* q = NULL;
		while (p != NULL)
		{
			if (p->key % 2 == 0)
			{
				if (q == NULL)
				{
					bucket[b] = p->next;
					delete p;
					p = bucket[b];
				}
				else {
					q->next = p->next;
					delete p;
					p = q->next;
				}
			}
			else
			{
				q = p;
				p = p->next;
			}
		}
	}
}
void ClearBucket(int b)
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
void resize()
{
	int cu = keysize;
	keysize *= 3;
	HashNode** moi = new HashNode * [keysize];

	for (int i = 0; i < keysize; i++)
		moi[i] = NULL;
	for (int i = 0; i < cu; i++)
	{
		HashNode* p = bucket[i];
		while (p != NULL)
		{
			int x = p->key;
			int bb = HashFuntion(x);
			HashNode* pp = new HashNode;
			pp->key = x;
			pp->next = moi[bb];
			moi[bb] = pp;
			p = p->next;
		}
		ClearBucket(i);
	}
	delete bucket;
	bucket = moi;
}

int main()
{
	int x, chon;
	HashNode* p;
	InitBucket();
	cout << "-----------------MENU---------------" << endl;;
	cout << "1.Tao bang bam co kich thuoc mang la 17 " << endl;
	cout << "2.Tao bang bam ngau nhien " << endl;
	cout << "3.Xuat cac ptu bang bam " << endl;
	cout << "4.Tim X " << endl;
	cout << "5.Tang kich thuoc mang gap 3" << endl;
	cout << "6.Xoa X la so chan " << endl;
	cout << "------------------------------------" << endl;
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
		Taongaunhien();
		cout << "\nXem bang bam:\n";
		Traverse();
		break;
	case 3:
		Taongaunhien();
		cout << "\nXem bang bam:\n";
		Traverse();
		break;
	case 4:
		Taongaunhien();
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
		Taongaunhien();
		cout << "\nXem bang bam:\n";
		Traverse();
		resize();
		Traverse();
		break;
	case 6:
		Taongaunhien();
		cout << "\nXem bang bam:\n";
		Traverse();
		Remove();
		cout << "\nBang bam sau khi xoa : \n";
		Traverse();
		break;
	default: cout << "bn nhap sai cu phap. Vui long chay lai ";
		break;
	}
}