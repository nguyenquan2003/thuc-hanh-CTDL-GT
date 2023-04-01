#include <iostream>
#include <Windows.h>
#include<fstream>
#include <queue>
using namespace std;
enum Color { Red, Black };
struct Node
{
	//left: nut trai, right: nut phai, parent: nut cha
	int data;
	Color color;
	Node* left, * right, * parent;
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
		cout << "khong the cap phat ";
		return NULL;
	}
	p->data = x;
	p->color = Red;
	p->left = p->right = p->parent = NULL;
	return p;
}
void set_color(int cl_back_ground, int cl_text) //cl la color
{
	HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Color, cl_back_ground * 16 + cl_text);
}
void show_node(Node* p) //hien nut
{
	if (p->color == Red)
	{
		set_color(15, 12);
	}
	else if (p->color == Black)
	{
		set_color(15, 0);
	}
	cout << p->data<<" ";
	set_color(0, 7);
}
void init_tree(Tree& bt) //tao cay
{
	bt.root = NULL;
}
void swap_color(Color& color1, Color& color2) //hoan vi mau cua 2 nut
{
	/*Color temp = color1;
	color1 = color2;
	color2 = temp;*/
	swap(color1, color2);
}
void swap_info(int& info1, int& info2)
{
	/*int temp = info1;
	info1 = info2;
	info2 = temp;*/
	swap(info1, info2);
}
void breadth_NLR(Node* root) //duyet cay theo chieu rong NLR
{
	if (root == NULL)
	{
		return;
	}
	queue<Node*>q;
	q.push(root);
	while (!q.empty())
	{
		Node* p = q.front();
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
void breadth_NRL(Node* root) //duyet cay theo chieu rong NRL
{
	if (root == NULL)
	{
		return;
	}
	queue <Node*> q;
	q.push(root);
	while (!q.empty())
	{
		Node* p;
		p = q.front();
		q.pop();
		show_node(p);
		if (p->right != NULL)
		{
			q.push(p->right);
		}
		if (p->left != NULL)
		{
			q.push(p->left);
		}
	}
}
void show_lv_order(Node* root)
{
	cout << "in theo thu tu cap : ";
	if (root == NULL)
	{
		cout << "cay rong ";
	}
	else
	{
		breadth_NLR(root);
	}
}
//rbt: red and black tree
Node* insert_rbt(Node* root, Node* p) //them nut vao cay do den
{
	if (root == NULL)
	{
		return p;
	}
	if (p->data < root->data)
	{
		root->left = insert_rbt(root->left, p);
		root->left->parent = root;
	}
	else if (p->data > root->data)
	{
		root->right = insert_rbt(root->right, p);
		root->right->parent = root;
	}
	return root;
}
void rotate_left(Node*& root, Node*& p) //xoay nut trai
{
	Node* pRight = p->right;
	p->right = pRight->left;
	if (p->right != NULL)
	{
		p->right->parent = p;
	}
	pRight->parent = p->parent;
	if (p->parent == NULL)
	{
		root = pRight;
	}
	else if (p == p->parent->left)
	{
		p->parent->left = pRight;
	}
	else
	{
		p->parent->right = pRight;
	}
	pRight->left = p;
	p->parent = pRight;
}
void rotate_right(Node*& root, Node*& p)
{
	Node* pLeft = p->left;
	p->left = pLeft->right;
	if (p->left != NULL)
	{
		p->left->parent = p;
	}
	pLeft->parent = p->parent;
	if (p->parent == NULL)
	{
		root = pLeft;
	}
	else if (p == p->parent->left)
	{
		p->parent->left = pLeft;
	}
	else
	{
		p->parent->right = pLeft;
	}
	pLeft->right = p;
	p->parent = pLeft;
}
void fix_violation(Node*& root, Node*& p)
{
	Node* parent = NULL, * grand_parent = NULL;
	while (p!=root&&p->color!=Black&&p->parent->color==Red)
	{
		parent = p->parent;
		grand_parent = p->parent->parent;
		//truong hop A: node cha cua p la con trai node cha cua p
		if (parent == grand_parent->left)
		{
			//truong hop 1: node chu cua p la node do chi can doi mau cho node do thanh den  
			Node* uncle = grand_parent->right;
			if (uncle != NULL && uncle->color == Red)
			{
				grand_parent->color = Red;
				parent->color = Black;
				uncle->color = Black;
				p = grand_parent;
			}
			else
			{
				//truong hop 2: p lat nut con phai cua nut cha no. ta thuc hien xoay trai
				if (p == parent->right)
				{
					rotate_left(root, parent);
					p = parent;
					parent = p->parent;
				}
				//truong hop 3: la con trai cua node cha, no thuc hien xoay phai 
				rotate_right(root, grand_parent);
				swap_color(parent->color, grand_parent->color);
				p = parent;
			}
		}
		//truong hop B: node cha cua p la con phai cua node cha cua node cha cua p
		else
		{
			Node* uncle = grand_parent->left;
			//truong hop 1: chu cua p la node do khi nay chi can doi mau cho 2 node do thanh den
			if (uncle != NULL && uncle->color == Red)
			{
				grand_parent->color = Red;
				parent->color = Black;
				uncle->color = Black;
				p = grand_parent;
			}
			else
			{
				//truong hop 2: p la con trai cua node cha no, thuc hien xoay phai
				if (p == parent->left)
				{
					rotate_right(root, parent);
					p = parent;
					parent = p->parent;
				}
				//truong hop 3: p la node con phai cua node cha no, thuc hien xoay trai
				rotate_left(root, grand_parent);
				swap_color(parent->color, grand_parent->color);
				p = parent;
			}
		}
	}
	root->color = Black;
}
void insert_node(Node*& root, int x) //them node moi vao du lieu da cho
{
	Node* p = create_node(x);
	root = insert_rbt(root, p); //thuc hien chen
	fix_violation(root, p); //sua loi qui tac cay do den
}
void create_tree_array(Tree& bt, int a[])
{
	int n;
	cout << "nhap so ptu : ";
	cin >> n;
	init_tree(bt);
	for (int i = 0; i < n; i++)
	{
		cout << "nhap gia tri nut : ";
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		insert_node(bt.root, a[i]);
	}
}
void read_file(Tree& bt, string filename)
{
	ifstream file;
	file.open(filename, ios::in);
	if (file.fail())
	{
		cout << "loi doc file ";
	}
	else
	{
		init_tree(bt);
		while (!file.eof())
		{
			int  x;
			file >> x;
			insert_node(bt.root,x);
		}
	}
	file.close();
}
void NLR(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	show_node(root);
	NLR(root->left);
	NLR(root->right);
}
void LNR(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	LNR(root->left);
	show_node(root);
	LNR(root->right);
}
void LRN(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	LRN(root->left);
	LRN(root->right);
	show_node(root);
}
void NRL(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	show_node(root);
	NRL(root->right);
	NRL(root->left);
}
void RNL(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	RNL(root->right);
	show_node(root);
	RNL(root->left);
}
void RLN(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	RLN(root->right);
	RLN(root->left);
	show_node(root);
}
Node* insert_node(Node* root, Node* p) //them nut vao cay do den
{
	if (root == NULL)
	{
		return p;
	}
	if (p->data < root->data)
	{
		root->left = insert_node(root->left, p);
		root->left->parent = root;
	}
	else if (p->data > root->data)
	{
		root->right = insert_node(root->right, p);
		root->right->parent = root;
	}
	return root;
}
Node* find_succssor(Node* p) //tim nut khong co con ben trai trong cay con cua nut da cho
{
	Node* temp = p;
	while (temp -> left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}
Node* replace(Node* p)
{
	if (p->left != NULL && p->right != NULL)
	{
		return find_succssor(p->right);
	}
}
bool is_on_left(Node* p)
{
	return p == p->parent->left;
}
Node* find_sibling(Node* p) //tim nut anh em 
{
	if (p->parent == NULL)
	{
		return NULL;
	}
	if (is_on_left(p))
	{
		return p->parent->right;
	}
	return p->parent->left;
}
bool has_red_child(Node* p) //kt nut hien tai co nut con la nut do khong
{
	return (p->left != NULL && p->left->color == Red) || (p->right != NULL && p->right->color == Red);
}
void fix_double_black(Node*& root, Node* p)
{
	//p la node goc thi return
	if (p == root)
	{
		return;
	}
	Node* pSibling = find_sibling(p);
	Node* pParent = p->parent;
	if (pSibling == NULL)
	{
		//khong co sibiling, mau den kep duoc day len
		fix_double_black(root, pParent);
	}
	else
	{
		if (pSibling->color == Red)
		{
			//anh em mau do
			pParent->color = Red;
			pSibling->color = Black;
			if (is_on_left(pSibling))
			{
				//trường hợp left
				rotate_right(root, pParent);
			}
			else
			{
				rotate_left(root, pParent);
			}
			fix_double_black(root, p);
		}
		else
		{
			//anh em đen
			if (has_red_child(pSibling))
			{
				//it nhat mot tre em mau do
				if (pSibling->left != NULL && pSibling->left->color == Red)
				{
					if (is_on_left(pSibling))
					{
						//left, left
						pSibling->left->color = pSibling->color;
						pSibling->color = pParent->color;
						rotate_right(root, pParent);
					}
					else
					{
						//right - left
						pSibling->left->color = pParent->color;
						rotate_right(root, pSibling);
						rotate_left(root, pParent);
					}
				}
				else
				{
					if (is_on_left(pSibling))
					{
						//left- right
						pSibling->right->color = pParent->color;
						rotate_left(root, pSibling);
						rotate_right(root, pParent);
					}
					else
					{
						//right -right
						pSibling->right->color = pSibling->color;
						pSibling->color = pParent->color;
						rotate_left(root, pParent);
					}
				}
				pParent->color = Black;
			}
			else
			{
				//hai con den
				pSibling->color = Red;
				if (pParent->color == Black)
				{
					fix_double_black(root, pParent);
				}
				else
				{
					pParent->color = Black;
				}
			}
		}
	}
}
void delete_node(Node* root, Node* pDelete)
{
	Node* pReplace = replace(pDelete);
	//dung khu pRelace va pDelete deu den
	//flag_db: flag Double Black: co doi den
	bool flag_db = (pReplace == NULL || pReplace->color == Black && pDelete->color == Black);
	Node* pParent = pDelete->parent;
	if (pReplace == NULL)
	{
		//pReplace la NULL do do pDelete la la
		if (pDelete == root)
		{
			//pDelete la root, lam cho root la NULL
			root = NULL;
		}
		else
		{
			if (flag_db)
			{
				//pReplace va pDelete deu den, pDete la la , sua mau den kep
				fix_double_black(root, pDelete);
			}
			else
			{
				//pReplace hoac pDelete la do
				if (find_sibling(pDelete) != NULL)
					//node anh chi em khong rong, lam cho no mau do
					find_sibling(pDelete)->color = Red;
			}
			//xóa khoi cay
			if (is_on_left(pDelete))
			{
				pParent->left = NULL;
			}
			else
			{
				pParent->right = NULL;
			}
		}
		delete pDelete;
		return;
	}
	if (pDelete->left == NULL || pDelete->right == NULL)
	{
		//pDelete co 1 con
		if (pDelete == root)
		{
			//gan gia tri cua  pReplace cho pDelete va xoa pReplace
			pDelete->data = pReplace->data;
			pDelete->left = pDelete->right = NULL;
			delete pReplace;
		}
		else
		{
			//tach node pDelete khoi cay va di chuyen node pReplace lên
			if (is_on_left(pDelete))
			{
				pParent->left = pReplace;
			}
			else
			{
				pParent->right = pReplace;
			}
			delete pDelete;
			pReplace->parent = pParent;
			if (flag_db)
			{
				//pReplace va pdelete deu den sua 2 mau den o pReplace
				fix_double_black(root, pReplace);
			}
			else
			{
				//pReplace hoac pDelete dỏ, mau pReplace den
				pReplace->color = Black;
			}
		}
		return;
	}
	//pDelete co 2 con, hoan dổi gia tri voi nut the mang va de qui
	swap_info(pReplace->data, pDelete->data);
	delete_node(root, pReplace);
}
Node* search(Node* root, int x)
{
	Node* temp = root;
	while (temp != NULL)
	{
		if (x == temp->data)
		{
			return temp;
		}
		else if (x < temp->data)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return NULL; //khong tim thay
}
int main()
{
	int select, a[50], x;
	Tree bt;
	Node* p;
	char filename[] = "data.txt";
	cout << "=================MENU=================" << endl;
	cout << "1. tao cay tu mang " << endl;
	cout << "2.tao cay tu file " << endl;
	cout << "3. duyet cay " << endl;
	cout << "4.duyet cay theo chieu rong " << endl;
	cout << "5. them 1 nut co gia tri x " << endl;
	cout << "6. Xoa nut có gia tri X bat ky " << endl;
	cout << "7. Tim nut co gia tri X tren cay " << endl;
	cout << "======================================" << endl;
	cout << "moi bn chon bai : ";
	cin >> select;
	switch (select)
	{
	case 1: 
		create_tree_array(bt, a);
		show_lv_order(bt.root);
		break;
	case 2:
		read_file(bt, filename);
		show_lv_order(bt.root);
		break;
	case 3:
		create_tree_array(bt, a);
		cout << "\nduyet cay theo NLR : ";
		NLR(bt.root);
		cout << "\nduyet cay theo NRL : ";
		NRL(bt.root);
		cout << "\nduyet cay theo LNR : ";
		LNR(bt.root);
		cout << "\nduyet cay theo RNL : ";
		RNL(bt.root);
		cout << "\nduyet cay theo LRN : ";
		LRN(bt.root);
		cout << "\nduyet cay theo RLN : ";
		RLN(bt.root);
		break;
	case 4:
		create_tree_array(bt, a);
		cout << "duyet cay theo chieu rong NLR : ";
		breadth_NLR(bt.root);
		cout << endl;
		cout << "duyet cay theo chieu rong NRL : ";
		breadth_NRL(bt.root);
		break;
	case 5:
		create_tree_array(bt, a);
		cout << "nhap gia tri can them : ";
		cin >> x;
		insert_node(bt.root, x);
		breadth_NLR(bt.root);
		break;
	case 6:
		cout << "nhap gia tri can xoa: ";
		cin >> x;
		p = search(bt.root, x);
		delete_node(bt.root, p);
		breadth_NLR(bt.root);
		cout << endl;
		break;
	case 7:
		cout << "nhap nut can tim: ";
		cin >> x;
		//p=CreateTNode(x);
		if (search(bt.root, x) != NULL)
		{
			cout << "tim thay: " << x << endl;
		}
		else
		{
			cout << "khong tim thay" << endl;
		}
		break;
	default: cout << "bn nhap sai cu phap. Vui long chay lai ";
		break;
	}
}