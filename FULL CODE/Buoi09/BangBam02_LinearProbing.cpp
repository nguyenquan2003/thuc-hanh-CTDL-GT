#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_LOAD_FACTOR 0.8
#define NULLKEY -1
#define DELKEY -2

struct Node
{
	int key;
	int value;
};

struct HashTable
{
	Node* arr;
	int size;//kich thuoc bang bam
	int n; //so luong phan tu hien hanh cua bang bam
};
int hash(int key, int M)
{
	return key%M;
}
void initHT(HashTable& ht, int capacity)
{
	ht.size = capacity;
	ht.n = 0;
	ht.arr = new Node[ht.size];
	for (int i = 0; i < ht.size; i++)
	{
		ht.arr[i].key = NULLKEY;
		//ht.arr[i].value = 0;
	}
}
void removeAllHT(HashTable& ht)
{
	ht.size = 0;
	ht.n = 0;
	delete[] ht.arr;
}

void insertNodeHT(HashTable& ht, int key, int value);
void rehashing(HashTable& ht, int capacity_new)
{
	//tao bang bam moi voi kich thuoc moi
	HashTable ht_new;
	initHT(ht_new, capacity_new);
	//chuyen tat ca du lieu tu bang bam cu sang moi
	for (int i = 0; i < ht.size; i++)
	{
		if (ht.arr[i].key != NULLKEY && ht.arr[i].key != DELKEY)
		{
			//lay du lieu tu bang bam cu
			int key = ht.arr[i].key;
			int value = ht.arr[i].value;
			//dua vao bang bam moi
			insertNodeHT(ht_new, key, value);
		}
	}
	//cap nhat lai bang bam
	HashTable ht_old = ht;
	ht = ht_new;
	removeAllHT(ht_old);
}
void insertNodeHT(HashTable& ht, int key, int value)
{
	int pos, h = hash(key, ht.size);
	for (int i = 0; i < ht.size; i++)
	{
		pos = (h + i) % ht.size; //lan thu thu i

		if (ht.arr[pos].key == key)
		{
			printf("Khoa %d bi trung\n",key);
			return;
		}

		if (ht.arr[pos].key == NULLKEY || ht.arr[pos].key == DELKEY)
		{
			ht.arr[pos] = { key, value };
			ht.n++;
			break;
		}
	}

	//======THAO TAC MO RONG ====
	//tinh chi so tai
	double loadFactor = ht.n* 1.0 / ht.size;
	if (loadFactor > DEFAULT_LOAD_FACTOR)
	{
		//bam lai
		rehashing(ht, ht.size * 2);
	}
}

int search(HashTable& ht, int key)
{
	int pos, h = hash(key, ht.size);
	for (int i = 0; i < ht.size; i++)
	{
		pos = (h + i)%ht.size;
		if (ht.arr[pos].key == NULLKEY) 
			return NULLKEY;

		//tim thay
		if (ht.arr[pos].key == key)
			return pos;
	}
	return NULLKEY;
}

void removeNodeHT(HashTable& ht, int key)
{
	int pos = search(ht, key);
	if (pos == NULLKEY)
	{
		printf("Khong ton tai khoa can xoa");
		return;
	}
	else
	{
		//thuc hien qua trinh xoa
		ht.arr[pos].key = DELKEY;
		ht.n--;
	}

}

void traverseHT(HashTable ht)
{
	printf("Duyet:\n");
	for (int i = 0; i < ht.size; i++)
	{
		if (ht.arr[i].key != NULLKEY && ht.arr[i].key != DELKEY)
		{
			printf("[%d]: <%d,%d> \n", i, ht.arr[i].key, ht.arr[i].value);
		}
	}
}

void menu()
{
	printf("\n 0.Thoat");
	printf("\t 1.Them");
	printf("\t 2.Xoa");
	printf("\t 3.Tim");
}

void loadFile(HashTable& ht, char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if (fp != NULL)
	{
		int x;
		while (fscanf(fp, "%d", &x) == 1)
		{
			insertNodeHT(ht, x, x);
		}
		fclose(fp);
	}
}

void main()
{
	//int a[] = { 7, 3, 6, 15, 2, 5, 1, 9, 3, 12, 25 };
	//int n = sizeof(a) / sizeof(a[0]);
	
	HashTable ht;
	initHT(ht, 5);
	//for (int i = 0; i < n; i++)
	//{
	//	printf("Them %d\n", a[i]);
	//	insertNodeHT(ht, a[i], a[i]);

	//	//traverseHT(ht);
	//	//system("pause");
	//}
	
	loadFile(ht, "input.txt");

	int chon = 0;
	do
	{
		traverseHT(ht);
		menu();
		printf("\nChon:");
		scanf("%d", &chon);
		switch (chon)
		{
		case 1:
		{
				  int x;
				  printf("Them: ");
				  scanf("%d", &x);
				  insertNodeHT(ht, x, x);
				  break;
		}
		case 2:
		{
				  int x;
				  printf("Xoa: ");
				  scanf("%d", &x);
				  removeNodeHT(ht, x);
				  break;
		}
		case 3:
		{
				  int x;
				  printf("Tim: ");
				  scanf("%d", &x);
				  int pos = search(ht, x);
				  if (pos != NULLKEY)
				  {
					  printf("Tim Thay tai vi tri %d\n",pos);
				  }
				  else
				  {
					  printf("Ko tim thay!\n");
				  }
				  break;
		}
		default:
			break;
		}

	} while (chon != 0);



	

	system("pause");
}