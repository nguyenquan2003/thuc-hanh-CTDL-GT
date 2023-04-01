#include<stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

struct sinhVien
{
	char mssv[11];
	char hoTen[30];
	char diaChi[50];
	int ngay;
	int thang;
	int nam;
	char nganhHoc[50];
	float diemTB;
	int tuoi;
	char diemChu[3];
	char xepLoai[15];
	float dtb;
	char hocluc[10];
	float diemToan, diemLy, diemHoa;
};
	void docFile(sinhVien a[], int &n);
	void nhapDSSV(sinhVien a[], int &n);
	void xuatDSSV(sinhVien a[], int &n);
	void timKiemTheoNganhHoc(sinhVien a[], int &n);
	void tinhDTB(sinhVien &a);
	void tinhTuoiSinhVien(sinhVien a, int &n);
	void xeploai(sinhVien &sv);
	void ghiFile(sinhVien a[], int n, char fileName[]);

	void nhapSV(sinhVien a)
{
	printf("nhap ma so sinh vien:\n");
	fflush(stdin);
	gets(a.mssv);
	printf("nhap ho ten sinh vien:\n");
	gets(a.hoTen);
	printf("nhap ngay sinh cua sinh vien:\n");
	scanf("%d", a.ngay);
	printf("nhap thang sinh cua sinh vien:\n");
	scanf("%d", a.thang);
	printf("nhap nam sinh cua sinh vien:\n");
	scanf("%d", a.nam);
	printf("nhap dia chi cua sinh vien:\n");
	gets(a.diaChi);
	printf("nhap nganh hoc cua sinh vien:\n");
	gets(a.nganhHoc);
	printf(" Nhap diem Toan: ");
	scanf(".2%f", a.diemToan);
	printf(" Nhap diem Ly: ");
	scanf("%.2f", a.diemLy);
	printf(" Nhap diem Hoa: ");
	scanf("%.2f", a.diemHoa);
	tinhDTB(a);
	xeploai(a);
	tinhTuoiSinhVien(a);
}
void nhapDSSV(sinhVien a[], int &n)
{
	printf("nhap so luong sinh vien\n");
	scanf("%d", &n);
	for (int i = 0; i<n; i++)
	{
		printf(" \tsinh vien thu %d:\n", i + 1);
		nhapSV(a[i]);
	}
}
void xuatSV(sinhVien a)
{
	printf("\tmssv:%s\n \thoten:%s\n \tngaysinh:%d\n \tthangsinh:%d\n \tnamsinh:%d\n \tdiachi:%s\n \tnganhhoc:%s\n \tdiemtb:%.2f\n \tdiemChu:%s\n \txeploai:%s\n", a.mssv, a.hoTen, a.ngay, a.thang, a.nam, a.nganhHoc, a.diaChi, a.diemTB, a.diemChu, a.xepLoai);
	printf("\t diem toan cua ban la:%.2f\n", a.diemToan);
	printf("\t diem ly cua ban la:%.2f\n", a.diemLy);
	printf("\t diem hoa cua ban la:%.2f\n", a.diemHoa);
	printf("\t diem trung binh cua ban la:%.2f\n\n", a.dtb);
	tinhDTB(a);
	xeploai(a);
}
void xuatDSSV(sinhVien a[], int &n)
{
	for (int i = 0; i<n; i++)
	{
		xuatSV(a[i]);
		printf("\n");
	}
}
void docFile(sinhVien a[],int &n)
{
	FILE *s;
	s= fopen("SinhVien.txt","r");
	fscanf(s,"%d",&n);
	for(int i=0;i<n;i++)
	{
		fscanf(s,"%s",&a[i].mssv);
		fscanf(s,"%s",&a[i].hoTen);
		fscanf(s,"%s",&a[i].ngay);
		fscanf(s,"%s",&a[i].diaChi);
		fscanf(s,"%s",&a[i].nganhHoc);
		fscanf(s,"%f",&a[i].diemTB);
		fscanf(s,"%s",&a[i].diemChu);
		fscanf(s,"%s",&a[i].xepLoai);
		fscanf(s,"%.2f",&a[i].diemToan);
		fscanf(s,"%.2f",&a[i].diemLy);
		fscanf(s,"%.2f",&a[i].diemHoa);
	}
	fclose;
}
void timKiemTheoNganhHoc(sinhVien a[], int &n)
{
	char tenNganh[30];
	printf("\n\t Moi ban nhap nganh hoc can tim la :");
	fflush(stdin);
	gets(tenNganh);
	int nH = 0;
	for (int i = 0; i<n; i++)
	if (a[i].nganhHoc == tenNganh)
	{
		printf("\n\t sinh vien thuoc nganh cong nghe thong tin la: %d", i + 1);
		printf("\n\t ten:%s", a[i].nganhHoc);
		nH++;
	}
	if (nH == 0)
		printf("\n\t Khong tim thay sinh vien nao thuoc nganh cong nghe thong tin", tenNganh);

}
void tinhTuoiSinhVien(sinhVien a, int &n)
{
	a.tuoi = (2019 - a.nam);
}
void tinhDTB(sinhVien &sv)
{
	sv.diemTB = (sv.diemToan + sv.diemLy + sv.diemHoa) / 3;
}
void xeploai(sinhVien &sv)
{
	if (sv.diemTB >= 8) strcpy(sv.hocluc, "Gioi");
	else if (sv.diemTB >= 6.5) strcpy(sv.hocluc, "Kha");
	else if (sv.diemTB >= 5) strcpy(sv.hocluc, "Trung binh");
	else strcpy(sv.hocluc, "Yeu");
}
//void ghiFile(sinhVien a[], int n, char fileName[]) 
//{
//  FILE * fp;
//fp = fopen (fileName,"w");
//for(int i = 0;i < n;i++){
//fprintf(fp, "%5d%30s%5s%5d%10f%10f%10f%10f%10s\n", a[i].mssv, a[i].hoTen,
//a[i].ngay, a[i].diemToan, a[i].diemLy, a[i].diemHoa, a[i].dtb);
//}
//fclose (fp);
//}
void main()
{
	sinhVien a[100];
	int n;
	nhapDSSV(a, n);
	docFile(a, n);
	//ghiFile(a,n);
	timKiemTheoNganhHoc(a, n);
	xuatDSSV(a, n);

	getch();
}





