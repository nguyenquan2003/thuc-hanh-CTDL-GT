#include <iostream>
using namespace std;
struct node
{
	int data; //du lieu trong 1 node
	struct node* pNext; //con tro dung de lien ket cac node
};
typedef struct node Node; //thay the struct node thanh Node
struct list
{
	Node* pHead; //node quan li dau ds
	Node* pTail; //node quan li cuoi ds
};
typedef struct list List; //thay the struct list thanh List

void khoi_tao(List& l)
{
	//cho 2 node tro den NULL vi dslk chua co ptu
	l.pHead = NULL;
	l.pTail = NULL;
}
Node* khoi_tao_node(int x)
{
	Node* p = new Node; //cap phat vung nho cho Node p
	if (p == NULL)
	{
		cout << "khong du bo nho cap phat ";
		return NULL;
	}
	p->data = x; //truyen gtri x cho data

	//dau tien khai bao node neu node chua co lk den node nao het thi ==> c tro cua no se tro den NULL
	p->pNext = NULL;
	return p; //tra ve Node p vua khoi tao
}
void them_vao_dau(List& l, Node* p)
{
	//ds dang rong
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p; //node dau cx chinh la node cuoi va la p
	}
	else
	{
		p->pNext = l.pHead; //cho c tro cua node can them la node p lien ket den node dau - pHead
		l.pHead = p; //cap nhat lai pHead chinh la node p 
	}
}
void them_vao_cuoi(List& l, Node* p)
{
	//ds dang rong
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p; //node dau cx chinh la node cuoi va la p
	}
	else
	{
		l.pTail->pNext = p; //cho c tro cua node can them la node p lien ket den node cuoi - pTail
		l.pTail = p; //cap nhat lai pHead chinh la node p 
	}
}
int tim_max(List l)
{
	int max = l.pHead->data;
	for (Node* k = l.pHead->pNext; k != NULL; k = k->pNext)
	{
		if (max < k->data)
		{
			max = k->data;
		}
	}
	return max;
}
void them_node_vao_sau_node(List& l, Node* p)
{
	int a;
	cout << "nhap gia tri node q : ";
	cin >> a;
	Node* q = khoi_tao_node(a);

	//neu danh sach chi co 1 ptu va ptu do cung chinh la node q =>bai toan tro thanh them vao cuoi ds
	if (q->data == l.pHead->data && l.pHead->pNext == NULL)
	{
		them_vao_cuoi(l, p);
	}
	else
	{
		//duyet tu dau ds den cuoi ds de tim node q
		for (Node* k = l.pHead; k != NULL; k = k->pNext)
		{
			if (q->data == k->data)
			{
				Node* h = khoi_tao_node(p->data); //khoi tao node h de them vao sau node q
				Node* g = k->pNext; //cho node g tro den node nam sau node q
				h->pNext = g; //tao moi lk tu node p den node h <=> cug chinh la tao moi lk tu node h den node nam sau node q
				k->pNext = h; //tao moi lk tu node q den node h <=> chinh la node k den node h

			}
		}
	}
}
void them_node_vao_truoc_node(List& l, Node* p)
{
	int x;
	cout << "nhap gia tri node q :";
	cin >> x;
	Node* q = khoi_tao_node(x);
	if (q->data == l.pHead->data && l.pHead->pNext == NULL)
	{
		them_vao_dau(l, p);
	}
	else
	{
		Node* g = new Node;
		for (Node* k = l.pHead; k != NULL; k = k->pNext)
		{
			if (q->data == k->data)
			{
				Node* h = khoi_tao_node(p->data);
				h->pNext = k;
				g->pNext = h;
			}
			g = k; //g giu lien ket cho cac node nam trc node q
		}
	}
}
void xuat_danh_sach(List l)
{
	for (Node* k = l.pHead; k != NULL; k = k->pNext)
	{
		cout << k->data << " ";
	}
}
int main()
{
	List l;
	khoi_tao(l);
	int n,chon,x;
	cout << "=================MENU=================" << endl;
	cout << "1. them node vao dau dslk " << endl;
	cout << "2. them node vao cuoi dslk " << endl;
	cout << "3. tim so lon nhat trong dslk" << endl;
	cout << "4. them node p dang sau node q " << endl;
	cout << "moi ban chon bai : ";
	cin >> chon;
	cout << "nhap so luong node : ";
	cin >> n;
	switch (chon)
	{
	case 1: for (int i = 1; i <= n; i++)
	{
		cout << "nhap so nguyen x : ";
		cin >> x;
		Node* p = khoi_tao_node(x); //khoi tao 1 node so nguyen
		them_vao_dau(l, p); //them node p vao dau dslk don
	}
		  xuat_danh_sach(l);
		  break;
	case 2: for (int i = 1; i <= n; i++)
	{
		cout << "nhap so nguyen x : ";
		cin >> x;
		Node* p = khoi_tao_node(x); //khoi tao 1 node so nguyen
		them_vao_cuoi(l, p); //them node p vao cuoi dslk don
	}
		  xuat_danh_sach(l);
		  break;
	case 3: for (int i = 1; i <= n; i++)
	{
		cout << "nhap so nguyen x : ";
		cin >> x;
		Node* p = khoi_tao_node(x); //khoi tao 1 node so nguyen

		//co the them ham them_vao_dau hoac ham them_vao_cuoi thi code moi co the tim ra gtln
		them_vao_dau(l, p);
		//them_vao_cuoi(l, p); 
	}
		  cout << "so lon nhat trong node : " << tim_max(l);
		  break;
	case 4: //xem lai case nay  khong xuat danh sach ra ket qua man hinh
	{
		for (int i = 1; i <= n; i++)
		{
			cout << "nhap so nguyen x : ";
			cin >> x;
		}
		int a;
		cout << "nhap gia tri node p can them vao sau : ";
		cin >> a;

		Node* p = khoi_tao_node(a); //khoi tao 1 node so nguyen
		them_node_vao_sau_node(l, p);
		xuat_danh_sach(l);
		system("pause");
		break;
	}
	case 5: 
	{
		for (int i = 1; i <= n; i++)
		{
			cout << "nhap so nguyen x : ";
			cin >> x;
		}
		int a;
		cout << "nhap gia tri node p can them vao sau : ";
		cin >> a;
		Node* p = khoi_tao_node(x);
		them_node_vao_truoc_node(l, p);
		break;
	}
	default: cout << "bn nhap sai cu phap. Vui long nhap lai ";
		break;
	}
}