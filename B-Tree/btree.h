#pragma once
#include <stdio.h>
#define MAXM  5
typedef int ElemType;

typedef struct TNode
{
	int keynum;
	ElemType key[MAXM+1];
	struct TNode *parent;
	struct TNode *kids[MAXM+1]; 
}node,*pnode, *Tree;
//
//typedef struct 
//{
//	struct TNode* tnode;
//	struct List *next;
//}list, *plist;

typedef struct 
{
	struct TNode* p;
	int flag;
	int pos;
}status;

status Search(Tree root, ElemType k);

void new_root(pnode root, pnode left, pnode right, ElemType k);

void InsertKey(pnode p, ElemType k, int pos, pnode kids);

void SpilitNode(pnode p, ElemType *k, int pos, pnode *q);

void Insert(Tree *root, ElemType k);

void Build(Tree *root, ElemType *datas, int len);

void MoveLeft(pnode p, int pos);

void MoveRight(pnode p, int pos);

void MergeNode(pnode p, pnode parent, pnode right, int pos);

void BorrowRight(pnode p, pnode q, int pos);

void BorrowLeft(pnode p, pnode q, int pos);

void DeleteKey(pnode p, int pos);

void Delete(Tree *root, ElemType k);

void Destroy(Tree *root);