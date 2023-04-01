//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <queue>
//#include <stack>
//using namespace std;
//
//
//struct Node
//{
//	int info;
//	Node* left;
//	Node* right;
//};
////khoi tao
//void init(Node*& root)
//{
//	root = NULL;
//}
////cap phat node
//Node* createNode(int x)
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
//void insert(Node*& root, int x)
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
//
//void LNR(Node* root)
//{
//	if (root != NULL)
//	{
//		LNR(root->left);
//		printf("%d ", root->info);
//		LNR(root->right);
//	}
//}
//void removeTree(Node*& root)
//{
//	if (root != NULL)
//	{
//		removeTree(root->left);
//		removeTree(root->right);
//		delete root;
//	}
//}
//
//bool isBST(Node* root)
//{
//	if (root == NULL) return true;
//	else
//	{
//		//kiem tra trai, phai
//		bool kt1 = isBST(root->left);
//		bool kt2 = isBST(root->right);
//
//		//kiem tra tai goc
//		if (root->left != NULL){
//			if (root->info <= root->left->info) return false;
//		}
//		if (root->right != NULL){
//			if (root->info >= root->right->info) return false;
//		}
//		return kt1 && kt2;
//	}
//}
//
//void readFile(Node*& root, char* fileName)
//{
//	FILE* fp = fopen(fileName, "rt");
//	if (fp == NULL)
//	{
//		printf("Loi doc file");
//		return;
//	}
//	else
//	{
//		int x;
//		while (fscanf(fp, "%d", &x) == 1)
//		{
//			insert(root, x);
//		}
//		fclose(fp);
//	}
//}
//int demNode(Node* root)
//{
//	if (root == NULL) return 0;
//	else
//	{
//		int d1 = demNode(root->left);
//		int d2 = demNode(root->right);
//		return 1 + d1 + d2;
//	}
//}
//int demNode_Chan(Node* root)
//{
//	if (root == NULL) return 0;
//	else
//	{
//		int d1 = demNode_Chan(root->left);
//		int d2 = demNode_Chan(root->right);
//		if (root->info % 2 == 0)
//			return 1 + d1 + d2;
//		else
//			return d1 + d2;
//	}
//}
//
//int demNodeTrongDoanAB(Node* root, int a, int b)
//{
//	if (root == NULL) return 0;
//	else
//	{
//		int d1 = demNodeTrongDoanAB(root->left, a,b);
//		int d2 = demNodeTrongDoanAB(root->right, a,b);
//		if (root->info >= a && root->info <= b)
//			return 1 + d1 + d2;
//		else
//			return d1 + d2;
//	}
//}
//int demNodeLonHonXTrongDoanAB(Node* root, int a, int b, int x)
//{
//	if (x < a || x > b) return 0;
//	return demNodeTrongDoanAB(root, x, b);
//}
//int tongNode(Node* root)
//{
//	if (root == NULL) return 0;
//	else
//	{
//		int t1 = tongNode(root->left);
//		int t2 = tongNode(root->right);
//		return root->info + t1 + t2;
//	}
//}
//void xuatChan_Giam(Node* root)
//{
//	if (root != NULL)
//	{
//		xuatChan_Giam(root->right);
//		if (root->info %2 == 0) 
//			printf("%d ", root->info);
//		xuatChan_Giam(root->left);
//	}
//}
//
//Node* findMin(Node* root)
//{
//	if (root == NULL) return NULL;
//	while (root->left != NULL)
//		root = root->left;
//	return root;
//}
//
//void removeNode(Node*& root, int x)
//{
//	if (root == NULL) return;
//	else
//	{
//		if (x < root->info)
//			removeNode(root->left, x);
//		else if (x > root->info)
//			removeNode(root->right, x);
//		else //tim thay x
//		{
//			//TH1: la node la
//			if (root->left == NULL && root->right == NULL)
//			{
//				Node* tmp = root;
//				root = NULL;
//				delete tmp;
//			}
//			//TH2.1: co 1 con phai
//			else if (root->left == NULL)
//			{
//				Node* tmp = root;
//				root = root->right;
//				delete tmp;
//			}
//			//TH2.2: co 1 con trai
//			else if (root->right == NULL)
//			{
//				Node* tmp = root;
//				root = root->left;
//				delete tmp;
//			}
//			//TH3: co 2 con
//			else 
//			{
//				//1. Tim node the mang (min ben nhanh phai)
//				Node* rpNode = findMin(root->right);
//				//2. Chep gia tri node the mang len node can xoa
//				root->info = rpNode->info;
//				//3. Xoa node the mang
//				removeNode(root->right, rpNode->info);
//			}
//
//		}
//	}
//}
//
////duyet theo chieu sau
//void DFS(Node* root)
//{
//	stack<Node*> s;
//	//1.them root vao stack
//	s.push(root);
//	//2. xu ly trong stack
//	while (!s.empty())
//	{
//		//2.1 Lay phan tu tren dinh stack ra de xu ly
//		Node* t = s.top(); s.pop();
//
//		//2.2 Xu ly phan tu t
//		printf("%d ", t->info);
//
//		//2.3 Them con phai va trai cua t vao stack
//		if (t->right != NULL)
//			s.push(t->right);
//		if (t->left != NULL)
//			s.push(t->left);
//	}
//}
//
////duyet theo chieu rong
//void BFS(Node* root)
//{
//	queue<Node*> q;
//	//1.them root vao queue
//	q.push(root);
//	//2. xu ly trong queue
//	while (!q.empty())
//	{
//		//2.1 Lay phan tu tren dinh queue ra de xu ly
//		Node* t = q.front(); q.pop();
//
//		//2.2 Xu ly phan tu t
//		printf("%d ", t->info);
//
//		//2.3 Them con trai va phai cua t vao queue
//		if (t->left != NULL)
//			q.push(t->left);
//		if (t->right != NULL)
//			q.push(t->right);
//
//	}
//}
//
////xoa cac node chan
//void removeNodeChan(Node*& root)//{//	if (root == NULL) return;//	else//	{//		removeNodeChan(root->left);//		removeNodeChan(root->right);//		if (root->info % 2 == 0)//		{//			removeNode(root, root->info);//		}//	}//}
//
//
//
//void main()
//{
//	//1.Khai bao
//	Node* root;
//	//2. Khoi tao
//	init(root);
//	//3. Xay dung cay
//	readFile(root, "input.txt");
//
//	//4. Xu ly
//	removeNodeChan(root);
//	LNR(root);
//	//DFS(root);
//	//printf("\n");
//	//BFS(root);
//
//	//5.Huy cay
//	removeTree(root);
//
//	system("pause");
//}