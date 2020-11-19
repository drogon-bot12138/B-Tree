#pragma once
#include "btree.h"

typedef struct LNode
{               //链表和链表结点类型 
	pnode data;                     //数据域
	struct LNode *next;             //指针域
}Node, *pNode;

int InitQueue(pNode *L);

pNode CreateNode(pnode p);

int Enqueue(pNode p, pnode q);

int Dequeue(pNode p, pnode q);

int IsEmpty(pNode L);

void DestroyQueue(pNode L);


