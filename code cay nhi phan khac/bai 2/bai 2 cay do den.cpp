#define _CRT_SECURE_NO_WARNINGS
#include"stdio.h"
#include"conio.h"
#include"string"
#include"Windows.h"
#include"math.h"
enum EColor { RED, BLACK };

struct MH
{
	char ma[11]; //ma mon hoc
	char ten[31]; //ten mh
	int soTC; // so tin chi
	char loai[21]; //loai hoc phan
};

struct BRTNode
{
	MH Info;
	EColor Color;
	BRTNode* Left;
	BRTNode* Right;
	BRTNode* Parent;
};

struct BRTree
{
	BRTNode* root;
};

void init(BRTree& rbt)
{
	rbt.root = NULL;
}
BRTNode* createBRTNode(MH x)
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
	if (p->Info.ma < root->Info.ma)
	{
		root->Left = Insert(root->Left, p);
		root->Left->Parent = root;
	}
	else if (p->Info.ma > root->Info.ma)
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
void swapInfos(MH& info1, MH& info2) {
	MH temp = info1;
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

void BRTInsert(BRTNode*& root, MH Info)
{
	BRTNode* pNew = createBRTNode(Info);

	/* Thực hiện chèn như bình thường */
	root = Insert(root, pNew);

	/* Sửa lại lỗi của quy tắc cây đỏ đen */
	fixViolation(root, pNew);
}

bool doc1MH(FILE* fp, MH& x)
{
	return fscanf(fp, "%[^#]#%[^#]#%d#%[^\n]\n", x.ma, x.ten, &x.soTC, x.loai) == 4;
}



void nhapTuFile(BRTree& rbt, char tenfile[])
{
	FILE* fp = fopen(tenfile, "rt");
	if (fp == NULL)
		return;
	else
	{
		int n;
		fscanf(fp, "%d\n", &n);
		for (int i = 0; i < n; i++)
		{
			MH x;
			doc1MH(fp, x);
			//BRTNode* p = createBRTNode(x);
			BRTInsert(rbt.root, x);
		}
	}

	fclose(fp);
}

void xuat1MH(MH x)
{
	printf("%-10s%-35s%-20d%-20s\n", x.ma, x.ten, x.soTC, x.loai);
}

void xuatTD()
{
	printf("%-10s%-35s%-20s%-20s\n", "Ma", "Ten mon hoc", "So tin chi", "Loai");
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

	xuat1MH(p->Info);
	//Light Yellow=14 (E), Green=2
	set_Color(0, 7);
}
void showBRTree_InOrder(BRTNode* root)
{
	if (root == NULL) return;

	showBRTree_InOrder(root->Left);
	showBRTNode(root);
	showBRTree_InOrder(root->Right);
}
#endif





//####################################################################################################################
//####################################################################################################################
//####################################################################################################################


//==============ham check============//

/* Kiểm tra xem node hiện tại có phải là node con trái của node cha không */
bool isOnLeft(BRTNode* p)
{
	return p == p->Parent->Left;
}

/* Kiểm tra có node hiện tại có node con là nút đỏ hay không */
bool hasRedChild(BRTNode* p) {
	return (p->Left != NULL && p->Left->Color == RED) ||
		(p->Right != NULL && p->Right->Color == RED);
}
//======================================//





//=============DELETE===========//

/* Tìm nút không có nút con bên trái trong cây con của nút đã cho */
BRTNode* findSuccessor(BRTNode* p) 
{
	BRTNode* temp = p;

	while (temp->Left != NULL)
		temp = temp->Left;

	return temp;
}

/* Tìm nút thay thế nút đã xóa trong BST */
BRTNode* BSTReplace(BRTNode* p) 
{
	// Khi nút có 2 con
	if (p->Left != NULL && p->Right != NULL)
		return findSuccessor(p->Right);

	// Khi node lá 
	if (p->Left == NULL && p->Right == NULL)
		return NULL;

	// Khi node có một con
	if (p->Left != NULL)
		return p->Left;
	else
		return p->Right;
}




/* Trả về con trỏ cho node anh chị em */
BRTNode* findSibling(BRTNode* p) 
{
	// node anh rỗng nếu không tồn tại node cha 
	if (p->Parent == NULL)
		return NULL;

	if (isOnLeft(p))
		return p->Parent->Right;
	else
		return p->Parent->Left;
}

void fixDoubleBlack(BRTNode*& root, BRTNode* p) {
	// p là node gốc thì return
	if (p == root) return;

	BRTNode* pSibling = findSibling(p);
	BRTNode* pParent = p->Parent;
	if (pSibling == NULL) {
		// Không có sibiling, màu đen kép được đẩy lên 
		fixDoubleBlack(root, pParent);
	}
	else {
		if (pSibling->Color == RED) {
			// Anh chị em màu đỏ 
			pParent->Color = RED;
			pSibling->Color = BLACK;
			if (isOnLeft(pSibling)) {
				// trường hợp left 
				rotateRight(root, pParent);
			}
			else {
				// trường hợp right 
				rotateLeft(root, pParent);
			}
			fixDoubleBlack(root, p);
		}
		else {
			// Anh chị em đen 
			if (hasRedChild(pSibling)) {
				// Ist nhất 1 trẻ em màu đỏ 
				if (pSibling->Left != NULL && pSibling->Left->Color == RED) {
					if (isOnLeft(pSibling)) {
						// left left 
						pSibling->Left->Color = pSibling->Color;
						pSibling->Color = pParent->Color;
						rotateRight(root, pParent);
					}
					else {
						// right left 
						pSibling->Left->Color = pParent->Color;
						rotateRight(root, pSibling);
						rotateLeft(root, pParent);
					}
				}
				else {
					if (isOnLeft(pSibling)) {
						// left right 
						pSibling->Right->Color = pParent->Color;
						rotateLeft(root, pSibling);
						rotateRight(root, pParent);
					}
					else {
						// right right 
						pSibling->Right->Color = pSibling->Color;
						pSibling->Color = pParent->Color;
						rotateLeft(root, pParent);
					}
				}
				pParent->Color = BLACK;
			}
			else {
				// Hai con đen 
				pSibling->Color = RED;
				if (pParent->Color == BLACK)
					fixDoubleBlack(root, pParent);
				else
					pParent->Color = BLACK;
			}
		}
	}
}

/* Xóa nút đã cho */
void deleteNode(BRTNode*& root, BRTNode* pDelete) {
	BRTNode* pReplace = BSTReplace(pDelete);

	// Đúng khi pReplace và pDelete đều đen
	bool flagDoubleBlack = ((pReplace == NULL || pReplace->Color == BLACK) && (pDelete->Color == BLACK));
	BRTNode* pParent = pDelete->Parent;

	if (pReplace == NULL) {
		// pReplace là NULL do đó pDelete là lá 
		if (pDelete == root) {
			// pDelete là root, làm cho root là NULL 
			root = NULL;
		}
		else {
			if (flagDoubleBlack) {
				// pReplace và pDelete đều đen
				// pDelete là lá, sửa màu đen kép tại pDelete 
				fixDoubleBlack(root, pDelete);
			}
			else {
				// pReplace hoặc pDelete là đỏ
				if (findSibling(pDelete) != NULL)
					// node anh chị em không rỗng, làm cho nó màu đỏ 
					findSibling(pDelete)->Color = RED;
			}

			// Xóa pDelete khỏi cây 
			if (isOnLeft(pDelete)) {
				pParent->Left = NULL;
			}
			else {
				pParent->Right = NULL;
			}
		}
		delete pDelete;
		return;
	}

	if (pDelete->Left == NULL || pDelete->Right == NULL) {
		// pDelete có 1 node con
		if (pDelete == root) {
			// pDelete là gốc, gán giá trị của pReplace cho pDelete và xóa pReplace 
			pDelete->Info = pReplace->Info;
			pDelete->Left = pDelete->Right = NULL;
			delete pReplace;
		}
		else {
			// Tách node pDelete khỏi cây và di chuyển node pReplace lên
			if (isOnLeft(pDelete)) {
				pParent->Left = pReplace;
			}
			else {
				pParent->Right = pReplace;
			}
			delete pDelete;
			pReplace->Parent = pParent;
			if (flagDoubleBlack) {
				// pReplace và pDelete đều đen, sửa hai màu đen ở pReplace 
				fixDoubleBlack(root, pReplace);
			}
			else {
				// pReplace hoặc pDelete đỏ, màu pReplace đen 
				pReplace->Color = BLACK;
			}
		}
		return;
	}

	// pDelete có 2 con, hoán đổi giá trị với nút kế nhiệm (thế mạng) và đệ quy 
	swapInfos(pReplace->Info, pDelete->Info);
	deleteNode(root, pReplace);
}



//search theo so TC
BRTNode* find_1TC(BRTNode* root)
{
	if (root == NULL) return NULL;

	if ((root->Info.soTC == 1) != NULL)
		return root;
	BRTNode* p = find_1TC(root->Left);

	if (p != NULL)
		return p;

	return find_1TC(root->Right);
}


//####################################################################################################################
//####################################################################################################################
//####################################################################################################################


//================================================================================//

//cau 2
void xuat_TH(BRTNode* p)
{
	if (p == NULL) return;
	xuat_TH(p->Left);
	if (strcmp(p->Info.loai, "Thuc hanh") == 0)
		showBRTNode(p);
	xuat_TH(p->Right);
}




//search theo ma mon hoc
BRTNode* find_ma2(BRTNode* p, char x[])
{
	if (p == NULL) return NULL;
	if (strcmp(x, p->Info.ma) == 0)
		return p;
	BRTNode* q = find_ma2(p->Left, x);
	if (q != NULL)
		return q;
	return find_ma2(p->Right, x);
}



//cau 4
void del_TC(BRTNode*& root) 
{
	// BRTree là rỗng 
	if (root == NULL) return;

	BRTNode* delete_pt = find_1TC(root);

	if (delete_pt == NULL) {
		return;
	}
	deleteNode(root, delete_pt);
	del_TC(root->Left);
	del_TC(root->Right);
}




void menu()
{
	printf("\n\n\n===================MENU=====================");
	printf("\n0.Thoat");
	printf("\n1.Nhap tu file");
	printf("\n2.In ra man hinh cac mon hoc <<Thuc hanh>>");
	printf("\n3.Xuat thong tin mon hoc co ma x");
	printf("\n4.Xoa mon hoc co tin chi bang 1");
	printf("\n");
	printf("\n");

}
void main()
{
	BRTree rbt;
	BRTNode* p = new BRTNode;
	init(rbt);
	int chon = 0;
	do
	{
		system("cls");
		printf("Danh sach mon hoc :\n");
		xuatTD();
		showBRTree_InOrder(rbt.root);
		menu();
		printf("Nhap lua chon: ");
		scanf("%d", &chon);
		char file[100] = "dsMH.txt";
		switch (chon)
		{
		case 0: break;
		case 1:
		{
			nhapTuFile(rbt, file);
			break;
		}
		case 2:
		{
			xuatTD();
			xuat_TH(rbt.root);
			break;
		}
		case 3:
		{
			char x[11];
			printf("Nhap ma muon tim: ");
			rewind(stdin);
			gets_s(x);
			BRTNode* q= find_ma2(rbt.root, x);
			if (q == NULL)
				printf("Khong tim thay mon hoc co ma %s\n", x);
			else
			{
				printf("Tim thay:\n");
				xuatTD();
				xuat1MH(q->Info);
			}
			break;
		}
		case 4:
		{
			del_TC(rbt.root);
			break;
		}
		default:
			break;
		}
		printf("\n");
		system("pause");


	} while (chon!=0);
}