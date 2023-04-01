#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int info;
	Node* left;
	Node* right;
};
//khoi tao
void init(Node*& root)
{
	root = NULL;
}
//cap phat node
Node* createNode(int x)
{
	Node* p = new Node;
	if (p != NULL)
	{
		p->info = x;
		p->left = p->right = NULL;
	}
	return p;
}

//them theo cay NPTK
void insert(Node*& root, int x)
{
	if (root == NULL)
		root = createNode(x);
	else
	{
		if (root->info == x) return;
		else if (x < root->info)
			insert(root->left, x);
		else
			insert(root->right, x);			
	}
}
//duyet theo thu tu truoc (preOrder traverse)
void NLR(Node* root)
{
	if (root != NULL)
	{
		printf("%d ", root->info);
		NLR(root->left);
		NLR(root->right);
	}
}
void LNR(Node* root)
{
	if (root != NULL)
	{
		LNR(root->left);
		printf("%d ", root->info);
		LNR(root->right);
	}
}
void LRN(Node* root)
{
	if (root != NULL)
	{
		LRN(root->left);
		LRN(root->right);
		printf("%d ", root->info);
	}
}

void removeTree(Node*& root)
{
	if (root != NULL)
	{
		removeTree(root->left);
		removeTree(root->right);
		delete root;
	}
}
void readFile(Node* &root, char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if (fp != NULL)
	{
		int x;
		while (fscanf(fp, "%d", &x) == 1)
		{
			insert(root, x);
		}

		fclose(fp);
	}
}

int demSLNode(Node* root)
{
	if (root == NULL) return 0;
	else
	{
		int d1 = demSLNode(root->left);
		int d2 = demSLNode(root->right);
		return 1 + d1 + d2;
	}
}
//dem theo dieu kien
int demSLNodeChan(Node* root)
{
	if (root == NULL) return 0;
	else
	{
		int d1 = demSLNode(root->left);
		int d2 = demSLNode(root->right);
		if (root->info %2 == 0)
			return 1 + d1 + d2;
		else
			return d1 + d2;
	}
}
int max(int a, int b)
{
	return a > b ? a : b;
}
int tinhChieuCao(Node* root)
{
	if (root == NULL) return 0;
	else
	{
		int c1 = tinhChieuCao(root->left);
		int c2 = tinhChieuCao(root->right);
		return 1 + max(c1, c2);
	}
}

void main()
{
	//1. Khai bao
	Node* root;
	//2. Khoi tao
	init(root);
	//3. Xay dung cay
	//Cach 1: xay thu cong
	//root = createNode(4);
	//root->left = createNode(2);
	//root->right = createNode(5);
	//root->left->left = createNode(1);
	//root->left->right = createNode(3);

	//Cach 2: dung insert cua NPTK (tu dong dieu huong)
	//insert(root, 4);
	//insert(root, 2);
	//insert(root, 5);
	//insert(root, 1);
	//insert(root, 3);

	//cach 3: doc tu file
	readFile(root, "input.txt");

	//4. Xu ly
	LNR(root);
	printf("\nChieu cao: %d", tinhChieuCao(root));
	//5. Huy cay
	removeTree(root);

	system("pause");
}