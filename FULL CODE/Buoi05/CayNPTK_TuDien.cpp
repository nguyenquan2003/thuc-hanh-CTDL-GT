//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////===PHAN SO====
//struct TuVung
//{
//	char tu[15];
//	char nghia[50];
//};
//
//void inPS(TuVung x)
//{
//	printf("%s : %s\n", x.tu, x.nghia);
//}
//
//bool operator == (TuVung a, TuVung b)
//{
//	return stricmp(a.tu, b.tu) == 0;
//}
//bool operator < (TuVung a, TuVung b)
//{
//	return stricmp(a.tu, b.tu) < 0;
//}
//bool operator == (TuVung a, TuVung b)
//{
//	return stricmp(a.tu, b.tu) > 0;
//}
////==CAY NPTK - PHANSO
//
//struct Node
//{
//	TuVung info;
//	Node* left;
//	Node* right;
//};
////khoi tao
//void init(Node*& root)
//{
//	root = NULL;
//}
////cap phat node
//Node* createNode(TuVung x)
//{
//	Node* p = new Node;
//	if (p != NULL)
//	{
//		p->info = x;
//		p->left = p->right = NULL;
//	}
//	return p;
//}
////them node vao cay
//void insert(Node*& root, TuVung x)
//{
//	if (root == NULL)
//		root = createNode(x);
//	else
//	{
//		if (root->info == x) return;
//		else if (x < root->info)
//			insert(root->left, x);
//		else
//			insert(root->right, x);
//	}
//}