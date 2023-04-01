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
void read_file(Tree& bt,string filename)
{
	int n = 0;
	ifstream file;
	file.open(filename, ios_base::in);
	if (file.fail())
	{
		cout << "loi doc file ";
	}
	else
	{
		file >> n;
		init_tree(bt);
		while (!file.eof())
		{
			int x;
			file >> x;
			insert_node(bt.root, create_node(x));
		}
	}
	file.close();
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
void LNR(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	LNR(root->left);
	cout << root->data << " ";
	LNR(root->right);
}
int min_distance(Node* root, int x)
{
	if (!root)
	{
		return -1;
	}
	int min = root->data;
	int mindis = abs(x - min);
	while (root != NULL)
	{
		if (root->data == x)
		{
			return x;
		}
		if (mindis > abs(x - root->data))
		{
			min = root->data;
			mindis = abs(x - min);
		}
		if (x > root->data)
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}
	}
	return min;
}
int count_smaller(Node* root, int x)
{
	int result = 0;
	if (root == NULL)
	{
		return 0;
	}
	if (root->data < x)
	{
		result++;
	}
	result += count_smaller(root->left, x);
	result += count_smaller(root->right, x);
	return result;
}
int sum_two_child(Node* root)
{
	int sum = 0;
	if (root == NULL)
	{
		return 0;
	}
	if (root->left != NULL && root->right != NULL)
	{
		return root->data + sum_two_child(root->left) + sum_two_child(root->right);
	}
	else
	{
		return sum_two_child(root->left) + sum_two_child(root->right);
	}
}
int main()
{
	Tree bt;
	Node* p,* root;
	int select, x;
	char filename[] = "data.txt";
	cout << "=======================MENU=======================" << endl;
	cout << "1. cay nhi phan luu cac so nguyen " << endl;
	cout << "2. doc file " << endl;
	cout << "3. kiem tra X ton tai  " << endl;
	cout << "4. xoa phan tu X " << endl;
	cout << "5. sap xep theo thu tu tang dan " << endl;
	cout << "6. tim ptu khoang cach toi X nho nhat " << endl;
	cout << "7. dem so nho hon X " << endl;
	cout << "8. tong cac nut 2 con " << endl;
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
		read_file(bt, filename);
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
		cout << "xuat theo thu tu tang dan : ";
		LNR(bt.root);
		break;
	case 6: 
		create_tree(bt);
		cout << "nhap gtri can tim khoang cach : ";
		cin >> x;
		cout << "khoang cach nho nhat : " << min_distance(bt.root, x);
		break;
	case 7: 
		create_tree(bt);
		cout << "so ptu nho hon X : "<<count_smaller(bt.root,50);
		break;
	case 8: 
		create_tree(bt);
		cout<<"tong cac nut 2 con : "<<sum_two_child(bt.root);
		break;
	default: cout << "bn nhap sai. Vui long chay lai ";
		break;
	}
}