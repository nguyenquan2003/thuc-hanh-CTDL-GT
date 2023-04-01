#include<conio.h>
#include<stdio.h>
#include<string.h>
struct Date
{
	int ngay;
	int thang;
	int nam;
};
struct HangHoa
{
	char Ma[10];
	char TenHang[21];
	float GB;
	Date NSX;
	int hangSD;
	int soLuong;
};
void xuat(HangHoa &hn);
void nhapMang(HangHoa a[], int &n);
void xuatMang(HangHoa a[], int n);
void docFile(HangHoa a[], int &n);
void xuatfile(HangHoa a[], int n);
void KTHangSD(HangHoa a[], int n);
void xuatHangGanHet(HangHoa a[], int n);
int demSH(HangHoa a[], int n);
int TongKhoHang(HangHoa a[], int n);
void xuatMHG(HangHoa a[], int n);
int demHMoi(HangHoa a[], int n);
void xuatMH2d3(HangHoa a[], int n);
void SXHanSD(HangHoa a[], int n);
void timMHSLMax(HangHoa a[], int n);
void timMHSLMax2(HangHoa a[], int n);

void xuat(HangHoa &hn)
{
	printf("\nMa: %s", hn.Ma);
	printf("\nTen: %s", hn.TenHang);
	printf("\nGia ban: %0.00f VND", hn.GB);
	printf("\ngay sx: %d/%d/%d", hn.NSX.ngay, hn.NSX.thang, hn.NSX.nam);
	printf("\nHang su dung: %d", hn.hangSD);
	printf("\nSo luong: %d", hn.soLuong);
}
void nhapMang(HangHoa a[], int &n)
{
	printf("Nhap so hang hoa: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("\n\t<<<Nhap Thong Tin Hang Hoa>>>>");
		printf("\nNhap Ma hang: ");
		scanf("%s", &a[i].Ma);
		printf("Nhap Ten Hang: ");
		scanf("%s", &a[i].TenHang);
		printf("Nhap Gia ban: ");
		scanf("%f", &a[i].GB);
		printf("Nhap Ngay: ");
		scanf("%d", &a[i].NSX.ngay);
		printf("Nhap Thang: ");
		scanf("%d", &a[i].NSX.thang);
		printf("Nhap Nam: ");
		scanf("%d", &a[i].NSX.nam);
		printf("Nhap hang su dung theo thang: ");
		scanf("%d", &a[i].hangSD);
		printf("Nhap so luong: ");
		scanf("%d", &a[i].soLuong);
	}
}
void xuatMang(HangHoa a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nMa: %s", a[i].Ma);
		printf("\nTen: %s", a[i].TenHang);
		printf("\nGia ban: %0.00f VND", a[i].GB);
		printf("\ngay sx: %d/%d/%d", a[i].NSX.ngay, a[i].NSX.thang, a[i].NSX.nam);
		printf("\nHang su dung: %d", a[i].hangSD);
		printf("\nSo luong: %d", a[i].soLuong);
	}
}
void docFile(HangHoa a[], int &n)
{
	FILE*f;
	f = fopen("HangHoa.TXT", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%s", &a[i].Ma);
		fscanf(f, "%s", &a[i].TenHang);
		fscanf(f, "%f", &a[i].GB);
		fscanf(f, "%d", &a[i].NSX.ngay);
		fscanf(f, "%d", &a[i].NSX.thang);
		fscanf(f, "%d", &a[i].NSX.nam);
		fscanf(f, "%d", &a[i].hangSD);
		fscanf(f, "%d", &a[i].soLuong);
	}
	fclose(f);
}
void xuatfile(HangHoa a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\n\t<<<<<Hang hoa thu %d>>>>>>>>", i + 1);
		xuat(a[i]);
	}
}
void KTHangSD(HangHoa a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i].hangSD + a[i].NSX.thang <= 2 && a[i].NSX.nam <= 2019 || a[i].hangSD + a[i].NSX.thang >= 2 && a[i].NSX.nam <= 2019)
			xuat(a[i]);
	}
}
void xuatHangGanHet(HangHoa a[], int n)
{
	for (int i = 0; i < n; i++)
	if (a[i].soLuong < 5)
	{
		xuat(a[i]);
	}
}
int demSH(HangHoa a[], int n)
{
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a[i].TenHang, "BanhDanisa") == 0)
			dem++;
	}
	return dem;
}
void swap(HangHoa & x, HangHoa & y)
{
	HangHoa t = x;
	x = y;
	y = t;
}
void SXHanSD(HangHoa a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i].hangSD < a[j].hangSD)
				swap(a[i], a[j]);
		}
		xuat(a[i]);
	}
}
int TongKhoHang(HangHoa a[], int n)
{
	int dem = 1;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a[0].Ma, a[i].Ma) != 0)
			dem++;
	}
	return dem;
}
void xuatMHG(HangHoa a[], int n)
{
	for (int i = 0; i<n; i++)
	{
		if (a[i].GB == 40000)
			xuat(a[i]);
	}
}
int demHMoi(HangHoa a[], int n)
{
	int dem = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i].NSX.thang == 3 && a[i].NSX.nam == 2019 || a[i].NSX.thang == 2 && a[i].NSX.nam == 2019)
			dem++;
	}
	return dem;
}
void xuatMH2d3(HangHoa a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i].hangSD >= 24 && a[i].hangSD <= 36)
			xuat(a[i]);
	}
}
void timMHSLMax(HangHoa a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		if (a[i].soLuong > a[j].soLuong)
			swap(a[i], a[j]);
	}
	xuat(a[0]);
}
void timMHSLMax2(HangHoa a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		if (a[i].soLuong > a[j].soLuong)
			swap(a[i], a[j]);
	}
	xuat(a[1]);
}

void main()
{
	HangHoa a[20];
	int n = 0;
	docFile(a, n);
	xuatfile(a, n);
	/*nhapMang(a,n);
	printf("\n\t<<<Thông tin hành hóa vua nhap>>>>");
	xuatMang(a,n);*/
	printf("\n\tCac san pham het han");
	KTHangSD(a, n);
	printf("\n\tsan pham xap het hang");
	xuatHangGanHet(a, n);
	printf("\nSo hang hoa ten BanhDanisa: %d", demSH(a, n));
	printf("\nTong so hang co trong kho: %d", TongKhoHang(a, n));
	printf("\n\tDanh sach mat hang gia 40000:");
	xuatMHG(a, n);
	printf("\nSo hang hoa moi san xuat: %d", demHMoi(a, n));
	printf("\nDanh sach mat hang co hang sd tu 2 den 3 nam: ");
	xuatMH2d3(a, n);
	printf("\n\tSap xep danh sach han gan den xa:");
	SXHanSD(a, n);
	printf("\n\tMat hang co so luong nhieu nhat:");
	timMHSLMax(a, n);
	printf("\n\tMat hang co so luong nhieu thý 2:");
	timMHSLMax2(a, n);
	getch();
}