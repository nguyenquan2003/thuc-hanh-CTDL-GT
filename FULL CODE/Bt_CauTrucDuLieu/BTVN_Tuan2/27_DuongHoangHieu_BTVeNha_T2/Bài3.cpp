#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct SinhVien
{
	char maSV[50];
	char hoTen[50];
	char dChi[50];
	char nganhHoc[40];
	float dTB;
	struct Date
	{
		int day;
		int month;
		int year;

	}ngaySinh;
	char diemChu[10];
	char xepLoai[10];

};





void docFile(SinhVien a[], int&n)
{
	FILE* f;
	f = fopen("imputSV.txt", "r");
	if (f == NULL)
	{
		printf("Loi file !!!");
		getch();
		exit(1);
	}

	fscanf(f, "%d", &n);

	for (int i = 0; i<n; i++)
	{
		fscanf(f, "%s", a[i].maSV);
		char c;
		fscanf(f, "%c", &c);

		fgets(a[i].hoTen, 50, f);
		a[i].hoTen[strlen(a[i].hoTen) - 1] = '\0';

		fscanf(f, "%s", a[i].dChi);
		fscanf(f, "%s", a[i].nganhHoc);
		fscanf(f, "%f", &a[i].dTB);
		fscanf(f, "%d/%d/%d", &a[i].ngaySinh.day, &a[i].ngaySinh.month, &a[i].ngaySinh.year);


	}
	fclose(f);
}

//void ghiFile(SinhVien a[], int n)
//{
//	FILE*f = fopen("outputsv.txt", "w");
//	if (f == NULL)
//	{
//		printf("Loi tao file");
//		getch();
//		exit(1);
//	}
//	fprintf(f, "%s", "So luong sinh vien: ");
//	fprintf(f, "%d\n", n);
//	fprintf(f, "%10s %20s %10s\n", "MSSV", "HOTEN", "DIACHI","NGANHHOC","DIEM","NGAYSINH","DIEMCHU","XEPLOAI");
//	for (int i = 0; i < n; i++)
//		fprintf(f, "\n%s \n%s \n%s  \n%s \n%.1f  \n%d/%d/%d \n%s \n%s",
//		a[i].maSV, a[i].hoTen, a[i].dChi, a[i].nganhHoc, a[i].dTB, a[i].ngaySinh.day, a[i].ngaySinh.month, a[i].ngaySinh.year, a[i].diemChu, a[i].xepLoai);
//	fclose(f);
//	printf("\n Write success to file!\n");
//
//
//}

void xuatFile(SinhVien a[], int n)
{
	printf("------------Danh sach sinh vien------------");
	//printf("\n%10s %20s %10s", "MSSV", "HOTEN", "DIEM");
	for (int i = 0; i<n; i++)
	{
		printf("\n%s \n%s \n%s  \n%s \n%.1f  \n%d/%d/%d",
			a[i].maSV, a[i].hoTen, a[i].dChi, a[i].nganhHoc, a[i].dTB, a[i].ngaySinh.day, a[i].ngaySinh.month, a[i].ngaySinh.year);
	}
}
void nhapTTSV(SinhVien &x)
{
	printf("\nNhap ma so sinh vien:");
	flushall();
	gets(x.maSV);
	printf("\nNhap ho va ten cua sv:");
	flushall();
	gets(x.hoTen);
	printf("\n Nhap vao dia chi:");
	flushall();
	gets(x.dChi);
	printf("\n Nhap vao nganh hoc:");
	flushall();
	gets(x.nganhHoc);
	printf("\nNhap vao diem trung binh:");
	scanf("%f", &x.dTB);
	printf("\n Nhap vao ngay sinh:");
	scanf("%d/%d/%d", &x.ngaySinh.day, &x.ngaySinh.month, &x.ngaySinh.year);


}
void xuatTTSV(SinhVien x)
{


	printf("\nMa so: %5s\n Ho ten:%5s\n Dia chi:%5s\n Nganh hoc:%5s\n Diem TB:%5f Ngay sinh:%5d/%d/%d", x.maSV, x.hoTen, x.dChi, x.nganhHoc, x.dTB, x.ngaySinh.day, x.ngaySinh.month, x.ngaySinh.year);
}
void nhapDSSV(SinhVien a[], int &n)
{
	printf("\n Danh sach sinh vien co:");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("\n Nhap sv thu %d:", i + 1);
		nhapTTSV(a[i]);
	}

}


void xuatDSSV(SinhVien a[], int n)
{

	for (int i = 0; i < n; i++)
	{
		printf("\t\t\nThong tin sinh vien thu:%d", i + 1);
		xuatTTSV(a[i]);
	}
}
void swap(SinhVien &x, SinhVien&y)
{
	SinhVien t = x;
	x = y;
	y = t;
}
void sX_DS_Giam_TheoDiem(SinhVien a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	for (int j = i + 1; j < n; j++)
	if (a[i].dTB < a[i].dTB)
		swap(a[i], a[j]);

}
void saXep(SinhVien a[], int n)
{
	sX_DS_Giam_TheoDiem(a, n);
}
void main()
{
	SinhVien a[50];
	SinhVien x;
	int n;
	/*docFile(a, n);
	xuatFile(a, n);*/
	//ghiFile(a, n);

	nhapDSSV(a, n);
	xuatDSSV(a, n);
	nhapTTSV(x);
	xuatTTSV(x);
	/*sX_DS_Giam_TheoDiem(a, n);
	printf("Diem duoc sap xep giam dan");*/
	getch();
}