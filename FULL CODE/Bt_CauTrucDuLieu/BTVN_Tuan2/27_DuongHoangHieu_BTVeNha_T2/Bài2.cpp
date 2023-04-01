//#include <conio.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <ctime>
//#include <cstdlib>
//#include <time.h>
//
//
//void RandomMang2Chieu(int a[][100], int &n, int &m)
//{
//	printf("Nhap so dong: ");
//	scanf("%d", &n);
//	printf("Nhap So cot: ");
//	scanf("%d", &m);
//
//	srand(time(NULL));
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < m; j++)
//			{				
//				a[i][j] = rand() % 100;
//			}
//}
//
//void XuatMang(int a[][100], int &n, int &m)
//{
//	
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < m; j++)
//		{
//			printf("%5d", a[i][j]);
//		}
//		printf("\n");
//	}
//
//
//}
//
//
//void LinearSearch_Mang2Chieu(int a[][100], int &n,int &m, int &x)
//{
//	int d=0, c=0;
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < m;j++)
//			{
//				if (a[i][j] == x)
//					{
//						d = i+1;
//						c = j+1;												
//					}
//			}
//		printf("Tim Thay so X= %d o Dong %d Cot %d", x, d, c);
//}
//
//
//void swap(int &x, int &y)
//{
//
//	int temp;
//	temp = x;
//	x = y;
//	y = temp;
//
//
//}
//
//
//void SapXepMangTangTheoDong(int a[100][100], int n,int m)
//{
//	
//	for (int i = 0; i<n; i++)
//		for (int j = 0; j<m; j++)
//			for (int k = 0; k<n; k++)
//				for (int l = 0; l<m; l++)
//					if (a[i][j]<a[k][l])
//							swap(a[i][j], a[k][l]);
//	
//}
//
//
//void SapXepGiamDanTheoCot(int a[][100], int n, int m)
//{
//
//	for (int i = 0; i < n; i++)
//		{
//			for (int j = 0; j < m / 2; j++)
//				{
//					swap(a[i][j + j], a[i][j + m - j - 1]);
//				}
//		}
//
//
//
//}
//
//
//void SapXepDuongCheo9Tang(int a[][100], int n, int m)
//{
//
//	for (int i = 0; i<n; i++)
//		for (int j = i + 1; j<n; j++)
//			if (a[i][i]>a[j][j])
//				{
//					swap(a[i][i], a[j][j]);
//				}
//
//}
//
//
//
//void SapXepDuongCheo9Giam(int a[][100], int n, int m)
//{
//
//	for (int i = 0; i<n; i++)
//		for (int j = i + 1; j<n; j++)
//			if (a[i][i]<a[j][j])
//			{
//				swap(a[i][i], a[j][j]);
//			}
//
//}
//
//
//
//
//
//void SapXepTheoZizag(int a[][100], int n, int m)
//{
//	int dem = 1;
//	for (int i = 0; i<n; i++)
//	{
//		if (i % 2 == 0)
//			for (int j = 0; j<m; j++)
//				a[i][j] = dem++;
//		else
//			for (int j = m - 1; j >= 0; j--)
//				a[i][j] = dem++;
//	}
//}
//
//
//
//
//
//
//
//
//
//void main()
//{
//	int a[100][100];
//	int n, x,m,R,C;
//
//	
//	RandomMang2Chieu(a, n, m);
//	printf("Ma Tran vua nhap: \n");
//	XuatMang(a, n, m);
//
//	printf("Mang sau khi sap xep tang dan: \n");
//	SapXepMangTangTheoDong(a, n,m);
//	XuatMang(a, n, m);
//
//	printf("Mang sau khi sap xep giam dan theo cot: \n");
//	SapXepGiamDanTheoCot(a, n, m);
//	XuatMang(a, n, m);
//
//	printf("\nNhap so x can tim: ");
//	scanf("%d", &x);
//	LinearSearch_Mang2Chieu(a, n, m, x);
//
//	printf("Mang sau khi sap sep tang dan duong cheo chinh:\n");
//	SapXepDuongCheo9Tang(a, n, m);
//	XuatMang(a, n, m);
//
//	printf("\nMang sau khi sap sep giam dan duong cheo chinh:\n");
//	SapXepDuongCheo9Giam(a, n, m);
//	XuatMang(a, n, m);
//
//
//	printf("ma tran sau khi sap xep tang dan theo zizag: \n");
//	SapXepTheoZizag(a, n, m);
//	XuatMang(a, n, m);
//
//
//
//
//
//	getch();
//}
//
//
