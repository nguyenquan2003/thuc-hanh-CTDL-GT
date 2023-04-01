#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

#define MAXSIZE 1000

typedef char KeyType;

struct SINHVIEN
{
	KeyType MASV[10];
	char HOSV[25];
	char TENSV[8];
	char LOP[10];
	float DiemTB;

};


typedef SINHVIEN ItemType;

void DocFile(SINHVIEN sv[MAXSIZE], int &n)
{
	FILE* f;
	f = fopen("input.txt", "r");
	if (f == NULL)
	{

		printf("Loi Doc File!!!");
		getch();
		exit(1);

	}

	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{

		fscanf(f, "%s", sv[i].MASV);

		char c;
		fscanf(f, "%c", &c);

		fgets(sv[i].HOSV, 25, f);
		sv[i].HOSV[strlen(sv[i].HOSV) - 1] = '\0';
		fgets(sv[i].TENSV, 8, f);
		sv[i].TENSV[strlen(sv[i].TENSV) - 1] = '\0';
		fgets(sv[i].LOP, 10, f);
		sv[i].LOP[strlen(sv[i].LOP) - 1] = '\0';


		fscanf(f, "%f", &sv[i].DiemTB);

	}
	fclose(f);

}


void XuatDS(SINHVIEN sv[MAXSIZE], int n)
{

	printf("------------Danh sach sinh vien------------");
	printf("\n%10s %20s %10s %15s %10s", "MSSV", "HOLOT", "TEN", "LOP","DIEMTB");
	for (int i = 0; i<n; i++)
	{
		printf("\n%10s %20s %10s %15s %10.1f", sv[i].MASV, sv[i].HOSV, sv[i].TENSV,sv[i].LOP, sv[i].DiemTB);
	}


}


float Search_DTB_MAX(SINHVIEN sv[MAXSIZE], int n)
{
	float max = 0;
	for (int i = 0; i < n; i++)
	{
		if (sv[i].DiemTB > max)
			max = sv[i].DiemTB;
	}
	return max;
}

void XuatSV_DTBMAX(SINHVIEN sv[MAXSIZE], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (sv[i].DiemTB == Search_DTB_MAX(sv, n))
		{
			printf("\n%10s %20s %10s %15s %10s", "MSSV", "HOLOT", "TEN", "LOP", "DIEMTB");
			printf("\n%10s %20s %10s %15s %10.1f", sv[i].MASV, sv[i].HOSV, sv[i].TENSV, sv[i].LOP, sv[i].DiemTB);

		}
	}
}


int TimSV_X(SINHVIEN sv[MAXSIZE], int n, char x[10])
{

	for (int i = 0; i < n; i++)
	if (strcmp(sv[i].TENSV, x) == 0)
		return i;
	return -1;
}

void swap(SINHVIEN &a, SINHVIEN &b)
{
	SINHVIEN temp;
	temp = a;
	a = b;
	b = temp;


}

void xuat1sv(SINHVIEN &sv)
{
	printf("\n%10s %20s %10s %15s %10s", "MSSV", "HOLOT", "TEN", "LOP", "DIEMTB");
	printf("\n%10s %20s %10s %15s %10.1f", sv.MASV, sv.HOSV, sv.TENSV, sv.LOP, sv.DiemTB);

}
void InterChangeSoft_TangTheoTen(SINHVIEN sv[MAXSIZE], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		if (strcmp(sv[min].TENSV, sv[j].TENSV)>0)
			swap(sv[min], sv[j]);
	}



}


void SelectionSoft_TangTheoTen(SINHVIEN sv[MAXSIZE], int n)
{
	for (int i = 0; i < n - 1; i++)
	{

		int min = i;
		for (int j = i + 1; j < n; j++)
		if (strcmp(sv[min].TENSV, sv[j].TENSV)>0)
			min = j;
		if (min != i)
			swap(sv[i], sv[min]);
	}

}






void main()
{
	int n, chon;
	char x[10];
	SINHVIEN sv[MAXSIZE];
	DocFile(sv, n);
	XuatDS(sv, n);
	printf("\nMENU:\n");
	printf("1. Tim Sinh Vien co diem tb cao nhat\n2. Tim Kiem Sinh vien Ten X co trong danh sach hay khong?\n3. Sap Xep Tang dan theo ten!\n");
	printf("0. THOAT!!!\n");


	do
	{
		printf("\nChon Bai Tap:\n");
		scanf("%d", &chon);
		switch (chon)
		{
		case 1:
		{
				  printf("\nSinh Vien co diem Trung Binh cao nhat:");
				  Search_DTB_MAX(sv, n);
				  XuatSV_DTBMAX(sv, n);
		}break;

		case 2:
		{
				  printf("\nNhap Ten Sinh vien can tim: ");
				  scanf("%s", &x);
				  if (TimSV_X(sv, n, x) != -1)
				  {
					  printf("TIM THAY!!\nSinh vien ten '%s' trong danh sach!", x);
					  xuat1sv(sv[TimSV_X(sv, n, x)]);
				  }
				  else
					  printf("KHONG TIM THAY!!\nsinh vien '%s' trong danh sach!", x);
		}break;

		case 3:
		{
				  printf("\nDanh sach sau khi sap xep: \n");
				  /*InterChangeSoft_TangTheoTen(sv, n);*/
				  SelectionSoft_TangTheoTen(sv, n);
				  XuatDS(sv, n);

		}break;


		default:
			break;
		}

	} while (chon != 0);




	getch();

}

