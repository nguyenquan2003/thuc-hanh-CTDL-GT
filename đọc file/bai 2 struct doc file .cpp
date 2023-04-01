#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;
struct baihat
{
	char bai_hat[30], tac_gia[20], ca_si[20];
	int thoi_luong;
};
struct Node
{
	baihat data; //luu tt cua nut hien hanh
	Node* next; //con tro chi den nut ke sau
};
struct List
{
	Node* head, * tail; //dc dau va dc cuoi trong ds
};

Node* create_node(baihat x)
{
	Node* p = new Node;
	if (p == NULL)
	{
		cout << "khong du bo nho cap phat ";
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}
void input_music(baihat& y) //ham nhap du lieu 
{
	cout << "nhap ten bai hat : ";
	rewind(stdin);
	gets_s(y.bai_hat);

	cout << "nhap ten ca si : ";
	rewind(stdin);
	gets_s(y.ca_si);

	cout << "nhap ten tac gia : ";
	rewind(stdin);
	gets_s(y.tac_gia);

	cout << "nhap thoi luong : ";
	cin >> y.thoi_luong;
}
void show_node(Node* p) //xuat nd cua nut
{
	cout << p->data.bai_hat << " ";
	cout << p->data.ca_si << " ";
	cout << p->data.tac_gia << " ";
	cout << p->data.thoi_luong << " ";
}
void init_list(List& l) //tao list rong 
{
	l.head = l.tail = NULL;
}
int Is_Empty(List l) //kt ds rong
{
	if (l.head == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//Duyệt danh sách.
void show_list(List l)
{
	if (Is_Empty(l) == 1)
	{
		cout << "danh sach rong ";
		return;
	}
	cout<<"Noi dung cua danh sach la: "<<endl;
	for (Node* p = l.head; p != NULL; p = p->next)
	{
		show_node(p);
		cout << endl;
	}
}

//Thêm nút p có giá trị x vào đầu danh sách.
void insert_head(List& l, Node* p)
{
	if (p == NULL)
	{
		return; //Thực hiện không thành công
	}
	if (Is_Empty(l) == 1)
	{
		l.head = l.tail = p;
	}
	else
	{
		p->next = l.head;
		l.head = p;
	}
}
void insert_tail(List& l, Node* p)
{
	if (p == NULL)
	{
		return; //Thực hiện không thành công
	}
	if (Is_Empty(l) == 1)
	{
		l.head = l.tail = p;
	}
	else
	{
		l.tail->next = p;
		l.tail = p;
	}
	//Thực hiện thành công
}
//chèn new sau q
void  insert_after(List& l, Node* q, Node* p)
{
	if (q == NULL)
	{ 
		return; //Thực hiện không thành công
	}
	p->next = q->next;
	q->next = p;
	if (l.tail == q)
	{
		l.tail = p;
	}
	//return 1; //Thực hiện thành công
}
int len(List l)
{
	Node* p = l.head; //tao 1 Node P de duyet danh sach L
	int i = 0; //bien dem
	while (p != NULL) //trong khi P chua tro den NULL (cuoi danh sach thi lam)
	{
		i++; //tang bien dem
		p = p->next; //cho P tro den Node tiep theo
	}
	return i; //tra lai so Node cua0 l
}

void delete_head(List& l)
{
	if (l.head == NULL)
	{
		return;
	}
	Node* p = l.head;
	l.head = l.head->next;
	delete p;
}
void delete_tail(List& l)
{
	if (l.head == NULL)
	{ 
		return;
	}
	Node* p = l.head, * r = l.tail;
	if (p == r) //danh ssach co 1 PT
	{
		l.head = l.tail = NULL;
		delete p;
	}
	else
	{
		while (p->next != r)
		{
			p = p->next;
		}
		p->next = NULL;
		l.tail = p;
		delete r;
	}
}
void delete_after(List& l, Node* q)
{
	if (q == NULL)
	{
		cout << "khong tim thay ";
		return;
	}
	Node* p, * i;
	for (i = l.head; i != NULL; i = i->next)
	{
		if (i == q)
		{
			if (l.tail == i->next)
			{
				delete_tail(l);
				return;
			}
			else
			{
				p = i->next;
				i->next = i->next->next;
				delete p;
				return;
			}
		}
	}
}
void delete_before(List& l, Node* q)
{
	if (q == NULL)
	{
		cout << "khong tim thay ";
		return;
	}
	Node* p, * i;
	for (i = l.head; i != NULL; i = i->next)
	{
		if (i->next == q)
		{
			delete_head(l);
			return;
		}
		if (i->next->next == q)
		{
			p = i->next;
			//DelAfter(sl,i);
			//return;
			i->next = i->next->next;
			delete p;
			return;
		}
	}
}

void create_text(List& l, char* filename) //tao ds tu file text
{
	int n = 0;
	ifstream in(filename);
	init_list(l);
	if (in)
	{
		in >> n;
		for (int i = 1; i <= n; i++)
		{
			Node* p;
			baihat bh;
			in >> bh.bai_hat;
			in >> bh.ca_si;
			in >> bh.tac_gia;
			in >> bh.thoi_luong;
			p = create_node(bh);
			insert_tail(l, p);
		}
	}
	in.close();
}
//void read_file(List& l, char filename[])
//{
//	FILE* f = fopen(filename, "rt");
//	if (!f)
//		cout << "loi doc file ";
//	else
//	{
//		baihat x;
//		char b[5] = "", a[5] = "";
//		int n;
//		fscanf(f, "%[^\n]%*c", &b);
//		n = atoi(b);
//		for (int i = 0; i < n; i++)
//		{
//			fscanf(f, "%[^#]%*c%[^#]%*c%[^#]%*c%[^\n]%*c", &x.bai_hat, &x.tac_gia, &x.ca_si, &a);
//			x.thoi_luong = atoi(a);
//			insert_tail(l, create_node(x));
//		}
//	}
//	fclose(f);
//}
int search(List l, char x[]) //tim x trong danh sach
{
	Node* p = l.head;
	int i = 1;
	while (p != NULL) //duyet danh sach den khi tim thay hoac ket thuc danh sach
	{
		if (strcmpi(p->data.bai_hat, x) == 0)
		{
			break;
		}
		p = p->next;
		i++;
	}
	if (p != NULL)
	{
		return i; //tra ve vi tri tim thay
	}
	else
	{
		return 0; //khong tim thay
	}
}

void delete_k(List& l, int k) //Xoa Node k trong danh sach
{
	Node* p = l.head;
	int i = 1;
	if (k<1 || k>len(l)) 
	{ 
		cout<<"Vi tri xoa khong hop le !" ; //kiem tra dieu kien
	} 
	else
	{
		if (k == 1)
		{
			delete_head(l); //xoa vi tri dau tien
			//return;
		}
		else if (k == len(l))
		{
			delete_tail(l);
			//return;
		}
		else //xoa vi tri k != 1
		{
			while (p != NULL && i != k - 1) //duyet den vi tri k-1
			{
				p = p->next;
				i++;
			}
			//SNode *r=P->Next;
			p->next = p->next->next; //cho P tro sang Node ke tiep vi tri k
			//delete r;
			//return;
		}
	}
}

int total_duration(List l) //ham tinh tong thoi luong
{
	Node* p;
	int total = 0;
	if (l.head == NULL)
	{
		cout<<"danh sach rong ";
		return 0;
	}
	for (p = l.head; p != NULL; p = p->next)
	{
		total += p->data.thoi_luong;
	}
}

void sort_name_music(List l) //sap xep ten bai hat
{
	Node* i, * j;
	baihat temp; //bien tam thoi
	for (i = l.head; i != NULL; i = i->next)
	{
		for (j = i->next; j != NULL; j = j->next)
		{
			if (strcmp(i->data.bai_hat, j->data.bai_hat) == 1)
			{
				temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
}
void descending_sort_singer(List l) //sắp xếp ca sĩ giảm dần
{
	Node* i, * j;
	baihat temp;
	for (i = l.head; i != NULL; i = i->next)
	{
		for (j = i->next; j != NULL; j = j->next)
		{
			if (strcmp(i->data.ca_si, j->data.ca_si) == -1)
			{
				temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
}
Node* find_node(List l, char x[])
{
	if (Is_Empty(l) == 1)
	{
		return NULL;
	}
	Node* p = l.head;//aa=strupr(x),bb=strupr(p->data.bai_hat)
	while ((p != NULL) && (strcmp(p->data.bai_hat, x) != 0))
	{
		p = p->next;
	}
	return p; //có thể NULL: không tìm thấy, hoặc khác NULL: tìm thấy
}
void put_song_on_top(List& l, char x[]) //dua bai hat len dau ds
{
	Node* p, * r;
	baihat y;
	p = find_node(l, x);
	strcpy(y.bai_hat, p->data.bai_hat);
	strcpy(y.ca_si, p->data.ca_si);
	strcpy(y.tac_gia, p->data.tac_gia);
	y.thoi_luong = p->data.thoi_luong;
	r = create_node(y);
	if (p == NULL)
	{
		cout << "khong tim thay";
	}
	else
	{
		if (p == l.tail)
		{
			delete_tail(l);
		}
		else
		{
			delete_k(l, search(l, x));//xoa p
		}
		insert_head(l, r);
	}
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
int main()
{
	cout<<"************MENU*******************"<<endl;
	cout << "0. Thoat chuong trinh" << endl;
	cout << "1. Doc danh sach tu file" << endl;
	cout << "2. In Danh sách" << endl;
	cout << "3. Thoi luong nghe tat ca bai hat" << endl;
	cout << "4. Them bai hat moi vao dau Danh sach" << endl;
	cout << "5. Them bai hat moi vao cuoi Danh sach" << endl;
	cout << "6. Xoa bai hat khoi danh sach" << endl;
	cout << "7. Kiem tra bai hat X co trong danh sach" << endl;
	cout << "8. Sap xep bai hat theo thu tu ten bai hat" << endl;
	cout << "9. Sap xep bai hat theo thu tu giam dan theo ten ca si" << endl;
	cout << "10. Dua bai hat len dau danh sach" << endl;
	cout << "****************************" << endl;
	Node* p;
	int select;
	baihat y;
	char file1[] = "Data.txt";
	char file2[] = "filetext.txt";
	char x[20];
	List l;
	init_list(l);
	cout << "moi bn chon bai : ";
	cin >> select;
	switch (select)
	{
		case 1:
		{
			create_text(l, file1);
			show_list(l);
			break;
		}
		/*case 2:
		{
			docfile(sl, filename2);
			ShowSList(sl);
			break;
		}*/
		case 3:
		{
			cout << "Tong thoi luong de nghe het cac bai hat: " << total_duration(l);
			break;
		}
		case 4:
		{
			input_music(y);
			p = create_node(y);
			insert_head(l, p);
			show_list(l);
			break;
		}
		case 5:
		{
			input_music(y);
			p = create_node(y);
			insert_tail(l, p);
			show_list(l);
			break;
		}
		case 6:
		{
			cout << "nhap ten bai hat can xoa : ";
			rewind(stdin);
			gets_s(x);
			delete_k(l, search(l, x));
			show_list(l);
			break;
		}
		case 7:
		{
			cout << "nhap ten bai hat can tim : ";
			rewind(stdin);
			gets_s(x);
			int i = search(l, x);
			if (i > 0)
			{
				cout << "Tim thay bai hat tai vi tri " << i;
			}
			else
				cout << "khong tim thay";
			break;
		}
		case 8:
		{
			sort_name_music(l);
			show_list(l);
			break;
		}
		case 9:
		{
			descending_sort_singer(l);
			show_list(l);
			break;
		}
		case 10:
		{
			cout << "nhap ten bai hat can dua len dau : ";
			rewind(stdin);
			cin >> x;
			put_song_on_top(l, x);
			show_list(l);
			break;
		}
	}
}
