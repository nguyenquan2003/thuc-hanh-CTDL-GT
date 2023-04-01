#include <stdio.h>
#include <stdlib.h>
#include "MyLinkedList.h"
#define DEFAULT_LOAD_FACTOR 0.8

struct HashTable
{
	NodePtr* bucket;
	int size; //kich thuoc bang bam (so luong bucket)
	int n; //so luong phan tu hien hanh
};

int hash(int key, int M)
{
	return key % M;
}

//khoi tao
void initHT(HashTable& ht, int capacity)
{
	ht.size = capacity;
	ht.n = 0;
	ht.bucket = new NodePtr[ht.size];
	for (int i = 0; i < ht.size; i++)
	{
		initList(ht.bucket[i]);
	}
}
//huy bang bam
void removeAllHT(HashTable& ht)
{
	for (int i = 0; i < ht.size; i++)
	{
		removeAllList(ht.bucket[i]);
	}
	
	delete[]ht.bucket;
	ht.size = 0;
	ht.n = 0;
}

Node* searchNodeHT(HashTable ht, int key)
{
	int pos = hash(key, ht.size);
	return searchList(ht.bucket[pos], key);
}
void traverseHT(HashTable ht)
{
	for (int i = 0; i < ht.size; i++)
	{
		printf("bucket[%d]: \n", i);
		traverseList(ht.bucket[i]);
	}
}
void reHashing(HashTable& ht, int capacity_new)
{
	//tao ra bang bam moi voi kich thuoc moi
	HashTable ht_new;
	initHT(ht_new, capacity_new);
	//chuyen du lieu tu ban bam cu sang bang bam moi
	for (int i = 0; i < ht.size; i++) //duyet qua cac bucket
	{
		for (Node* p = ht.bucket[i]; p != NULL; p = p->next)
		{
			//lay du lieu tu bucket cu
			int key = p->key;
			int value = p->value;

			//them du lieu vao ht moi
			int pos = hash(key, ht_new.size);
			addHead(ht_new.bucket[pos], key, value);
			ht_new.n++;
		}
	}

	//cap nhat lai bang bam
	HashTable ht_old = ht;
	ht = ht_new;
	removeAllHT(ht_old);

}
//them
void insertNodeHT(HashTable& ht, int key, int value)
{
	int pos = hash(key, ht.size);
	if (searchList(ht.bucket[pos], key) != NULL)
	{
		printf("Da ton tai khoa %d\n", key);
		return;
	}
	//them phan tu moi vao dau bucket
	addHead(ht.bucket[pos], key, value);
	ht.n++;

	//kiem tra lai chi so tai
	double loadFactor = ht.n*1.0 / ht.size;

	printf("\n-> load factor: %.2f\n", loadFactor);
	if (loadFactor > DEFAULT_LOAD_FACTOR)
	{
		//bam lai
		reHashing(ht, ht.size*2);
	}
}
void removeNodeHT(HashTable& ht, int key)
{
	int pos = hash(key, ht.size);
	if (searchList(ht.bucket[pos], key) != NULL)
	{
		removeNodeList(ht.bucket[pos], key);
		ht.n--;
	}
	else
	{
		printf("Khong ton tai khoa can xoa!\n");
	}
}
void main()
{
	HashTable ht;
	initHT(ht, 5);
	//them
	int a[] = { 3, 1, 9, 5, 2, 15, 4, 16, 25, 0, 11, 13, 19, 5 };
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n; i++)
	{
		printf("Them %d\n", a[i]);
		insertNodeHT(ht, a[i], a[i]);
		traverseHT(ht);
		system("pause");
	}
	
	int x;
	printf("Tim: ");
	scanf("%d", &x);
	Node* p = searchNodeHT(ht, x);
	if (p != NULL)
	{
		printf("Tim thay!\n");
	}
	else
	{
		printf("K Tim thay!\n");
	}


	removeAllHT(ht);
	system("pause");
}