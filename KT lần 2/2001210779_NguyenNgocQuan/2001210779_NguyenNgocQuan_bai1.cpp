#include<iostream>
#include<queue>
#include<fstream>
#include<math.h>
using namespace std;
struct Node
{
	int data;
	Node* left, * right;
};
struct Tree
{
	Node* root;
};
Node* create_node(int x)
{
	Node* p = new Node;
	if (p == NULL)
	{
		cout << "khong du bo nho cap phat ";
		return NULL;
	}
	p->data = x;
	p->left = p->right = NULL;
	return p;

}
void show_node(Node* t)
{
	cout << t->data << " ";
}
//bt la BTREE
void init_tree(Tree& bt) //tao cay rong
{
	bt.root = NULL;
}

//chen nut p ben trai
void insert_node(Node*& root, Node* p)
{
	if (root == NULL)
	{
		root = p;
		return;
	}
	if (root->data == p->data)
	{
		return;
	}
	if (p->data < root->data)
	{
		insert_node(root->left, p); //them ben trai
	}
	else
	{
		insert_node(root->right, p);
	}
}
void create_tree(Tree& bt) //tao cay bang nhap n ptu 
{
	int n;
	float x;
	init_tree(bt);
	cout << "nhap n ptu : ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "nhap gia tri nut : ";
		cin >> x;
		Node* p = create_node(x);
		insert_node(bt.root, p);
	}
}
void breadth_NLR(Node* root) //duyet cay chieu rong theo queue NLR
{
	if (root == NULL)
	{
		return;
	}
	queue<Node*>q;
	q.push(root);
	while (!q.empty())
	{
		Node* p;
		p = q.front();
		q.pop();
		show_node(p);
		if (p->left != NULL)
		{
			q.push(p->left);
		}
		if (p->right != NULL)
		{
			q.push(p->right);
		}
	}
}
Node* find_node(Node* root, int x)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->data == x)
	{
		return root;
	}
	else if (root->data > x)
	{
		return find_node(root->left, x);
	}
	else
	{
		return find_node(root->right, x);
	}
}
Node* find_stand_for(Node*& p)
{
	Node* f = p, * q = p;
	while (q->left != NULL)
	{
		f = q;
		q = q->left;
	}
	p->data = q->data;
	if (f == p)
	{
		f->right = q->right;
	}
	else
	{
		f->left = q->right;
	}
	return q;
}
int delete_node(Node*& root, int x)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->data > x)
	{
		return delete_node(root->left, x);
	}
	else if (root->data < x)
	{
		return delete_node(root->right, x);
	}
	else
	{
		Node* p = root;
		if (root->left == NULL)
		{
			root = root->right;
			delete p;
		}
		else if (root->right == NULL)
		{
			root = root->left;
			delete p;
		}
		else
		{
			Node* q = find_stand_for(p);
			delete p;
		}
		return 1;
	}
}
int max_distance(Node* root, int x) //ham tim khoang cach xa nhat
{
	if (!root)
	{
		return -1;
	}
	Node* minleft = root, * maxright = root;
	while (minleft->left != NULL)
	{
		minleft = minleft->left;
	}
	while (maxright->right != NULL)
	{
		maxright = maxright->right;
	}
	int distance1 = abs(x - minleft->data);
	int distance2 = abs(x - maxright->data);
	if (distance1 > distance2)
	{
		return minleft->data;
	}
	else
	{
		return maxright->data;
	}
}
void create_tree_array(Tree& bt, int a[]) //tao cay tu mang
{
	int n;
	init_tree(bt);
	for (int i = 0; i < 15; i++)
	{
		cout << "nhap gia tri nut : ";
		cin >> a[i];
	}
	for (int i = 0; i < 15; i++)
	{
		Node* p = create_node(a[i]);
		insert_node(bt.root, p);
	}
}
int sum_one_child(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return 0;
	}
	if (root->left == NULL)
	{
		return root->right->data + sum_one_child(root->right);
	}
	if (root->right == NULL)
	{
		return root->left->data + sum_one_child(root->left);
	}
	return sum_one_child(root->left) + sum_one_child(root->right);
}
int count_xy(Node* root, int x, int y)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->data >= x && root->data <= y)
	{
		return 1 + count_xy(root->left, x, y) + count_xy(root->right, x, y);
	}
	else if (root->data < x)
	{
		return count_xy(root->right, x, y);
	}
	else
	{
		return count_xy(root->left, x, y);
	}
}
int main()
{
	Tree bt;
	Node* p, * root;
	int select, x;
	int a[15];
	cout << "=======================MENU=======================" << endl;
	cout << "1. cay nhi phan luu cac so nguyen " << endl;
	cout << "2. tao cay nhi phan tu mang  " << endl;
	cout << "3. kiem tra X ton tai  " << endl;
	cout << "4. xoa phan tu X " << endl;
	cout << "5. duyet cay theo chieu rong NLR " << endl;
	cout << "6. khoang cach lon nhat " << endl;
	cout << "7. dem nut nam trong doan [x,y] " << endl;
	cout << "8. tinh tong cac nut 1 con " << endl;
	cout << "==================================================" << endl;
	cout << endl;
	cout << "moi ban chon bai : ";
	cin >> select;
	switch (select)
	{
	case 1:
		create_tree(bt);
		cout << "duyet cay theo NLR : ";
		breadth_NLR(bt.root);
		break;
	case 2:
		create_tree_array(bt, a);
		cout << "duyet cay theo NLR : ";
		breadth_NLR(bt.root);
		break;
	case 3:
		create_tree(bt);
		cout << "nhap gia tri can tim : ";
		cin >> x;
		if (find_node(bt.root, x) != NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 4:
		create_tree(bt);
		cout << "nhap gia tri can xoa : ";
		cin >> x;
		delete_node(bt.root, x);
		cout << "duyet cay theo chieu rong NLR : ";
		breadth_NLR(bt.root);
		break;
	case 5:
		create_tree(bt);
		cout << "duyet cay theo chieu rong NLR : ";
		breadth_NLR(bt.root);
		break;
	case 6:
		create_tree(bt);
		cout << "nhap gtri can tim khoang cach : ";
		cin >> x;
		cout << "khoang cach xa nhat : " << max_distance(bt.root, x);
		break;
	case 7:
		create_tree(bt);
		int x, y;
		cout << "nhap x : ";
		cin >> x;
		cout << "nhap y: ";
		cin >> y;
		cout << "dem nut trong doan [x,y] : " << count_xy(bt.root, x, y);
		break;
	case 8:
		create_tree(bt);
		cout << "tong so nut 1 con : " << sum_one_child(bt.root);
		break;
	default: cout << "Bn nhap sai cu phap. Vui long chay lai ";
		break;
	}
}