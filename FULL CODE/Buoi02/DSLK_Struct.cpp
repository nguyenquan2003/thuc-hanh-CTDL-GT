#include "BaiHat.h"

struct Node
{
	BaiHat info;
	Node* next;
};
struct List
{
	Node* head;
	Node* tail;
};

//CAC THAO THAC CO BAN
//khoi tao
void init(List& list)
{
	list.head = list.tail = NULL;
}
//kiem tra rong
bool isEmpty(List list)
{
	return list.head == NULL;
}
//cap phat mot node moi
Node* createNode(BaiHat x)
{
	Node* p = new Node;
	if (p != NULL) {
		p->info = x;
		p->next = NULL;
	}
	return p;
}
//dem so luong phan tu cua ds
int count(List list)
{
	int dem = 0;
	Node* p = list.head;
	while (p != NULL)
	{
		dem++;
		p = p->next;
	}
	return dem;
}
//them dau
void addHead(List& list, Node* p)
{
	if (p == NULL) return;

	if (isEmpty(list))
	{
		list.head = list.tail = p;
	}
	else
	{
		p->next = list.head;
		list.head = p;
	}
}
//them node p vao cuoi ds
void addTail(List& list, Node* p)
{
	if (p == NULL) return;

	if (isEmpty(list))
	{
		list.head = list.tail = p;
	}
	else
	{
		list.tail->next = p;
		list.tail = p;
	}
}
//them node p sau node q
void addAfter(List& list, Node* q, Node* p)
{
	if (isEmpty(list) || q == NULL || p == NULL) return;
	else
	{
		p->next = q->next;
		q->next = p;

		if (list.tail == q)
			list.tail = p;
	}
}
//them bai hat vao node
void addNodeAtKth(List& list, BaiHat x, int k)
{
	int n = count(list); //sl pt list
	if (k < 0 || k > n)
	{
		printf("Vi tri them khong hop le!\n");
	}
	else
	{
		Node* p = createNode(x);
		if (k == 0)
		{
			addHead(list, p);
		}
		else
		{
			//tim node vi tri k -1
			int i = 0;
			Node* q = list.head;
			while (i < k - 1)
			{
				q = q->next;
				i++;
			}
			//i = k -1, q = node thu k-1

			addAfter(list, q, p);
		}

	}
}
//xoa dau
void removeHead(List& list)
{
	if (isEmpty(list)) return;
	else
	{
		Node* p = list.head;
		list.head = p->next;

		if (list.head == NULL)
			list.tail = NULL;

		delete p;
	}
}
//xoa node p sau q
void removeAfter(List& list, Node* q)
{
	if (isEmpty(list) || q == NULL || q->next == NULL)
		return;
	else
	{
		Node* p = q->next;
		q->next = p->next;

		if (list.tail == p)
			list.tail = q;

		delete p;
	}
}
//xoa node o vi tri k
void removeNodeAtKth(List& list, int k)
{
	int n = count(list); //sl pt list
	if (k < 0 || k > n - 1)
	{
		printf("Vi tri them khong hop le!\n");
	}
	else
	{
		if (k == 0)
		{
			removeHead(list);
		}
		else
		{
			//tim node thu k -1
			int i = 0;
			Node* q = list.head;
			while (i < k - 1)
			{
				q = q->next;
				i++;
			}

			//i = k-1, q la node thu k-1
			removeAfter(list, q);
		}
	}
}
//xoa bai hat theo ten
void removeBHTheoTen(List& list, char *tenBH)
{
	if (isEmpty(list)) return;
	else
	{
		if (strcmp(list.head->info.tenBH, tenBH)==0)
			removeHead(list);
		else
		{
			Node* q = list.head; //gia tri q khac x
			while (q->next != NULL)
			{
				if (strcmp(q->next->info.tenBH,tenBH) ==0) //q->next la phan tu can xoa
				{
					removeAfter(list, q);
					break;
				}
				q = q->next;
			}

		}
	}
}
void printNode(Node* p)
{
	xuatBH(p->info);
}
//duyet
void traverse(List list)
{
	xuatTieuDe();
	Node* p = list.head;
	while (p != NULL)
	{
		//xu ly p
		printNode(p);

		//cap nhat lai p
		p = p->next;
	}
	printf("-Het-\n");
}
//huy danh sach
void removeList(List& list)
{
	while (!isEmpty(list))
	{
		removeHead(list);
	}
}

//doc file ko co so luong n
void readFile(List& list, char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if (fp != NULL)
	{
		BaiHat x;
		while (fscanf(fp, "%s%s%s%d", &x.tenBH,&x.tenTG,&x.tenCS, &x.thoiLuong) == 4)
		{
			//Them x vao dslk
			Node* p = createNode(x);
			addTail(list, p);
		}

		fclose(fp);
	}
}

int tongThoiLuongNghePlayist(List list)
{
	int tong = 0;
	Node* p = list.head;
	while (p != NULL)
	{
		tong += p->info.thoiLuong;
		p = p->next;
	}
	return tong;
}
void writeFile(List& list, char* fileName)
{
	FILE* fp = fopen(fileName, "wt");
	if (fp != NULL)
	{
		Node* p = list.head;
		while (p != NULL)
		{
			fprintf(fp, "%s ", p->info.tenBH);
			fprintf(fp, "%s ", p->info.tenTG);
			fprintf(fp, "%s ", p->info.tenCS);
			fprintf(fp, "%d\n", p->info.thoiLuong);
			p = p->next;
		}

		fclose(fp);
	}
}


void addBaiHatDauDanhSach(List& list, BaiHat x)
{
	Node*p = createNode(x);
	addHead(list, p);
}

void swap(BaiHat& a, BaiHat& b)
{
	BaiHat t = a;
	a = b;
	b = t;
}
void sapXepTheoTenCS_Giam(List& list)
{
	for (Node* q = list.head; q != list.tail; q = q->next)
	{
		for (Node* p = q->next; p != NULL; p = p->next)
		{
			if (strcmp(q->info.tenCS, p->info.tenCS) < 0)
				swap(q->info, p->info);
		}
	}
}
void sapXepTheoTenBH_Tang(List& list)
{
	for (Node* q = list.head; q != list.tail; q = q->next)
	{
		for (Node* p = q->next; p != NULL; p = p->next)
		{
			if (strcmp(q->info.tenBH, p->info.tenBH) > 0)
				swap(q->info, p->info);
		}
	}
}
//tim node theo ten bh
Node* findNode(List list, char* tenBH)
{
	Node* p = list.head;
	while (p != NULL)
	{
		if (strcmp(p->info.tenBH, tenBH) == 0)
			return p;

		//cap nhat lai p
		p = p->next;
	}
	return NULL;
}

void duaBHLenDauDS(List& list, char* tenBH)
{
	Node* p = list.head;
	while (p != NULL)
	{
		if (strcmp(p->info.tenBH, tenBH) == 0)
		{
			swap(p->info, list.head->info);
			break;
		}

		//cap nhat lai p
		p = p->next;
	}
}

void menu()
{
	printf("\n --- ");
	printf("\nCHUC NANG: ");
	printf("\n0.Thoat");
	printf("\n1.Doc file");
	printf("\n2.Ghi file");
	printf("\n3.Them phan tu o vi tri k");
	printf("\n4.Xoa phan tu o vi tri k");
	printf("\n5.Xoa phan tu co gia tri x (pt x dau)");
	printf("\n6.Tim kiem phan tu co gia tri x");
	printf("\n7.Sap xep theo ten bai hat (tang)");
	printf("\n8.Sap xep theo ten ca si (giam)");
	printf("\n9.Dua mot bai hat len dau");
	printf("\n10.Tong thoi luong cua ds");

}

void main()
{
	List list;
	init(list);
	int chon = 0;
	do
	{
		system("cls");
		printf("DS hien tai: \n");
		traverse(list);

		menu();
		printf("\nLua chon: ");
		scanf("%d", &chon);

		switch (chon)
		{
		case 0:
		{

				  break;
		}
		case 1:
		{
				  readFile(list, "data.txt");
				  printf("Doc file thanh cong!");

				  break;
		}
		case 2:
		{
				  writeFile(list, "data_out.txt");
				  break;
		}
		case 3:
		{
				  int k;
				  printf("Nhap vi tri k can them: ");
				  scanf("%d", &k);
				  BaiHat x;
				  printf("Nhap bai hat can them: \n");
				  nhapBH(x);
				 
				  addNodeAtKth(list, x, k);
				  
				  break;
		}
		case 4:
		{
				  int k;
				  printf("Nhap vi tri k can xoa: ");
				  scanf("%d", &k);
				  removeNodeAtKth(list, k);
				  break;
		}
		case 5:
		{
				  char ten[40];
				  printf("Nhap ten bai hat can xoa: ");
				  scanf("%s", &ten);

				  removeBHTheoTen(list, ten);
				  break;
		}
		case 6:
		{
				  char ten[40];
				  printf("Nhap ten bai hat can tim: ");
				  scanf("%s", &ten);
				  Node* p = findNode(list, ten);
				  if (p != NULL)
				  {
					  printf("Da Tim thay!\n");
					  printf("Thong tin chi tiet: \n");
					  xuatBH(p->info);
				  }
				  else
				  {
					  printf("Khong tim thay!\n");
				  }
				  break;
		}
		case 7:
		{
				  sapXepTheoTenBH_Tang(list);
				  printf("Da sap xep thanh cong!\n");
				  break;
		}
		case 8:
		{
				  sapXepTheoTenCS_Giam(list);
				  printf("Da sap xep thanh cong!\n");
				  break;
		}
		case 9:
		{
				  char ten[40];
				  printf("Nhap ten bai hat can dua len dau ds: ");
				  scanf("%s", &ten);
				  duaBHLenDauDS(list, ten);
				 printf("Da dua bai hat len thanh cong!\n");
				  break;
		}
		case 10:
		{
				  int tong = tongThoiLuongNghePlayist(list);
				  printf("Thoi luong nghe het playlist: %ds", tong);
				  break;
		}

		default:
			break;
		}
		system("pause");
	} while (chon != 0);


}


