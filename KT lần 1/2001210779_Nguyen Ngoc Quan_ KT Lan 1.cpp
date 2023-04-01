#include <iostream>
#include <string>
#include <fstream>
#include <stack>
using namespace std;
struct sinhvien
{
	string ma_sv, ho_ten, lop;
	float toan, ly, hoa;
};
struct Node
{
	sinhvien data;
	Node* next; //con tro chi den nut ke sau
};
struct dssv
{
	sinhvien sv;
	int n = 8;
};
struct List
{
	Node* head, * tail; //dc dau va dc cuoi trong ds
};

Node* create_node(sinhvien x)
{
	Node* p = new Node;
	if (p == NULL)
	{
		cout << "khong du bo nho cap phat ";
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}
void init_list(List& l) //tao list rong 
{
	l.head = l.tail = NULL;
}
int Is_Empty(List l) //kt ds rong
{
	if (l.head == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void show_node(Node* p) //xuat nd cua nut
{
	cout << p->data.ma_sv << " ";
	cout << p->data.ho_ten << " ";
	cout << p->data.lop << " ";
	cout << p->data.toan << " ";
	cout << p->data.ly << " ";
	cout << p->data.hoa << " ";
}
//Duyệt danh sách.
void show_list(List l)
{
	if (Is_Empty(l) == 1)
	{
		cout << "danh sach rong ";
		return;
	}
	cout << "Noi dung cua danh sach la: " << endl;
	for (Node* p = l.head; p != NULL; p = p->next)
	{
		show_node(p);
		cout << endl;
	}
}

//Thêm nút p có giá trị x vào đầu danh sách.
void insert_head(List& l, Node* p)
{
	if (p == NULL)
	{
		return; //Thực hiện không thành công
	}
	if (Is_Empty(l) == 1)
	{
		l.head = l.tail = p;
	}
	else
	{
		p->next = l.head;
		l.head = p;
	}
}
void insert_tail(List& l, Node* p)
{
	if (p == NULL)
	{
		return; //Thực hiện không thành công
	}
	if (Is_Empty(l) == 1)
	{
		l.head = l.tail = p;
	}
	else
	{
		l.tail->next = p;
		l.tail = p;
	}
	//Thực hiện thành công
}

string* splitString(string str)
{
	string* strArray = new string[6];
	int iStrArray = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '#')
		{
			iStrArray++;
		}
		else
		{
			strArray[iStrArray].push_back(str[i]);
		}
	}

	return strArray;
}

void read_file(List& l, string fileName)
{
	ifstream file;
	file.open(fileName, ios_base::in);

	if (file.fail())
		cout << "loi doc file ";
	else
	{
		while (!file.eof())
		{
			sinhvien x;

			string line;
			getline(file, line);
			string* strArray = splitString(line);

			x.ma_sv = strArray[0];
			x.ho_ten = strArray[1];
			x.lop = strArray[2];
			x.toan = stof(strArray[3]);
			x.ly = stof(strArray[4]);
			x.hoa = stof(strArray[5]);

			Node* newNode = create_node(x);
			insert_tail(l, newNode);
		}

	}
	file.close();
}
void create_text(List& l, char* filename) //tao ds tu file text
{
	int n = 0;
	ifstream in(filename);
	init_list(l);
	if (in)
	{
		in >> n;
		for (int i = 1; i <= n; i++)
		{
			Node* p;
			sinhvien sv;
			in >> sv.ma_sv;
			in >> sv.ho_ten;
			in >> sv.lop;
			in >> sv.toan;
			in >> sv.ly;
			in >> sv.hoa;
			p = create_node(sv);
			insert_tail(l, p);
		}
	}
	in.close();
}
void diem_tb(sinhvien& sv)
{
	float tb = (sv.toan + sv.ly + sv.hoa) / 3;
	cout << tb;
}
//void diem_tb(sinhvien &sv)
//{
//	float tb = (sv.toan + sv.ly + sv.hoa) / 3;
//	cout << tb;
//}

bool isOperator(char c)
{
	return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
{
	if (C == '-' || C == '+')
		return 1;
	else if (C == '*' || C == '/')
		return 2;
	else if (C == '^')
		return 3;
	return 0;
}

string infixToPostfix(string infix)
{
	infix = '(' + infix + ')';
	int l = infix.size();
	stack<char> char_stack;
	string output;

	for (int i = 0; i < l; i++) {

		// If the scanned character is an
		// operand, add it to output.
		if (isalpha(infix[i]) || isdigit(infix[i]))
			output += infix[i];

		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (infix[i] == '(')
			char_stack.push('(');

		else if (infix[i] == ')') {
			while (char_stack.top() != '(') {
				output += char_stack.top();
				char_stack.pop();
			}

			// Remove '(' from the stack
			char_stack.pop();
		}

		// Operator found
		else
		{
			if (isOperator(char_stack.top()))
			{
				if (infix[i] == '^')
				{
					while (getPriority(infix[i]) <= getPriority(char_stack.top()))
					{
						output += char_stack.top();
						char_stack.pop();
					}

				}
				else
				{
					while (getPriority(infix[i]) < getPriority(char_stack.top()))
					{
						output += char_stack.top();
						char_stack.pop();
					}

				}

				// Push current Operator on stack
				char_stack.push(infix[i]);
			}
		}
	}
	while (!char_stack.empty()) {
		output += char_stack.top();
		char_stack.pop();
	}
	return output;
}

string infixToPrefix(string infix)
{
	int l = infix.size();
	reverse(infix.begin(), infix.end());
	for (int i = 0; i < l; i++) {

		if (infix[i] == '(') {
			infix[i] = ')';
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
		}
	}

	string prefix = infixToPostfix(infix);

	// Reverse postfix
	reverse(prefix.begin(), prefix.end());

	return prefix;
}

int main()
{
	List l;
	string file = "text.txt";
	init_list(l);
	int chon;
	Node* p;
	sinhvien x;
	string s;
	init_list(l);
	cout << "===============MENU===============" << endl;
	cout << "1. doc file " << endl;
	cout << "2. diem tb " << endl;
	cout << "3. trung to sang tien to " << endl;
	cout << "===============MENU===============" << endl;
	cout << "moi ban chon bai : ";
	cin >> chon;
	switch (chon)
	{
	case 1:read_file(l, file);
		show_list(l);
		break;
	case 2: diem_tb(x);
		break;
	case 3 : cout << "nhap chuoi : ";
		cin >> s;
		cout <<"ket qua : "<< infixToPrefix(s) << endl;
		return 0;
	default:
		break;
	}
}