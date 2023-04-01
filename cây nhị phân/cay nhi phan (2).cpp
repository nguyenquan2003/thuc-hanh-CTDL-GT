#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<cmath>
//CACH KHAI BAO DEU GIONG NHAU
//Node* p = create_node(x);insert_node(bt.root, p); = insert_node(bt.root, create_node(x));
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
//ham tao cay 
void create_tree_array(Tree& bt, int a[]) //tao cay tu mang
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
		Node* p = create_node(a[i]);
		insert_node(bt.root, p);
	}
}
void create_tree(Tree& bt) //tao cay bang nhap n ptu 
{
	int x, n;
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
void create_tree_auto(Tree& bt)
{
	int n, x;
	cout << "nhap n ptu : ";
	cin >> n;
	init_tree(bt);
	srand((unsigned)time(NULL)); //tao so moi sau moi lan thuc hien 
	for (int i = 1; i <= n; i++)
	{
		x = (rand() % 199) - 99; //tao 1 so ngau nhien tu -99 den 99
		Node* p = create_node(x);
		insert_node(bt.root, p);
	}
}
void breadth_NLR_stack(Node* root) //duyet cay chieu rong theo stack
{
	stack<Node*>q;
	Node* p;
	q.push(root);
	while (!q.empty())
	{
		p = q.top();
		q.pop();
		cout << p->data << " ";
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
void breadth_NLR_queue(Node* root) //duyet cay chieu rong theo queue NLR
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
void breadth_NRL(Node* root) //duyet cay chieu rong theo queue NRL
{
	if (root == NULL)
		return;
	queue <Node*> q;
	q.push(root);
	while (!q.empty())
	{
		Node* p;
		p = q.front();//nhận giá trị nút trên cùng
		q.pop(); //xóa giá trị trên cùng
		show_node(p);
		if (p->right != NULL)
			q.push(p->right);
		if (p->left != NULL)
			q.push(p->left);

	}

}
void depth_NLR(Node* root) //ham duyet cay theo chieu sau
{
	stack<Node*>q;
	Node* p;
	q.push(root);
	while (!q.empty())
	{
		p = q.top();
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
//============= DOC FILE C++ ============= 
void read_file(Tree& bt, string fileName)
{
	ifstream file;
	file.open(fileName, ios_base::in);
	if (file.fail())
		cout << "loi doc file ";
	else
	{
		init_tree(bt);
		while (!file.eof())
		{
			int x;
			file >> x; // chuyen nd vao file
			insert_node(bt.root, create_node(x));
		}
	}
	file.close();
}
//============= DOC FILE C ============= 
void taoFile(Tree& bt, char fileName[])
{
	FILE* f = fopen(fileName, "r+");
	if (f == NULL)
	{
		printf("\nLoi doc file!");
		return;
	}
	int x;
	init_tree(bt);
	int n;
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &x);
		insert_node(bt.root, create_node(x));
	}
	fclose(f);
}

//ham xuat cay nhi phan theo NLR
void NLR(Node* root)
{
	if (root == NULL) //neu cay con ptu thi tiep tuc duyet
	{
		return;
	}
	cout << root->data << " "; //xuat du lieu trong node
	NLR(root->right); //duyet qua phai
	NLR(root->left); //duyet qua trai
}
void NRL(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	cout << root->data << " ";
	NRL(root->right);
	NRL(root->left);
}
//ham xuat cay nhi phan theo LNR <=> xuat ra cac ptu tu be den lon
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
//ham xuat cay nhi phan theo RNL
void RNL(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	RNL(root->right);
	cout << root->data << " ";
	RNL(root->left);
}
//ham xuat cay nhi phan theo LRN
void LRN(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	LRN(root->left);
	LRN(root->right);
	cout << root->data << " ";
}
//ham xuat cay nhi phan theo RLN
void RLN(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	RLN(root->right);
	RLN(root->left);
	cout << root->data << " ";
}

Node* find_node(Node* root, int x) //ham tim nut
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
Node* find_stand_for(Node*& p)//ham tim nut the mang
{
	Node* f = p, * q = p; //nut q,f a nut cha the mang cho nut q
	while (q->left != NULL)
	{
		f = q; //luu nut cha cua q
		q = q->left; //q qua ben trai
	}
	p->data = q->data;//tim duoc ptu the mang cho p la q
	if (f == p) //neu cha cua q la p
	{
		f->right = q->right;
	}
	else
	{
		f->left = q->right;
	}
	return q; //tra ve nut q la nut the mang cho p
}
int delete_node(Node*& root, int x) //ham xoa nut
{
	if (root == NULL) //khi cay rong ta return ve 0
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
		//root->data=x, tim nut the mang cho root
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
			delete p; //xoa nut q la nut the mang cho p
		}
		return 1;
	}
}
int count_smaller_node(Node* root, int x) //ham dem node nho hon x 
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
	result += count_smaller_node(root->left, x);
	result += count_smaller_node(root->right, x);
	return result;
}
int count_large_node(Node* root, int x) ////ham dem node lon hon x 
{
	int result = 0;
	if (root == NULL)
	{
		return 0;
	}
	if (root->data > x)
	{
		result++;
	}
	result += count_large_node(root->left, x);
	result += count_large_node(root->right, x);
	return result;
}
int find_min(Node* root) //ham tim nut nho nhat
{
	Node* p = root;
	while (p->left != NULL)
	{
		p = p->left;
	}
	return p->data;
}
int find_max(Node* root) //ham tim nut lon nhat
{
	Node* p = root;
	while (p->right != NULL)
	{
		p = p->right;
	}
	return p->data;
}

void show_level_k(Node* root, int k)
{
	if (!root)
	{
		return;
	}
	if (k == 0) //đến mức cần tìm
	{
		cout << root->data;
	}
	k--; //Mức k giảm dần về 0
	show_level_k(root->left, k); //đệ quy trái
	show_level_k(root->right, k);//đệ quy phải
}
void show_leaf(Node* root, int k)
{
	if (!root)
	{
		return;
	}
	if (k == 0 && !root->left && !root->right) //đến mức cần tìm
	{
		cout << root->data;
	}
	k--; //Mức k giảm dần về 0
	show_leaf(root->left, k); //đệ quy trái
	show_leaf(root->right, k);//đệ quy phải
}
void show_one_child(Node* root, int k)
{
	if (!root)
	{
		return;
	}
	if (k == 0 && ((!root->left && root->right) || (root->left && !root->right))) //đến mức cần tìm
	{
		cout << root->data;
	}
	k--; //Mức k giảm dần về 0
	show_one_child(root->left, k); //đệ quy trái
	show_one_child(root->right, k);//đệ quy phải
}
void show_two_child(Node* root, int k)
{
	if (!root)
	{
		return;
	}
	if (k == 0 && root->left && root->right) //đến mức cần tìm
	{
		cout << root->data;
	}
	k--; //Mức k giảm dần về 0
	show_two_child(root->left, k); //đệ quy trái
	show_two_child(root->right, k);//đệ quy phải
}

int count_level_k(Node* root, int k)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	if (k == 0) //đến mức cần tìm
	{
		result++;
	}
	k--; //Mức k giảm dần về 0
	result += count_level_k(root->left, k); //đệ quy trái
	result += count_level_k(root->right, k);//đệ quy phải
	return result;
}
int count_leaf(Node* root, int k)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	if (k == 0 && !root->left && !root->right) //đến mức cần tìm
	{
		result;
	}
	k--; //Mức k giảm dần về 0
	result += count_leaf(root->left, k); //đệ quy trái
	result += count_leaf(root->right, k);//đệ quy phải
	return result;
}
int count_one_child(Node* root, int k)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	if (k == 0 && ((!root->left && root->right) || (root->left && !root->right))) //đến mức cần tìm
	{
		result++;
	}
	k--; //Mức k giảm dần về 0
	result += count_one_child(root->left, k); //đệ quy trái
	result += count_one_child(root->right, k);//đệ quy phải
	return result;
}
int count_two_child(Node* root, int k)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	if (k == 0 && root->left && root->right) //đến mức cần tìm
	{
		result++;
	}
	k--; //Mức k giảm dần về 0
	result += count_two_child(root->left, k); //đệ quy trái
	result += count_two_child(root->right, k);//đệ quy phải
	return result;
}
int sum_negetive(Node* root) //ham tim node am
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	if (root->data < 0)
	{
		result += root->data;
	}
	result += sum_negetive(root->left);
	result += sum_negetive(root->right);
	return result;
}
int sum_positive(Node* root) //ham tim node duong
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	if (root->data > 0)
	{
		result += root->data;
	}
	result += sum_positive(root->left);
	result += sum_positive(root->right);
	return result;
}
int min_distane(Node* root, int x) //ham tim khoang cach gan nhat
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
	while (maxright->right!= NULL)
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

//++++++++++++++++SO NGUYEN TO++++++++++++++++
int prime_number(int x) //ham so ng to 
{
	if (x < 2)
	{
		return 0;
	}
	for (int i = 2; i <= sqrt(x); i++)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	return 1;
}
void delete_prime(Node*& root) //ham xoa so ng to
{
	if (root)
	{
		delete_prime(root->left);
		delete_prime(root->right);
		if (prime_number(root->data))
		{
			delete_node(root, root->data);
		}
	}
}
void show_prime(Node* root) //ham xuat so ng to 
{
	int result = 0;
	if (!root)
	{
		return;
	}
	else
	{
		if (prime_number(root->data))
		{
			cout << root->data<<" ";
		}
		show_prime(root->left);
		show_prime(root->right);
	}
}
int sum_prime(Node* root)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	else
	{
		if (prime_number(root->data))
		{
			result += root->data;
		}
		result += sum_prime(root->left);
		result += sum_prime(root->right);
	}
	return result;
}

//++++++++++++++++SO CHINH PHUONG++++++++++++++++
int square_number(int x)
{
	for (int i = 2; i * i <= x; i++)
	{
		if (i * i == x)
		{
			return 1;
		}
	}
	return 0;
}
void show_square(Node* root)
{
	if (!root)
	{
		return;
	}
	else
	{
		if (square_number(root->data))
		{
			cout << root->data << " ";
		}
		show_square(root->left);
		show_square(root->right);
	}
}
int sum_square(Node* root)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	else
	{
		if (square_number(root->data))
		{
			result += root->data;
		}
		result += sum_square(root->left);
		result += sum_square(root->right);
	}
	return result;
}
//++++++++++++++++SO HOAN HAO++++++++++++++++
int prefect_number(int n)
{
	int sum = 0;
	for (int i = 1; i <= n / 2; i++)
	{
		if (n % i == 0)
		{
			sum += i;
		}
	}
	if (sum == n)
	{
		return 1;
	}
	return 0;
}
int sum_prefect(Node* root)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	else
	{
		if (prefect_number(root->data))
		{
			result += root->data;
		}
		result += sum_prefect(root->left);
		result += sum_prefect(root->right);
	}
	return result;
}
void show_prefect(Node* root)
{
	if (!root)
	{
		return;
	}
	else
	{
		if (prefect_number(root->data))
		{
			cout << root->data<< " ";
		}
		show_prefect(root->left);
		show_prefect(root->right);
	}
}

//++++++++++++++++SO THINH VUONG++++++++++++++++
int prosperity_number(int n)
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (n % i == 0)
		{
			sum += i;
		}
	}
	if (sum > n)
	{
		return 1;
	}
	return 0;
}
void show_prosperity(Node* root)
{
	if (!root)
	{
		return;
	}
	else
	{
		if (prosperity_number(root->data))
		{
			cout << root->data << " ";
		}
		show_prosperity(root->left);
		show_prosperity(root->right);
	}
}
int sum_properity(Node* root)
{
	int result = 0;
	if (!root)
	{
		return 0;
	}
	else
	{
		if (prosperity_number(root->data))
		{
			result += root->data;
		}
		result += sum_properity(root->left);
		result += sum_properity(root->right);
	}
	return result;
}
Node* negative_max(Node* root)
{
	Node* p = root;
	if (root->data < 0)
	{
		while (p->right != NULL && p->data < 0)
		{
			p = p->right;
		}
		return p;
	}
	else
	{
		while (p->left != NULL && p->data < 0)
		{
			p = p->left;
		}
		return p;
	}
}
int main()
{
	int chon, a[50] = { 1,2,3,4,5 };
	int x;
	char file[] = "data.txt";
	Tree bt;
	Node* p, * root;
	cout << "==============MENU==============" << endl;
	cout << "1. tao cay thu cong " << endl;
	cout << "2. tao cay tu mang " << endl;
	cout << "3. tao cay tu dong " << endl;
	cout << "4. tao cay tu doc file (C) " << endl;
	cout << "5. tao cay tu doc file ( C++ ) " << endl;
	cout << "6. duyet cay " << endl;
	cout << "7. duyet cay theo chieu rong NRL va NLR " << endl;
	cout << "8. duyet cay theo chieu sau " << endl;
	cout << "9. them nut x " << endl;
	cout << "10. tim nut x " << endl;
	cout << "11. xoa nut x " << endl;
	cout << "12. dem so co gia tri trong khoang [x,y] " << endl;
	cout << "13. tim max va min " << endl;
	cout << "14. xuat nut o muc K,nut la, nut 1 con, nut 2 con o muc K " << endl;
	cout << "15. tinh tong nut am va tong nut duong " << endl;
	cout << "16. tim khoang cach xa nhat va khoang cach gan nhat " << endl;
	cout << "17. tim So Nguyen To va tinh tong So Nguyen To " << endl;
	cout << "18. tim So Chinh Phuong va tinh tong So Chinh Phuong " << endl;
	cout << "19. tim So Hoan Hoa va tinh tong So Hoan Hoa " << endl;
	cout << "20. tim So Thinh Vuong va tinh tong So Thinh Vuong " << endl;
	cout << "21. xoa So Nguyen To " << endl;
	cout << "22. tim max am " << endl;
	cout << "=================================" << endl;
	cout << "moi bn chon bai : ";
	cin >> chon;
	switch (chon)
	{
	case 1:
		create_tree(bt);
		cout << "duyet cay theo NLR : ";
		breadth_NLR_stack(bt.root);
		break;
	case 2:
		create_tree_array(bt, a);
		cout << "duyet cay theo NLR : ";
		breadth_NLR_stack(bt.root);
		break;
	case 3:
		create_tree_auto(bt);
		cout << "duyet cay theo NLR : ";
		breadth_NLR_stack(bt.root);
		break;
	case 4: //============= DOC FILE C ============= 
		taoFile(bt, file);
		cout << "Duyet theo NLR: ";
		breadth_NLR_stack(bt.root);
		cout << endl;
		break;
	case 5: //============= DOC FILE C++ ============= 
		read_file(bt, file);
		cout << "Duyet theo NLR: ";
		breadth_NLR_stack(bt.root);
		cout << endl;
		break;
	case 6:
		create_tree(bt);
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
	case 7:
		create_tree(bt);
		cout << "duyet cay theo chieu rong NLR : ";
		breadth_NLR_queue(bt.root);
		cout << endl;
		cout << "duyet cay theo chieu rong NRL : ";
		breadth_NRL(bt.root);
		cout << endl;
		break;
	case 8:
		create_tree(bt);
		cout << "duyet cay theo chieu sau NLR : ";
		depth_NLR(bt.root);
		break;
	case 9:
		create_tree(bt);
		cout << "nhap gia tri can them : ";
		cin >> x;
		insert_node(bt.root, create_node(x));
		cout << "duyet cay theo chieu rong NLR : ";
		breadth_NLR_stack(bt.root);
		break;
	case 10:
		create_tree(bt);
		cout << "nhap gia tri can tim : ";
		cin >> x;
		if (find_node(bt.root, x) != NULL)
		{
			cout << "tim thay x ";
		}
		else
		{
			cout << "khong tim thay x ";
		}
		break;
	case 11:
		create_tree(bt);
		cout << "nhap gia tri can xoa : ";
		cin >> x;
		delete_node(bt.root, x);
		cout << "duyet cay theo chieu rong NLR : ";
		breadth_NLR_stack(bt.root);
		break;
	case 12:
		create_tree(bt);
		cout << "so ptu nho hon X : ";
		cout << count_smaller_node(bt.root, 50) << endl;
		cout << "so ptu lon hon X : ";
		cout << count_large_node(bt.root, 50);
		break;
	case 13:
		create_tree(bt);
		cout << "ptu lon nhat : " << find_max(bt.root) << endl;
		cout << "ptu nho nhat : " << find_min(bt.root);
		break;
	case 14:
		create_tree(bt);
		cout << "so nut muc k : " << count_level_k(bt.root, 2) << endl;
		cout << "La : ";
		show_level_k(bt.root, 2);
		cout << endl;
		cout << "so nut la muc k : " << count_leaf(bt.root, 2) << endl;
		cout << "La : ";
		show_leaf(bt.root, 2);
		cout << endl;
		cout << "so nut 1 con muc k : " << count_one_child(bt.root, 2) << endl;
		cout << "La : ";
		show_one_child(bt.root, 2);
		cout << endl;
		cout << "so nut 2 con muc k : " << count_two_child(bt.root, 2) << endl;
		cout << "La : ";
		show_two_child(bt.root, 2);
		break;
	case 15: 
		create_tree(bt);
		cout << "tong nut am : " << sum_negetive(bt.root) << endl;
		cout << "tong nut duong : " << sum_positive(bt.root) << endl;
		break;
	case 16: 
		create_tree(bt);
		cout << "nhap gtri can tim khoang cach : ";
		cin >> x;
		cout << "khoang cach gan nhat : " << min_distane(bt.root, x) << endl;
		cout << "khoang cach xa nhat : " << max_distance(bt.root, x);
		break;
	case 17: 
		create_tree(bt);
		cout << "so ng to : ";
		show_prime(bt.root);
		cout << endl;
		cout << "tong so ng to : "<<sum_prime(bt.root);
		break;
	case 18: 
		create_tree(bt);
		cout << "so chinh phuong : ";
		show_square(bt.root);
		cout << endl;
		cout << "tong so chinh phuong : " << sum_square(bt.root);
		break;
	case 19:
		create_tree(bt);
		cout << "so hoan hao : ";
		show_prefect(bt.root);
		cout << endl;
		cout << "tong so hoan hao : " << sum_prefect(bt.root);
		break;
	case 20:
		create_tree(bt);
		cout << "so thinh vuong : ";
		show_prosperity(bt.root);
		cout << endl;
		cout << "tong so thinh vuong : " <<sum_properity(bt.root);
		break;
	case 21: 
		create_tree(bt);
		cout << "so nguyen to : ";
		show_prime(bt.root);
		cout << endl;
		cout << "cac so sau khi xoa so nguyen to : ";
		delete_prime(bt.root);
		breadth_NLR_queue(bt.root);
		break;
	case 22: 
		create_tree(bt);
		p = negative_max(bt.root);
		if (p)
		{
			cout << "max am : "<<p->data;
		}
		break;
	default: cout<<"bn nhap sai cu phap. Vui long nhap lai ";
		break;
	}
}