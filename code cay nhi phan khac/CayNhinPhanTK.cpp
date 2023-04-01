#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>

struct Node
{
	int info;
	Node* Left;
	Node* Right;
};
struct BTree
{
	Node* root;
};
Node* CreateNode(int x)
{
	Node* p = new Node;
	if (p == NULL)
		return NULL;
	p->info = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;
}
void insertNode(Node*& root, Node* p)
{
	if (root == NULL)
	{
		root = p;
		return;
	}
	if (p->info == root->info)
	{
		printf("Khong them vi tri trung khoa");
		return;
	}
	if (p->info > root->info)
		insertNode(root->Right, p);
	else
		insertNode(root->Left, p);
}
//void Tao_Cay_N_Node(Node* &root)
//{
//	int n;
//	printf("\nNhap so nut: ");
//	scanf("%d",&n);
//
//	root=NULL;
//	for(int i=0;i<n;i++)
//	{
//		int x;
//		printf("Nhap khoa x: ");
//		scanf("%d",&x);
//		Node* p=CreateNode(x);
//		insertNode(root,p);
//	}
//}
void Tao_Cay_tuFile(Node*& root)
{
	FILE* f = fopen("DLCay1.txt", "rt");

	int n;

	fscanf(f, "%d", &n);

	root = NULL;
	for (int i = 0; i < n; i++)
	{
		int x;

		fscanf(f, "%d", &x);
		Node* p = CreateNode(x);
		insertNode(root, p);
	}
}
////void Tao_Cay_N_Node(Node* &root)
////{
////	int n;
////	printf("\nNhap so nut: ");
////	scanf("%d",&n);
////
////	root=NULL;
////	for(int i=0;i<n;i++)
////	{
////		int x;
////		printf("Nhap khoa x: ");
////		scanf("%d",&x);
////		Node* p=CreateNode(x);
////		insertNode(root,p);
////	}
//
////}
Node* findNode(Node* root, int x)
{
	if (root == NULL) return NULL;
	if (root->info == x) return root;
	Node* p = findNode(root->Left, x);
	if (p != NULL)
		return p;
	return findNode(root->Right, x);
}
void In_Cay_LNR(Node* root)
{
	if (root == NULL)
		return;
	In_Cay_LNR(root->Left);
	printf("\t %d", root->info);
	In_Cay_LNR(root->Right);
}
void In_Cay_RNL(Node* root)
{
	if (root == NULL)
		return;
	In_Cay_RNL(root->Right);
	printf("\t %d", root->info);
	In_Cay_RNL(root->Left);
}
int tongGT(Node* root)
{
	if (root == NULL)
		return 0;
	return root->info + tongGT(root->Left) + tongGT(root->Right);
}
int demSoLonHonX(Node* root, int x)
{
	int d = 0;

	if (root == NULL)
		return 0;
	if (root->info <= x)
		d = demSoLonHonX(root->Right, x);
	else
		d = 1 + demSoLonHonX(root->Left, x) + demSoLonHonX(root->Right, x);
	return d;
}
int ChieuCaoCay(Node* root)
{
	if (root = NULL)
		return 0;
	int cl = ChieuCaoCay(root->Left);
	int cr = ChieuCaoCay(root->Right);

	if (cl > cr)
		return 1 + cl;
	else
		return 1 + cr;
}
void InNode_k(Node* root, int k)
{
	if (root == NULL)
		return;
	if (k == 0)
		printf("\t%d", root->info);
	k--;
	InNode_k(root->Left, k);
	InNode_k(root->Right, k);
}
void timMotNode(Node* root)//3 Kiểm tra Nút có trong cây hay k
{
	int x;
	printf("\nNhap nut can tim: ");
	scanf("%d", &x);
	Node* p = findNode(root, x);
	if (p == NULL)
		printf("\nKhong tim thay Nut");
	else
		printf("Da tim thay Node");
}
int isLeaf(Node* T) //4 Kiểm tra nút lá
{
	if (T == NULL)
		return 0;
	if (T->Left == NULL && T->Right == NULL)
		return 1;
	return 0;
}
int countTNode(Node* root)//5 Đếm số nút trên cây
{
	if (root == NULL)
		return 0;
	int nl = countTNode(root->Left);
	int nr = countTNode(root->Right);
	return(nl + nr + 1);
}

int countTNodeLeaf(Node* root)//6 đếm số nut lá của cây
{
	if (root == NULL)
		return 0;
	if (isLeaf(root))//if(root->Left==NULL && root->Right==NULL) //if(isLeaf(root))
		return 1;
	int nl = countTNodeLeaf(root->Left);
	int nr = countTNodeLeaf(root->Right);
	return(nl + nr);
}
int countTNodeNotLeaf(Node* root)//7 đếm số nut k là nút lá của cây
{

	return countTNode(root)-countTNodeLeaf(root);
	
}

int DemSoNutTrungGian(Node* root) //8 dem nút trung gian
{
	return countTNode(root) - countTNodeLeaf(root) -1;
}
int countTNodeHaveTwoChild(Node* root)
{
	if (root == NULL)
		return 0;
	if (root->Left == NULL || root->Right == NULL)
		return 0;
	int nl = countTNodeHaveTwoChild(root->Left);
	int nr = countTNodeHaveTwoChild(root->Right);
	return(nl + nr + 1);
}
//đếm so nut có 1 nut con
int countTNodeHaveOneChild(Node* root)
{
	if (root == NULL)
		return 0;
	if ((root->Left == NULL && root->Right != NULL) || (root->Right == NULL && root->Left != NULL))
		return 1;
	int nl = countTNodeHaveOneChild(root->Left);
	int nr = countTNodeHaveOneChild(root->Right);
	return(nl + nr);
}
int demConLaNutLa(Node* r)
{
	
	if (r == NULL)
		return 0;
	if (isLeaf(r->Left) == 1 || isLeaf(r->Right) == 1)
		return 1;
	int nl = demConLaNutLa(r->Left);
	int nr = demConLaNutLa(r->Right);
	return nl + nr ;
		
}

//Tìm giá trị lớn nhất trên cây nhị phân
int maxTNode(Node* root)
{
	if (root == NULL)
		return 0;
	if (!root->Left && !root->Right) //Thì Trỏ về Null là nút gốc
		return (root->info);
	int maxl = maxTNode(root->Left);
	int maxr = maxTNode(root->Right);
	int max = root->info;
	if (max < maxl)
		max = maxl;
	if (max < maxr)
		max = maxr;
	return max;
}

void InNode_k_NutLa(Node* root, int k)
{
	if (root == NULL)
		return;
	if (k == 0 && isLeaf(root))
		printf("\t%d", root->info);
	k--;
	InNode_k_NutLa(root->Left, k);
	InNode_k_NutLa(root->Right, k);
}
int Dem_Node_k(Node* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 0)
		return 1;
	k--;
	int nl=Dem_Node_k(root->Left, k);
	int nr=Dem_Node_k(root->Right, k);
	return nl + nr;
}
int Dem_Node_La_k(Node* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 0 && isLeaf(root))
		return 1;
	k--;
	int nl = Dem_Node_La_k(root->Left, k);
	int nr = Dem_Node_La_k(root->Right, k);
	return nl + nr;
}
void NodeTheMang(Node*& X, Node*& Y)
{
	if (Y->Left != NULL)
	{
		NodeTheMang(X, Y->Left);
	}
	else
	{
		X->info = Y->info;
		X = Y;
		Y = Y->Right;
	}
}
Node* findNodeReplace(Node*& p)
{
	Node* f = p;
	Node* rp = p->Right;
	while (rp->Left != NULL)
	{
		f = rp;
		rp = rp->Left;
	}
	p->info = rp->info;
	if (f == p)
		f->Right = rp->Right;
	else
		f->Left = rp->Right;
	return rp;
}
int XoaNode(Node* &root, int x)
{
	if (root == NULL)
	{
		return 0; 
	}
	else
	{
		if (x < root->info)
		{
			XoaNode(root->Left, x); 
		}
		else if (x > root->info)
		{
			XoaNode(root->Right, x); 
		}
		else 
		{
			Node* X = root; 
			if (root->Left == NULL)
			{
				root = root->Right;
				delete X;
			}
			else if (root->Right == NULL)
			{
				root = root->Left;
				delete X;
			}
			else
			{
				Node* q = findNodeReplace(X);
				delete q;
			}
			return 1;
		}
	}
}
int deleteTree(Node*& root) {
	if (root == NULL) {
		return 0;
	}
	if (root->Left) {
		deleteTree(root->Left);
	}
	if (root->Right) {
		deleteTree(root->Right);
	}
	delete root;
	// them vao cuoi
	root = NULL;
	return 1;
}
void main()
{
	int x;
	BTree bt;
	Tao_Cay_tuFile(bt.root);
	In_Cay_LNR(bt.root);
	//In_Cay_RNL(bt.root);

	/*printf("\nTong cac phan tu: %d",tongGT(bt.root));
	int x;ư
	printf("\n x=");
	scanf("%d",&x);
	int count=demSoLonHonX(bt.root, x);
	printf("\n\nTong gia tri lon hon X: %d",count);*/
	//printf("\nNhap vao gia tri nut ban muon xoa: "); scanf("%d", &x);
	if (deleteTree(bt.root) )
	{
		printf("Xoa Node thanh cong");
		In_Cay_LNR(bt.root);
	}
	else printf("Xoa node khong thanh cong");
	int k;
	printf("\nLevel k= ");
	scanf("%d", &k);
	//InNode_k_NutLa(bt.root, k);
	//timMotNode(bt.root);
	
	int soNutTG = Dem_Node_La_k(bt.root, k);
	printf("\n----So nut trung gian: %d", soNutTG);
	_getch();

}