#pragma once
#include "btree.h"

typedef struct LNode
{               //��������������� 
	pnode data;                     //������
	struct LNode *next;             //ָ����
}Node, *pNode;

int InitQueue(pNode *L);

pNode CreateNode(pnode p);

int Enqueue(pNode p, pnode q);

int Dequeue(pNode p, pnode q);

int IsEmpty(pNode L);

void DestroyQueue(pNode L);


