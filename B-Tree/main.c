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
		Enqueue(L, t->kids[0]);                       //入队         
		for (i = 1; i <= t->keynum; i++) 
		{
			printf(" %d ", t->key[i]);
			Enqueue(L, t->kids[i]);                   //子结点入队 
		}
		sum += t->keynum + 1;
		printf("]");
		if (newline == 0) 
		{                             //需要另起一行 
			printf("\n");
			newline = sum - 1;
			sum = 0;
		}
		else
			newline--;
	}

	if (!IsEmpty(L)) 
	{                         //l不为空 
		Dequeue(L, &p);                              //出队，以p返回 
		Traverse(p, L, newline, sum);                 //遍历出队结点 
	}
	return 1;
}

int PrintBTree(Tree root) 
{
	pNode L = NULL;
	pnode t = root;
	if (t == NULL) 
	{
		printf("  B树为空树");
		return 1;
	}
	InitQueue(&L);                                   //初始化队列 
	Traverse(t, L, 0, 0);                              //利用队列输出 
	DestroyQueue(&L);                                //销毁队列 
	return 1;
}
void Test1();

int main()
{
	Tree tree = NULL;                                  //设定查找结果 

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
	Tree t = NULL ;                                  //设定查找结果 
	int j, n = 15;
	ElemType k;
	ElemType a[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	printf("创建一棵%d阶B树:\n", 3);
	for (j = 0; j < n; j++) 
	{                               //逐一插入元素 
		Insert(&t, a[j]);
		printf("   第%d步,插入元素%d:\n ", j + 1, a[j]);
		PrintBTree(t);
	}

	printf("\n");
	printf("删除操作:\n");                          //删除操作 
	k = 9;
	Delete(&t, k);
	printf("  删除%d:\n ", k);
	printf("  删除后的B树: \n");
	PrintBTree(t);
	printf("\n");

	k = 1;
	Delete(&t, k);
	printf("  删除%d:\n ", k);
	printf("  删除后的B树: \n");
	PrintBTree(t);
	printf("\n");

	printf("  递归释放B树\n");                       
	Destroy(&t);
	PrintBTree(t);
}