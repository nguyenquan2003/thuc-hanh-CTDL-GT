#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;
struct Node
{
	int data;
	Node* next;
};
struct List
{
	Node* head, * tail;
};
Node* create_node(int x)
{
	Node* p = new Node;
	if (p == NULL)
	{
		cout << "khong du bo nho cap phat ! ";
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}
void show_node(Node* p)
{
	cout << p->data;
}
void show_list(List l)
{
	for (Node* p = l.head; p != NULL; p = p->next)
	{
		cout << p->data << " ";
	}
}
void inint_list(List& l) //ham khoi tao node
{
	l.head = l.tail = NULL;
}

void insert_head(List& l, Node* p) //them vao dau ds
{
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else
	{
		p->next = l.head;
		l.head = p;
	}
}
void insert_tail(List& l, Node* p) //them vao cuoi ds
{
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else
	{
		l.tail->next = p;
		l.tail = p;
	}
}
void create_list(List& l, int n)
{
	int x;
	inint_list(l);
	for (int i = 0; i < n; i++)
	{
		cout << "nhap phan tu thu " << i + 1 << " : ";
		cin >> x;
		insert_tail(l, create_node(x));
	}
}

void insert_after(List& l, Node* q, Node* p) //chen p sau q
{
	if (p == NULL || q == NULL)
	{
		return;
	}
	else
	{
		if (q == l.tail)
		{
			insert_tail(l, p);
		}
		else
		{
			p->next = q->next;
			q->next = p;
		}
	}
}
void insert_before(List& l, Node* q, Node* p) //chen p trc q
{
	if (p == NULL || q == NULL)
	{
		return;
	}
	else
	{
		if (l.head == NULL)
		{
			l.head = l.tail = p;
		}
		else
		{
			Node* r = l.head;
			while (r->next != q)
			{
				r = r->next;
			}
			p->next = q;
			r->next = p;
		}
	}
}

Node* search(List l, int x) //????????????
{
	for (Node* p = l.head; p != NULL; p = p->next)
	{
		if (p->data == x)
		{
			return p;
		}
	}
	return NULL;
}
int search_x(List l, int x) //???????????????????????????
{
	int i = 0;
	Node* p;
	p = l.head;
	while (p && p->data == x)
	{
		p = p->next;
		i++;
	}
	if (p)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
void delete_head(List& l)
{
	if (l.head == NULL)
	{
		return;
	}
	else
	{
		Node* p = l.head;
		l.head = p->next;
		p->next = NULL;
		delete p;
	}
}
void delete_tail(List& l)
{
	if (l.head == NULL)
	{
		return;
	}
	else
	{
		Node* p = l.tail;
		Node* q = l.head;
		while (q->next != l.tail)
		{
			q = q->next;
		}
		l.tail = q;
		l.tail->next = NULL;
		delete p;
	}
}
void delete_before(List& l, Node* q)
{
	if (q == NULL)
	{
		cout << "khong tim thay ";
		return;
	}
	for (Node* i = l.head; i != NULL; i = i->next)
	{
		if (i->data == q->data)
		{
			if (l.tail == i->next)
			{
				delete_tail(l);
				return;
			}
			else
			{
				Node* p = i->next;
				i->next = i->next->next;
				delete p;
				return;
			}
		}
	}
}
void delete_after(List& l, Node* q)
{
	if (q == NULL)
	{
		cout << "khong tim thay ";
		return;
	}
	for (Node* i = l.head; i != NULL; i = i->next)
	{
		if (i->data == q->data)
		{
			if (l.tail == i->next)
			{
				delete_head(l);
				return;
			}
		}
		if (i->next->next->data == q->data)
		{
			Node* p = i->next;
			i->next = i->next->next;
			delete p;
			return;
		}
	}
}
int count(List l)
{
	Node* p = l.head;
	int i = 0;
	while (p != NULL)
	{
		i++;
		p = p->next;
	}
	return i;
}
void delete_k(List& l, int k) //xpa node k trong ds
{
	Node* p = l.head;
	int i = 1;
	if (k<1 || k>count(l))
	{
		cout << "vi tri xoa khong hop le ";
	}
	else
	{
		if (k == 1)
		{
			delete_head(l);
		}
		else if (k == count(l))
		{
			delete_tail(l);
		}
		else //xoa vt k!=1
		{
			while (p != NULL && i != k - 1)
			{
				p = p->next;
				i++;
			}
			p->next = p->next->next; //cho p tro sang node ke tiep vt k
		}
	}
}
void search_even(List l) //ham tim so chan 
{
	int i = 0;
	for (Node* p = l.head; p != NULL; p = p->next)
	{
		if (p->data % 2 == 0)
		{
			cout << p->data << " ";
		}
	}
}

int prime(int n) //ham kt so ng to
{
	if (n < 2)
	{
		return 0;
	}
	for (int i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}
int counting_primes(List l) //ham dem so ng to 
{
	int count = 0;
	for (Node* p = l.head; p != NULL; p = p->next)
	{
		if (prime(p->data))
		{
			count++;
		}
	}
	return count;
}

int perfect_square(int n)//ham so chih phuong
{
	if (sqrt(n) == (int)sqrt(n))
	{
		return 1;
	}
	return 0;
}
int sum_perfect(List l)
{
	int sum = 0;
	for (Node* p = l.head; p; p = p->next)
	{
		if (perfect_square(p->data))
		{
			sum += p->data;
		}
	}
	return sum;
}
int search_min(List l) //ham tim so nho nhat
{
	Node* p = l.head;
	int min = p->data;
	for (p = p->next; p; p = p->next)
	{
		if (min > p->data)
		{
			min = p->data;
		}
	}
	return min;
}
int search_max(List l)
{
	Node* p = l.head;
	int max = p->data;
	for (p = p->next; p; p = p->next)
	{
		if (max < p->data)
		{
			max = p->data;
		}
	}
	return max;
}
void delete_list(List& l)
{
	Node* p;
	for (p = l.head; p != NULL; p = p->next)
	{
		delete_head(l);
		p = l.head;
	}
	l.head = l.tail = NULL;
}
//void read_file(List& l, char filename[])
//{
//	ofstream f;
//	f.open(filename, ios::out);
//	if (!f)
//	{
//		cout << "loi doc file ";
//	}
//	else
//	{
//		int n, x;
//		f << n << "\n";
//		for (int i = 0; i < n; i++)
//		{
//			f << x << "\n";
//			insert_tail(l, create_node(x));
//		}
//	}
//}
//void rf(List& l, char filename[])
//{
//	FILE* f = fopen(filename, "rt");
//	if (!f)
//	{
//			cout << "loi doc file ";
//	}
//	else
//	{
//		int n, x;
//		fscanf(f, "%d", &n);
//		for (int i = 0; i < n; i++)
//		{
//			fscanf(f, "%d", &x);
//			insert_tail(l, create_node(x));
//		}
//	}
//}
void delete_node_after(List& l, Node* q) //xoa 1 node nam sau node q
{
	if (l.head == NULL)
	{
		return;
	}
	for (Node* k = l.head; k != NULL; k = k->next)
	{
		if (k->data == q->data)
		{
			Node* g = k->next; //node g chinh la node nam sau node k(nam sau node q)
			k->next = g->next; //cap nhat moi lk gia node k(node q) voi node sau node g
			delete g; //xoa node nam sau node q
			return; //xoa xong thi dung 
		}
	}
}
void add_node_after(List& l, Node* p) //them node p vao sau node q
{
	int a;
	cout << "nhap gia tri node q : ";
	cin >> a;
	Node* q = create_node(a);

	//neu danh sach chi co 1 ptu va ptu do cung chinh la node q =>bai toan tro thanh them vao cuoi ds
	if (q->data == l.head->data && l.head->next == NULL)
	{
		insert_tail(l, p);
	}
	else
	{
		//duyet tu dau ds den cuoi ds de tim node q
		for (Node* k = l.head; k != NULL; k = k->next)
		{
			if (q->data == k->data)
			{
				Node* h = create_node(p->data); //khoi tao node h de them vao sau node q
				Node* g = k->next; //cho node g tro den node nam sau node q
				h->next = g; //tao moi lk tu node p den node h <=> cug chinh la tao moi lk tu node h den node nam sau node q
				k->next = h; //tao moi lk tu node q den node h <=> chinh la node k den node h

			}
		}
	}
}
void add_node_before(List& l, Node* p) //them node p truoc node q
{
	int x;
	cout << "nhap gia tri node q :";
	cin >> x;
	Node* q = create_node(x);
	if (q->data == l.head->data && l.head->next == NULL)
	{
		insert_head(l, p);
	}
	else
	{
		Node* g = new Node;
		for (Node* k = l.head; k != NULL; k = k->next)
		{
			if (q->data == k->data)
			{
				Node* h = create_node(p->data);
				h->next = k;
				g->next = h;
			}
			g = k; //g giu lien ket cho cac node nam trc node q
		}
	}
}
void add_node_any(List& l, Node* p, int location) //them 1 node vao vi tri bat ki
{
	int n = 0;
	for (Node* k = l.head; k != NULL; k = k->next)
	{
		n++;
	}
	if (l.head == NULL || location == 1)
	{
		insert_head(l, p);
	}
	else if (location == n + 1)
	{
		insert_tail(l, p);
	}
	else
	{
		int result = 0;
		Node* g = new Node;
		for (Node* k = l.head; k != NULL; k = k->next)
		{
			result++;
			if (result==location)
			{
				Node* h = create_node(p->data);
				h->next = k;
				g->next = h;
			}
			g = k; //g giu lien ket cho cac node nam trc node q
		}
	}
}
void delete_any(List& l, int x)
{
	if (l.head == NULL) //neu ds rong thi return 
	{
		return;
	}
	if (l.head->data==x)
	{
		delete_head(l);
		return;
	}
	if (l.tail->data==x)
	{
		delete_tail(l);
		return;
	}
	Node* g = new Node;
	for (Node* k = l.head; k != NULL; k = k->next)
	{
		if (k->data == x)
		{
			g->next = k->next; //cap nhat lai node moi
			delete k; //xoa node nam sau node k
			return;
		}
		g = k; //cho node g tro den node k 
	}
}
//============================================
int dem(List& l)
{
	int i = 0;
	while (l.head != NULL) {
		i++;
		l.head = l.head->next;
	}
	return i;
}
void addAfter(List& l, Node* p, Node* newNode)
{
	if (p != NULL)
		if (p != l.tail)
		{
			newNode->next = p->next;
			p->next = newNode;
		}
		else
			insert_tail(l, newNode);
	else
		insert_head(l, newNode);
}
//==========================================

int main()
{
	List l;
	int n, x, select;
	Node* p, * q;
	inint_list(l);
	cout << "==============MENU==============" << endl;
	cout << "1. them gia tri dau " << endl;
	cout << "2. them gia tri sau " << endl;
	cout << "3. them gia tri q vao trc p " << endl;
	cout << "4. them gia tri q vao sau p " << endl;
	cout << "5. tim gia tri x " << endl;
	cout << "6. tim so chan " << endl;
	cout << "7. dem so ng to " << endl;
	cout << "8. tong so chinh phuong " << endl;
	cout << "9. tim min va max " << endl;
	cout << "10. xoa ptu cuoi " << endl;
	cout << "11. xoa ptu dau " << endl;
	cout << "12. xoa ptu sau " << endl;
	cout << "13. xoa ptu truoc " << endl;
	cout << "14. xoa toan bo ds " << endl;
	cout << "15. them node p sau node q " << endl;
	cout << "16. them node p truoc node q " << endl;
	cout << "17. xoa 1 node nam sau node q " << endl;
	cout << "18. them ptu vao vi tri bat ki " << endl;
	cout << "19. xoa ptu bat ki truoc khoa k " << endl;
	cout << "=================================" << endl;
	cout << "moi ban chon bai : ";
	cin >> select;
	cout << "nhap so ptu : ";
	cin >> n;
	create_list(l, n);
	switch (select)
	{
	case 1: 
		cout << "nhap gia tri can them dau : ";
		cin >> x;
		p = create_node(x);
		insert_head(l, p);
		cout << "gia tri cua dslk : ";
		show_list(l);
		break;
	case 2:
		cout << "nhap gia tri can them sau : ";
		cin >> x;
		p = create_node(x);
		insert_tail(l, p);
		cout << "gia tri cua dslk : ";
		show_list(l);
		break;
		/*case 3: cout << "nhap gia tri can them truoc : ";
			cin >> x;
			p = create_node(x);
			cout << "nhap gia tri nut q : ";
			cin >> x;
			q = search(l, x);
			insert_before(l, p,q);
			cout << "gia tri cua dslk : ";
			show_list(l);
			break;*/
	case 4:
		cout << "nhap gia tri can them sau : ";
		cin >> x;
		p = create_node(x);
		cout << "nhap gia tri nut q : ";
		cin >> x;
		q = search(l, x);
		insert_after(l, q, p);
		cout << "gia tri cua dslk : ";
		show_list(l);
		break;
	case 5: 
		cout << "nhap ptu can tim : ";
		cin >> x;
		cout << "gia tri cua dslk : ";
		show_list(l);
		cout << endl;
		p = search(l, x);
		if (p)
		{
			cout << "tim thay ptu ";
		}
		else
		{
			cout << "khong tim thay ptu ";
		}
		break;
	case 6: 
		cout << "gia tri cua dslk : ";
		show_list(l);
		cout << endl;
		cout << "tim thay so chan : ";
		search_even(l);
		break;
	case 7: 
		cout << "co " << counting_primes(l) << " so nguyen to trong ds ";
		break;
	case 8: 
		cout << "tong so chinh phuong : " << sum_perfect(l);
		break;
	case 9: 
		cout << "so lon nhat trong ds : " << search_max(l) << endl;
		cout << "so nho nhat trong ds : " << search_min(l);
		break;
	case 10: 
		delete_tail(l);
		cout << "ds sau khi xoa ptu cuoi : ";
		show_list(l);
		break;
	case 11: 
		delete_head(l);
		cout << "ds sau khi xoa ptu dau : ";
		show_list(l);
		break;
	case 12:
		cout << "nhap ptu xoa sau : ";
		cin >> x;
		q = create_node(x);
		delete_after(l, q);
		cout << "ds sau khi xoa ptu sau : ";
		show_list(l);
		break;
	case 13:
		cout << "nhap ptu xoa truoc : ";
		cin >> x;
		q = create_node(x);
		delete_before(l, q);
		cout << "ds sau khi xoa ptu truoc : ";
		show_list(l);
		break;
	case 14: 
		delete_list(l);
		show_list(l);
		break;
	case 15:
	{
		int b;
		cout << "nhap gia tri node p can them vao sau : ";
		cin >> b;
		Node* p = create_node(b);
		add_node_after(l, p);
		show_list(l);
		break;
	}
	case 16:
	{
		int a;
		cout << "nhap gia tri node p can them vao truoc : ";
		cin >> a;
		Node* p = create_node(a);
		add_node_before(l, p);
		show_list(l);
		break;
	}
	case 17:
	{
		int c;
		cout << "nhap nut can xoa : ";
		cin >> c;
		Node* q = create_node(c);
		delete_node_after(l, q);
		show_list(l);
		break;
	}
	case 18:
		int location,x;
		cout << "nhap gia tri node p : ";
		cin >> x;
		p = create_node(x);
		do
		{
			cout << "nhap gia tri can them node p : ";
			cin >> location;
			if (location<1 || location>n + 1)
			{
				cout << "vi tri can them phai nam trong doan [1 ; " << n + 1;
				system("pause");
			}
		} while (location<1 || location>n + 1);
		add_node_any(l, p, location);
		cout << "dslk sau khi them : ";
		show_list(l);
		break;
	case 19:
		cout << "nhap ptu can xoa : ";
		cin >> x;
		delete_any(l, x);
		cout << "ds sau khi xoa ptu : ";
		show_list(l);
		break;
	//con ham delete_k,delete_k,search_x, search,insert_before
	default:cout << "bn nhap sai cu phap. Vui long nhap lai ";
		break;

	}
}