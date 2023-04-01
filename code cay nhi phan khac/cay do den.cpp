#define _CRT_SECURE_NO_WARNINGS
#include"stdio.h"
#include"conio.h"
#include"string"
#include"Windows.h"
#include"math.h"
enum EColor { RED, BLACK };

struct VeXP
{
	int mave;
	char tenp[50];
	int dau;
	int cuoi;
	char pchieu[30];
};

struct BRTNode
{
	VeXP Info;
	EColor Color;
	BRTNode* Left;
	BRTNode* Right;
	BRTNode* Parent;
};

struct BRTree
{
	BRTNode* root;
};

BRTNode* createBRTNode(VeXP x)
{
	BRTNode* p = new BRTNode;
	if (p == NULL)
	{
		printf("\nKhong the cap phat nut moi!");
		_getch();
		return NULL;
	}
	p->Info = x; // Gán dữ liệu mới cho nút
	p->Color = RED; // Gán màu đỏ (Red) mặc định
	p->Left = NULL; // Chưa có nút con trái
	p->Right = NULL; // Chưa có nút con phải
	p->Parent = NULL; // Chưa có nút cha
	return p;
}

BRTNode* Insert(BRTNode* root, BRTNode* p)////////////////////////////////////////////////////
{
	/* Nếu cây trống thì trả về một BRTNode mới */
	if (root == NULL) return p;

	/* Nếu không thì tiếp tục duyệt xuống dưới cây */
	if (p->Info.mave < root->Info.mave)
	{
		root->Left = Insert(root->Left, p);
		root->Left->Parent = root;
	}
	else if (p->Info.mave > root->Info.mave)
	{
		root->Right = Insert(root->Right, p);
		root->Right->Parent = root;
	}
	/* Trả về con trỏ BRTNode */
	return root;
}

#ifndef HieuChinh 
void rotateLeft(BRTNode*& root, BRTNode*& p)
{
	BRTNode* pRight = p->Right;
	p->Right = pRight->Left;
	if (p->Right != NULL)
		p->Right->Parent = p;
	pRight->Parent = p->Parent;
	if (p->Parent == NULL)
		root = pRight;
	else if (p == p->Parent->Left)
		p->Parent->Left = pRight;
	else
		p->Parent->Right = pRight;
	pRight->Left = p;
	p->Parent = pRight;
}
void rotateRight(BRTNode*& root, BRTNode*& p)
{
	BRTNode* pLeft = p->Left;
	p->Left = pLeft->Right;
	if (p->Left != NULL)
		p->Left->Parent = p;
	pLeft->Parent = p->Parent;
	if (p->Parent == NULL)
		root = pLeft;
	else if (p == p->Parent->Left)
		p->Parent->Left = pLeft;
	else
		p->Parent->Right = pLeft;
	pLeft->Right = p;
	p->Parent = pLeft;
}
void swapColors(EColor& color1, EColor& color2) {
	EColor temp = color1;
	color1 = color2;
	color2 = temp;
}
void swapInfos(int& info1, int& info2) {
	int temp = info1;
	info1 = info2;
	info2 = temp;
}
void fixViolation(BRTNode*& root, BRTNode*& pt)
{
	BRTNode* pParent = NULL;
	BRTNode* pGrandParent = NULL;

	if (!pt || !pt->Parent) return; //Nút rỗng thì dừng

	while ((pt != root) && (pt->Color != BLACK) && (pt->Parent->Color == RED))
	{
		pParent = pt->Parent;
		pGrandParent = pt->Parent->Parent; //Nút ông

		if (!pGrandParent) break; //Nút ông bị rỗng

		/* Trường hợp A:
		node cha của pt là con trái của node ông của pt */
		if (pParent == pGrandParent->Left)
		{
			BRTNode* pUncle = pGrandParent->Right;

			/* Trường hợp: 1
			node chú của pt là node đỏ khi này chỉ cần đổi màu cho node đó thành đen */
			if (pUncle != NULL && pUncle->Color == RED)
			{
				pGrandParent->Color = RED;
				pParent->Color = BLACK;
				pUncle->Color = BLACK;
				pt = pGrandParent;
			}

			else
			{
				/* Trường hợp: 2
				pt là node con phải của node cha nó ta thực hiện xoay trái */
				if (pt == pParent->Right)
				{
					rotateLeft(root, pParent);
					pt = pParent;
					pParent = pt->Parent;
				}

				/* Trường hợp: 3
				pt là con trái của node cha nó ta thực hiện xoay phải */
				rotateRight(root, pGrandParent);
				swapColors(pParent->Color, pGrandParent->Color);
				pt = pParent;
			}
		}

		/* Trường hợp: B
		node cha của pt là con phải của node cha của pt */
		else
		{
			BRTNode* pUncle = pGrandParent->Left;

			/* Trường hợp: 1
			node chú của pt là node đỏ khi này chỉ cần đổi màu cho node đó thành đen */
			if ((pUncle != NULL) && (pUncle->Color == RED))
			{
				pGrandParent->Color = RED;
				pParent->Color = BLACK;
				pUncle->Color = BLACK;
				pt = pGrandParent;
			}
			else
			{
				/* Trường hợp: 2
				pt là con trái của node cha nó ta thực hiện xoay phải */
				if (pt == pParent->Left)
				{
					rotateRight(root, pParent);
					pt = pParent;
					pParent = pt->Parent;
				}

				/* Trường hợp: 3
				pt là node con phải của node cha nó -> nên thực hiện xoay trái */
				rotateLeft(root, pGrandParent);
				swapColors(pParent->Color, pGrandParent->Color);
				pt = pParent;
			}
		}
	}

	root->Color = BLACK;
}
#endif

void BRTInsert(BRTNode*& root, VeXP Info)
{
	BRTNode* pNew = createBRTNode(Info);

	/* Thực hiện chèn như bình thường */
	root = Insert(root, pNew);

	/* Sửa lại lỗi của quy tắc cây đỏ đen */
	fixViolation(root, pNew);
}


void TaocayFile(BRTNode*& root, char tenfile[])
{
	FILE* f = fopen(tenfile, "r+");

	int n;
	fscanf(f, "%d", &n);

	root = NULL;

	for (int i = 0; i < n; i++)
	{
		VeXP x;
		fscanf(f, "%d#%[\^#]#%d#%d#%[\^#]#", &x.mave, &x.tenp, &x.dau, &x.cuoi, &x.pchieu);
		BRTNode* p = createBRTNode(x);
		BRTInsert(root, x);
	}
}

void In1ve(VeXP x)
{
	printf("\n%5d%30s%5d%5d%30s", x.mave, x.tenp, x.dau, x.cuoi, x.pchieu);
}


#ifndef InCay
void set_Color(int colorBackground, int colorText)
{
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, colorBackground * 16 + colorText);
	/*
	0 = Black       8 = Gray
	1 = Blue        9 = Light Blue
	2 = Green       A = Light Green
	3 = Aqua        B = Light Aqua
	4 = Red         C = Light Red
	5 = Purple      D = Light Purple
	6 = Yellow      E = Light Yellow
	7 = White       F = Bright White
	=> set_Color(X); -> X = a*16 + b, a (background) và b (character)
	*/
}
void showBRTNode(BRTNode* p)
{
	if (p->Color == RED)//Light Red=12 (C), Bright White=15 (F)
		set_Color(15, 12);
	else if (p->Color == BLACK)//Black=0, Bright White=15 (F)
		set_Color(15, 0);

	In1ve(p->Info);
	//Light Yellow=14 (E), Green=2
	set_Color(14, 2);
}
void showBRTree_InOrder(BRTNode* root)
{
	if (root == NULL) return;

	showBRTree_InOrder(root->Left);
	showBRTNode(root);
	showBRTree_InOrder(root->Right);
}
#endif

void Them1ve(BRTNode*& root, BRTNode* p)
{
	printf("\nNhap phan tu can them: ");
	printf("\nMa ve: "); scanf("%d", &p->Info.mave); 
	fflush(stdin);
	printf("\nTen Phim: "); scanf("%s",&p->Info.tenp);//gets(p->Info.tenp);
	fflush(stdin);
	printf("\Gio chieu: "); scanf("%d", &p->Info.dau);
	printf("\nKet thuc: "); scanf("%d", &p->Info.cuoi); 
	fflush(stdin);
	printf("\nPhong: "); scanf("%s", &p->Info.pchieu);//gets(p->Info.pchieu);
	BRTNode* q = createBRTNode(p->Info);
	BRTInsert(root, q->Info);
	showBRTree_InOrder(root);
}

BRTNode* TimNode_Ten(BRTNode* root, char t[50])
{
	if (root == NULL) return NULL;

	if (strstr(root->Info.tenp, t) != NULL)
		return root;
	BRTNode* p = TimNode_Ten(root->Left, t);

	if (p != NULL)
		return p;

	return TimNode_Ten(root->Right, t);
}

float Thoiluong(VeXP x)
{
	return float(x.cuoi) - float(x.dau);
}

void IncayTL(BRTNode* root)
{
	if (root == NULL) return;

	IncayTL(root->Left);
	if (Thoiluong(root->Info) > 1)
	{
		showBRTNode(root);
	}
	IncayTL(root->Right);
}

BRTNode* TimNode_MS(BRTNode* root, int ms)
{
	if (root == NULL) return NULL;

	if ((root->Info.mave == ms) != NULL)
		return root;
	BRTNode* p = TimNode_MS(root->Left, ms);

	if (p != NULL)
		return p;

	return TimNode_MS(root->Right, ms);
}

void Hieuchinh(BRTNode*& root)
{
	int k;
	printf("\nNhap ma so phim can hieu chinh thoi gian: ");
	scanf("%d", &k);
	BRTNode* MS = TimNode_MS(root, k);
	if (MS == NULL)
	{
		printf("\nKhong tim thay");
	}
	else
	{
		printf("Nhap lai thoi gian bat dau: "); scanf("%d", &MS->Info.dau);
		printf("Nhap lai thoi gian ket thuc: "); scanf("%d", &MS->Info.cuoi);
		showBRTree_InOrder(root);
	}
}

int countPhim(BRTNode* root)
{
	if (root == NULL)
		return 0;
	if (root != NULL)
	{
		int a = countPhim(root->Left);
		int b = countPhim(root->Right);
		if ((Thoiluong(root->Info) * 60) > 50)
		{
			return 1 + a + b;
		}
		return a + b;
	}
}

int Height(BRTNode* r)
{
	if (r == NULL || (r->Left == NULL && r->Right == NULL))
		return 0;
	else
	{
		int Lheight = Height(r->Left);
		int Rheight = Height(r->Right);
		return 1 + max(Lheight, Rheight);
	}
}

int countred(BRTNode* root)
{
	if (root != NULL)
	{
		int a = countred(root->Left);
		int b = countred(root->Right);
		if (root->Color == RED)
			return 1 + a + b;
		return a + b;
	}
	return 0;
}

void menu()
{
	printf("\n===========================Menu============================");
	printf("\n1.Them 1 ve");
	printf("\n2.Tim ten phim");
	printf("\n3.Phim tren 60 phut");
	printf("\n4.Chinh thoi gian phim theo ma so");
	printf("\n5.So bai hat co thoi luong tren 50 phut");
	printf("\n6.Xoa dau:");
	printf("\n7.Xoa cuoi");
	printf("\n8.Dem so not do");
	printf("\n9.Chieu cao cay");
	printf("\n0.Ket thuc");
	printf("\n===========================End=============================");
}

int main()
{
	BRTree xp;
	BRTNode* p = new BRTNode;
	char t[100] = "VXP.txt";
	TaocayFile(xp.root, t); //TaocayFile(xp.root, "VXP.txt");
	showBRTree_InOrder(xp.root);


	/*Them1ve(xp.root,p);*/

	/*char t[50];
	printf("\nNhap ten phim can tim: ");
	gets(t);
	TimNode_Ten(xp.root,t);
	BRTNode*T=TimNode_Ten(xp.root,t);
	printf("\nKet qua tim kiem: ");
	In1ve(T->Info);*/

	/*printf("\nNhung phim co thoi luong tren 60 phut");
	IncayTL(xp.root);*/

	//Hieuchinh(xp.root);
	int lc;
	int x;
	do {
		menu();
		printf("\nBan chon chuc nang nao ?\n");
		scanf("%d", &lc);
		switch (lc)
		{
		case 1:
		{
			Them1ve(xp.root,p);
		} break;
		case 2:
		{
			char s[50];
			printf("\nNhap ten phim can tim: ");
			scanf("%s",&s);
			fflush(stdin);
			TimNode_Ten(xp.root,s);
			BRTNode*T=TimNode_Ten(xp.root,s);
			printf("\nKet qua tim kiem: ");
			In1ve(T->Info);
		} break;
		case 3:
		{
			printf("\nNhung phim co thoi luong tren 60 phut");
			IncayTL(xp.root);
		} break;
		case 4:
		{
			Hieuchinh(xp.root);
		} break;
		case 5:
		{
			printf("So bai hat co thoi luong tren 50 phut: %d", countPhim(xp.root));
		} break;
		case 6:
		{
			
		} break;
		case 7:
		{
		
		} break;
		case 8:
		{
			printf("So not do la: %d", countred(xp.root));
		} break;
		case 9:
		{
			printf("Chieu cao cay: %d", Height(xp.root));
		} break;
		default:
		{
			printf("Ban nhap sai");
		} break;
		}
	} while (lc != 0);
	_getch();
}