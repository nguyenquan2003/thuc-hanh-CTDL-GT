#include "MyPhanSo.h"


void nhapPS(PhanSo &x)
{
	printf("tu: "); scanf("%d", &x.tu);
	printf("mau: "); scanf("%d", &x.mau);
}
void inPS(PhanSo x)
{
	printf("(%d/%d) ", x.tu, x.mau);
}
int UCLN(int a, int b)
{
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == 0 || b == 0) return a + b;

	while (b != 0)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
void rutGon(PhanSo& x)
{
	int uc = UCLN(x.tu, x.mau);
	x.tu /= uc;
	x.mau /= uc;
}
//a = b <=> a - b = 0
//a < b <=> a - b < 0
//a > b <=> a - b > 0
int soSanh(PhanSo a, PhanSo b)
{
	return a.tu*b.mau - b.tu*a.mau;
}

bool operator == (PhanSo a, PhanSo b)
{
	return soSanh(a, b) == 0;
}
bool operator != (PhanSo a, PhanSo b)
{
	return soSanh(a, b) != 0;
}
bool operator < (PhanSo a, PhanSo b)
{
	return soSanh(a, b) < 0;
}
bool operator > (PhanSo a, PhanSo b)
{
	return soSanh(a, b) > 0;
}

PhanSo cong(PhanSo a, PhanSo b)
{
	PhanSo c;
	c.tu = a.tu * b.mau + b.tu*a.mau;
	c.mau = a.mau*b.mau;
	rutGon(c);
	return c;
}
PhanSo operator + (PhanSo a, PhanSo b)
{
	return cong(a, b);
}

bool doc1PS(FILE*fp, PhanSo& x)
{
	return fscanf(fp, "%d%d", &x.tu, &x.mau) == 2;
}

