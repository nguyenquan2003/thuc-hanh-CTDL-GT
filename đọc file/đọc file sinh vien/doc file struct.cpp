#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;
struct date
{
	int ngay, thang, nam;
};
struct sinhvien
{
	string ho_ten, ma_sv;
	float diem_tb;
	date ngay_sinh;
};
struct Node
{
	sinhvien data;
	Node* next;
};
struct List
{
	Node* head, * tail;
};

Node* create_node(sinhvien x)
{
	Node* p = new Node;
	if (p == NULL)
	{
		cout << "khong du bo nho cap phat ! ";
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}
void inint_list(List& l) //ham khoi tao node
{
	l.head = l.tail = NULL;
}
void insert_head(List& l, Node* p) //them vao dau ds
{
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else
	{
		p->next = l.head;
		l.head = p;
	}
}
void insert_tail(List& l, Node* p) //them vao cuoi ds
{
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else
	{
		l.tail->next = p;
		l.tail = p;
	}
}

void read_date(ifstream &file,date &date) //ham doc ngay thang nam 
{
	file >> date.ngay;
	file.seekg(1, 1); //dich sang phai 1 byte de bo qua ki tu /
	file >> date.thang;
	file.seekg(1, 1);
	file >> date.nam;
}
void read_file_1_sv(ifstream &file, sinhvien& sv) //ham doc 1 sv
{
	getline(file, sv.ho_ten,','); //doc den dau , thi dung
	file.seekg(1, 1); //tai vt hien tai dich sang phai 1 byte de bo khoang trang
	
	getline(file, sv.ma_sv, ',');
	file.seekg(1, 1);

	read_date(file, sv.ngay_sinh);
	file.seekg(2, 1);

	file >> sv.diem_tb;

	//tao bien tam de ki tuu xuong dong
	string temp;
	getline(file, temp);
}
void read_file_text_sv(ifstream& file, List& l)
{
	while (!file.eof())//doc den cuoi file thi dung
	{
		sinhvien sv;
		read_file_1_sv(file, sv);
		Node* p = create_node(sv);
		insert_tail(l, p); //them sv vao dslk
	};
}

void output(sinhvien sv)
{
	cout << "ho ten : " << sv.ho_ten<<endl;
	cout << "ma sinh vien : " << sv.ma_sv << endl;;
	cout << "ngay sinh : " << sv.ngay_sinh.ngay << "/" << sv.ngay_sinh.thang << "/" << sv.ngay_sinh.nam << endl;
	cout << "diem trung binh : " << sv.diem_tb<<endl;
}
void output_sv(List& l)
{
	int result = 1;
	for (Node* k = l.head; k != NULL; k = k->next)
	{
		cout << "========================================" << endl;
		cout << "\tSINH VIEN THU " << result++ << endl;
		output(k->data);
	}
}
void Swap(sinhvien& x, sinhvien& y) //doi cho
{
	swap(x, y);
}
void sort_up(List& l) //sap xep tang dan
{
	for (Node* k = l.head; k != NULL; k = k->next)
	{
		for (Node* h = k->next; h != NULL; h = h->next)

		{
			if (k->data.diem_tb > h->data.diem_tb)
			{
				Swap(k->data, h->data);
			}
		}
	}
}
void write_info_1sv(ofstream& file, sinhvien sv) //ghi thong tin 1 sv
{
	file << sv.ho_ten << ",";
	file << sv.ma_sv << ",";
	file << sv.ngay_sinh.ngay << "/" << sv.ngay_sinh.thang << "/" << sv.ngay_sinh.nam << ",";
	file << sv.diem_tb;
}
void save_sort_up(List l) //luu file sap xep tang dan theo diem tb
{
	ofstream file;
	file.open("sapxepdiemmax.txt", ios::out);
	sort_up(l);
	for (Node* k = l.head; k != NULL; k = k->next)
	{
		write_info_1sv(file, k->data);
		file << endl;
	}
}
void write_file_diemtb_max(List l)
{
	float max = l.head->data.diem_tb;
	for (Node* k = l.head->next; k != NULL; k = k->next)
	{
		if (max < k->data.diem_tb)
		{
			max = k->data.diem_tb;
		}
	}
	ofstream file;
	file.open("diemtbmax.txt", ios::out);
	for (Node* k = l.head; k != NULL; k = k->next)
	{
		if (max == k->data.diem_tb)
		{
			write_info_1sv(file,k->data);
			file << endl;
		}
	}
}
int main()
{
	List l;
	inint_list(l);
	sinhvien sv;
	ifstream file;
	file.open("sv.txt", ios::in);
	read_file_text_sv(file, l);
	output_sv(l);
	write_file_diemtb_max(l); //ghi thong tin sinh vien diem tb max
	file.close();




	//doc file voi nhiu sv
	//List l;
	//inint_list(l);
	//sinhvien sv;
	//ifstream file;
	//file.open("sv.txt", ios::in);
	//read_file_text_sv(file, l);
	//output_sv(l);
	//save_sort_up(l); //xuat ra file sap xep dien tb tang dan 
	//file.close();


	//doc file voi 1 sv
	/*sinhvien sv;
	ifstream file;
	file.open("sv.txt", ios::in);
	read_file_1_sv(file, sv);
	output(sv);
	file.close();
	return 0;*/
}