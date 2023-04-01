#include "BaiHat.h"

void nhapBH(BaiHat& x)
{
	printf("Nhap ten BH: ");
	scanf("%s", &x.tenBH);
	printf("Nhap ten TG: ");
	scanf("%s", &x.tenTG);
	printf("Nhap ten CS: ");
	scanf("%s", &x.tenCS);
	printf("Nhap thoi luong: ");
	scanf("%d", &x.thoiLuong);
}
void xuatBH(BaiHat x)
{
	printf("%-25s%-20s%-20s%10d\n", x.tenBH, x.tenTG, x.tenCS, x.thoiLuong);
}
void xuatTieuDe()
{
	printf("%-25s%-20s%-20s%10s\n", "TenBH", "TenTG", "TenCS", "ThoiLuong");
	int i = 0;
	while (i++ < 75) printf("-");
	printf("\n");
}
//void main()
//{
//	BaiHat x;
//	nhapBH(x);
//	xuatBH(x);
//
//	system("pause");
//}