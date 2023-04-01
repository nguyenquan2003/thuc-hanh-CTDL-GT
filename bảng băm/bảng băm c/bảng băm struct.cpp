#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define NULLKEY -1
#define TRUE 1
#define FALSE 0
int  M =8;

int N; //biến toàn cục, chỉ số nut hiện có trên bảng băm
struct SACH
{
	char MS[5];
	char TS[50];;
	int Sotrang;
	float giaban;
};
typedef SACH Itemtype;
struct Node
{
	Itemtype key;
};
//khai bao bang băm
Node *Hashtable;

int HashFunction(char k[])
{
	int b=0,i;
	for(i=1;i<=strlen(k);i++)
		b=b+(int)k[i];
	return (b%M);
}
int IsEmpty()
{
	return (N==0? TRUE: FALSE);
}
void Initializa()
{
	Hashtable=new Node[M];
	for(int i=0;i<M;i++)
	{
		strcpy(Hashtable[i].key.MS,"");
		strcpy(Hashtable[i].key.TS,"");
		Hashtable[i].key.Sotrang=NULLKEY;
		Hashtable[i].key.giaban=NULLKEY;
	}
	N=0;
}
int IsFull()
{
	return (N==M-1? TRUE:FALSE);
}
int Search(char k[])
{
	
	for(int i=0;i<M;i++)
	{
		int b=(HashFunction(k)+i*i)%M;
		if(strcmp(Hashtable[b].key.MS,k)==0)
		{
			return b;
			break;
		}
	}
		
		return (M);
}
void resize()
{
	int i;
	int cu=M;
	M=M*2;
	Node *moi=new Node[M];
	for(i=0;i<M;i++)
	{
		strcpy(moi[i].key.MS,"");
		strcpy(moi[i].key.TS,"");
		moi[i].key.Sotrang=NULLKEY;
		moi[i].key.giaban=NULLKEY;
	}
	for(i=0;i<cu;i++)
		moi[i].key=Hashtable[i].key;
	delete Hashtable;
	Hashtable=moi;
}
void Insert(Itemtype k)
{
	/*if(IsFull())
	{
		
		printf("\n bang bam daykhong them nut co khoa %d duoc",k);
		return ;
	}*/
	if(N>=M*0.6)
		resize();
	for(int i=0;i<M;i++)
	{
		int b=(HashFunction(k.MS)+i*i)%M;
		if(strcmp(Hashtable[b].key.MS,"")==0)
		{
			Hashtable[b].key=k;
			N=N+1;
			break;
		}
	}
	
}
//xoa nut tai dia chi i tren bang bam
void Remove(char k[])
{
	int i=Search(k);
	if(i!=M)
	{
		strcpy(Hashtable[i].key.MS,"");
		strcpy(Hashtable[i].key.TS,"");
		Hashtable[i].key.Sotrang=NULLKEY;
		Hashtable[i].key.giaban=NULLKEY;
		printf("da xoa");
	}
	else
		printf("Khong co phan tu de xoa");
}
void ViewTable()
{
	for(int i=0;i<M;i++)
		if(strcmp(Hashtable[i].key.MS,"")!=0)
			printf("\n Table [%d]: %s , %s , %d , %.0f ",i,Hashtable[i].key.MS,Hashtable[i].key.TS,Hashtable[i].key.Sotrang,Hashtable[i].key.giaban);
}
void themnut()
{
	int n;
	Itemtype key;
	printf("so nut moi:");
	scanf_s("%d",&n);
		for(int i=0;i<n;i++)
		{
			printf("Ma Sach:");
			fflush(stdin);
			gets(key.MS);
			printf("Ten Sach:");
			fflush(stdin);
			gets(key.TS);
			printf("So trang:");
			scanf_s("%d",&key.Sotrang);
			printf("gia ban:");
			scanf_s("%f",&key.giaban);
			Insert(key);
		}
}

void Docfile()
{
	int n;
	Itemtype key;
	FILE* f=fopen("data.txt","r+");
	if(!f)
	{
		printf("Loi doc file");
		return;
	}
	//fscanf(f,"%d\n",&n);
	//for(int i=0;i<n;i++)
	while(!feof(f))
	{
		fscanf(f,"%[^#]# %[^#]# %d# %f\n",&key.MS,&key.TS,&key.Sotrang,&key.giaban);
		
		Insert(key);
	}
	fclose(f);
}
void Menu()
{
	printf("\n------------------------------");
	printf("\n1. Them nut moi vao bang bam.");
	printf("\n2. Them nut vao bang bam tu file.");
	printf("\n3. Tim quyen sach.");
	printf("\n4. Xoa quyen sach.");
	printf("\n5. Xuat thong tin ra man hinh.");
	printf("\n6. Xoa toan bo bang bam.");
	printf("\n---------------------------.");
}
void process()
{
	int i;
	int key,chon;
	char ms[5];
	char c;
	Initializa();
	do
	{
		Menu();
		printf("\n chon chuc nang:");
		scanf_s("%d",&chon);
		switch(chon)
		{
		case 1:
		   themnut();
		   ViewTable();
			break;
		case 2:
			Docfile();
			ViewTable();
			break;
		case 3:
			printf("nhap ma sach can tim:");
			fflush(stdin);
			gets(ms);
			i=Search(ms);
			if(i!=M)
				printf("\n Table [%d]: %s , %s , %d , %.0f ",i,Hashtable[i].key.MS,Hashtable[i].key.TS,Hashtable[i].key.Sotrang,Hashtable[i].key.giaban);
			else
				printf("khong tim thay:");
			break;
		case 4:
			printf("\n Nhap ma sach can xoa:");
           fflush(stdin);
		   gets(ms);
		   Remove(ms);
			ViewTable();
			break;
		case 5:
			ViewTable();
			break;
		case 6:
			printf("Ban co muon xoa khong? c/k");
			c=getch();
			if(c=='c'||c=='C')
				Initializa();
			break;
		}
	}while(chon!=0);
}
void main()
{
	process();
}