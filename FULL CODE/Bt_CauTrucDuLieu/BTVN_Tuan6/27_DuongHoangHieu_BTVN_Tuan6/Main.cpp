#include <conio.h>
#include <stdio.h>
#include<stdlib.h>
#include "DSLK_SinhVien.h"

void main()
{
	int n;
	SListSV sl;
	CreateSListSV_DOCFILE(sl,n);
	XuatSlistSV(sl);
	
	/*int n;
	SListMH sl;
	CreateSListMH_DOCFILE(sl, n);
	XuatSlist(sl);*/
	

	getch();

}