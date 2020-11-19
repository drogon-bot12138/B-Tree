#include "btree.h"
#include "queue.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
int Traverse(Tree root, pNode L, int newline, int sum) 
{
	int i;
	pnode p;
	pnode t = root;
	if (t != NULL) 
	{
		printf("  [ ");
		Enqueue(L, t->kids[0]);                       //���         
		for (i = 1; i <= t->keynum; i++) 
		{
			printf(" %d ", t->key[i]);
			Enqueue(L, t->kids[i]);                   //�ӽ����� 
		}
		sum += t->keynum + 1;
		printf("]");
		if (newline == 0) 
		{                             //��Ҫ����һ�� 
			printf("\n");
			newline = sum - 1;
			sum = 0;
		}
		else
			newline--;
	}

	if (!IsEmpty(L)) 
	{                         //l��Ϊ�� 
		Dequeue(L, &p);                              //���ӣ���p���� 
		Traverse(p, L, newline, sum);                 //�������ӽ�� 
	}
	return 1;
}

int PrintBTree(Tree root) 
{
	pNode L = NULL;
	pnode t = root;
	if (t == NULL) 
	{
		printf("  B��Ϊ����");
		return 1;
	}
	InitQueue(&L);                                   //��ʼ������ 
	Traverse(t, L, 0, 0);                              //���ö������ 
	DestroyQueue(&L);                                //���ٶ��� 
	return 1;
}
void Test1();

int main()
{
	Tree tree = NULL;                                  //�趨���ҽ�� 

	ElemType a[] = { 1,2,3,4,5,6,7,8,9,10,11,11,12,78,54,787,13,14,15 };
	//ElemType a[] = { 2,5,7,8,10,13,14,15,18,20,22,24,25,26,27,28,30,32,35,38,40,41,42,45,46,50,78,1,3,9,11,12 };
	int len = sizeof(a) / sizeof(a[0]);
	Build(&tree, a, len);
	PrintBTree(tree);
	Destroy(&tree);
	PrintBTree(tree);
	system("pause");
	//Test1();

	return 0;
}

void Test1() 
{
	//system("color 70");
	Tree t = NULL ;                                  //�趨���ҽ�� 
	int j, n = 15;
	ElemType k;
	ElemType a[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	printf("����һ��%d��B��:\n", 3);
	for (j = 0; j < n; j++) 
	{                               //��һ����Ԫ�� 
		Insert(&t, a[j]);
		printf("   ��%d��,����Ԫ��%d:\n ", j + 1, a[j]);
		PrintBTree(t);
	}

	printf("\n");
	printf("ɾ������:\n");                          //ɾ������ 
	k = 9;
	Delete(&t, k);
	printf("  ɾ��%d:\n ", k);
	printf("  ɾ�����B��: \n");
	PrintBTree(t);
	printf("\n");

	k = 1;
	Delete(&t, k);
	printf("  ɾ��%d:\n ", k);
	printf("  ɾ�����B��: \n");
	PrintBTree(t);
	printf("\n");

	printf("  �ݹ��ͷ�B��\n");                       
	Destroy(&t);
	PrintBTree(t);
}