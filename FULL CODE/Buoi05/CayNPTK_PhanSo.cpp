#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MyPhanSo.h"

//==CAY NPTK - PHANSO

struct Node
{
	PhanSo info;
	Node* left;
	Node* right;
};
//khoi tao
void init(Node*& root)
{
	root = NULL;
}
//cap phat node
Node* createNode(PhanSo x)
{
	Node* p = new Node;
	if (p != NULL)
	{
		p->info = x;
		p->left = p->right = NULL;
	}
	return p;
}
//them node vao cay
void insert(Node*& root, PhanSo x)
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
void LNR(Node* root)
{
	if (root != NULL)
	{
		LNR(root->left);
		inPS(root->info);
		LNR(root->right);
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

void readFile(Node*& root, char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		printf("Loi doc file");
		return;
	}
	else
	{
		PhanSo x;
		while (doc1PS(fp, x))
		{
			rutGon(x);
			insert(root, x);
		}
		fclose(fp);
	}
}

PhanSo tongNode(Node* root)
{
	if (root == 0) return {0,1};
	else
	{
		PhanSo t1 = tongNode(root->left);
		PhanSo t2 = tongNode(root->right);
		return root->info + t1 + t2;
	}
}
Node* findMin(Node* root)
{
	if (root == NULL) return NULL;
	while (root->left != NULL)
		root = root->left;
	return root;
}
void removeNode(Node*& root, PhanSo x)
{
	if (root == NULL) return;
	else
	{
		if (x < root->info)
			removeNode(root->left, x);
		else if (x > root->info)
			removeNode(root->right, x);
		else //tim thay x
		{
			//TH1: la node la
			if (root->left == NULL && root->right == NULL)
			{
				Node* tmp = root;
				root = NULL;
				delete tmp;
			}
			//TH2.1: co 1 con phai
			else if (root->left == NULL)
			{
				Node* tmp = root;
				root = root->right;
				delete tmp;
			}
			//TH2.2: co 1 con trai
			else if (root->right == NULL)
			{
				Node* tmp = root;
				root = root->left;
				delete tmp;
			}
			//TH3: co 2 con
			else 
			{
				//1. Tim node the mang (min ben nhanh phai)
				Node* rpNode = findMin(root->right);
				//2. Chep gia tri node the mang len node can xoa
				root->info = rpNode->info;
				//3. Xoa node the mang
				removeNode(root->right, rpNode->info);
			}

		}
	}
}

void main()
{
	Node* root;
	init(root);
	readFile(root, "PS.txt");
	LNR(root);
	printf("\nTong: ");
	PhanSo t = tongNode(root);
	inPS(t);

	printf("\nXoa phan so: \n");
	PhanSo x;
	nhapPS(x);
	removeNode(root, x);
	LNR(root);

	removeTree(root);

	system("pause");
}