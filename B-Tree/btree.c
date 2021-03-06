#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
const int M = 5;
const int Min = 2;
//在整个树中查找key
status Search(Tree root, ElemType k)
{	
	int i = 0, found = 0;
	status result;
	pnode p = root, q = NULL;
	while (p!=NULL&&!found)
	{
		int keynum = p->keynum;
		for (i = 0; i < keynum && k >= p->key[i + 1]; i++);
		if (p->key[i] == k) found =1;

		//i = search_node(p, k);
		//if (i > 0 && i <= p->keynum && p->key[i] == k) found = 1;
		else
		{
			q = p;
			p = p->kids[i];
		}
	}
	
	if (found)
	{
		result.p = p;
		result.pos = i;
		result.flag = 1;
	}
	
	else
	{
		result.p = q;
		result.pos = i;
		result.flag = 0;
	}
	return result;
}
//新键根节点
void new_root(pnode root, pnode left, pnode right, ElemType k)
{
	root = (pnode)malloc(sizeof(node));

	root->keynum = 1;
	root->kids[0] = left;
	root->kids[1] = right;
	root->key[1] = k;

	if (left != NULL) left->parent = root;
	if (right != NULL) right->parent = root;

}
//在节点中插入key
void InsertKey(pnode p, ElemType k,int pos, pnode kids)
{
	//后移一个位置
	for (int j = p->keynum; j > pos; j--) 
	{                      
		p->key[j + 1] = p->key[j];
		p->kids[j + 1] = p->kids[j];
	}
	p->key[pos + 1] = k;

	p->kids[pos + 1] = kids;
	if (kids != NULL)
		kids->parent = p;
	p->keynum++;
}
//节点分裂
void SpilitNode(pnode p, ElemType *k, int pos, pnode *q)
{
	InsertKey(p, *k, pos, *q);

	pnode left =  p;
	pnode right;
	right = (pnode)malloc(sizeof(node));//
	int mid = (M + 1) / 2;

	//移一半给right
	right->kids[0] = left->kids[mid];
	for (int i = mid + 1; i <= M; i++) 
	{
		right->key[i - mid] = left->key[i];
		right->kids[i - mid] = left->kids[i];
	}

	//修改数量
	right->keynum = left->keynum - mid;
	left->keynum = mid - 1;


	pnode kids;// 
	for (int i = 0; i <= right->keynum; i++)
	{
		if (right->kids[i] != NULL)
		{
			kids = right->kids[i];

			kids->parent = right;
		}
	}
	//将右节点挂载到左节点的父节点名下
	right->parent = left->parent;
	//取出。回溯左节点中间的键值，用于上升，即插在父节点中
	*k = left->key[mid];
	//返回q,此时q为左节点的父节点名下的子节点
	*q = right;
}
//在整个树中进行插入
void Insert(Tree *root, ElemType k)
{
	if (*root == NULL)//空树
	{
		*root = (pnode)malloc(sizeof(node));
		(*root)->keynum = 1;
		(*root)->key[1] = k;
		for (int i = 0; i <= M; i++)
			(*root)->kids[i] = NULL;
		(*root)->parent = NULL;
		return;
	}
	
	status result;
	result = Search((*root),k);
	int found = result.flag;
	if (found) return;

	//要插入的节点指针
	pnode p = result.p;
	//位置索引
	int pos = result.pos;
	//是否找到，若找到则直接返回

	//为新的键建立的子节点 初始为NULL; 同时用来接收分裂产生的新节点
	pnode q = NULL;
	ElemType x = k;
	//if (p == NULL) new_root(root, k, NULL, NULL); //

	while (1)
	{
		//关键字个数未到达上限，直接插入
		if (p->keynum < M - 1)
		{
			InsertKey(p, x, pos, q);
			return;
		}

		 SpilitNode(p,&x,pos,&q);

		if (p->parent!=NULL) //父结点不为空
		{                      
			p = p->parent;
			//查找x的插入位置
			for ( pos = 0; pos < p->keynum && x >= p->key[pos + 1]; pos++);
			//pos = search_node(p, x);
		}
		else
		{
			*root = (pnode)malloc(sizeof(node));
			(*root)->parent = NULL;
			(*root)->keynum = 1;
			(*root)->key[1] = x;
			(*root)->kids[0] = p;
			(*root)->kids[1] = q;
			p->parent = *root;
			q->parent = *root;
			return;
		}
				
		
	}
}
//建立B树
void Build(Tree *root, ElemType *datas, int len)
{
	for (int i = 0; i < len; i++) 
		Insert(root, datas[i]);
}

//key向左移动覆盖pos位置
void MoveLeft(pnode p, int pos)
{
	for (int i = pos; i < p->keynum; i++)
	{
		p->key[i] = p->key[i + 1];
		p->kids[i] = p->kids[i + 1];
	}
	p->keynum--;
}
//key向右移动空出pos位置
void MoveRight(pnode p, int pos)
{
	for (int i = p->keynum; i>=pos ; i--)
	{
		p->key[i+1] = p->key[i];
		p->kids[i+1] = p->kids[i ];
	}
	p->keynum++;
}
//融合节点
void MergeNode(pnode p, pnode parent, pnode right, int pos)
{
	int n = p->keynum + 1;
	p->key[n] = parent->key[pos];
	p->kids[n] = right->kids[0];

	for (int j = 1; j <= right->keynum; j++) //将右兄弟剩余关键字和指针移到p中
	{
		p->key[n + j] = right->key[j];
		p->kids[n + j] = right->kids[j];
	}
	if (p->kids[0]) 
	{
		pnode kids;
		for (int j = 0; j <= right->keynum; j++)
		{
			kids = p->kids[n + j];
			kids->parent = p;
		}
	}
	MoveLeft(parent, pos);            //父结点的关键字个数减1
	p->keynum = p->keynum + right->keynum + 1; //合并后关键字的个数
	free(right);
	right = NULL;

}
//从左兄弟借key
void BorrowRight(pnode p, pnode q, int pos)
{
	//p的右兄弟
	pnode right = q->kids[pos + 1];
	//兄弟有足够多的关键字
	if (right->keynum >= (M + 1) / 2)
	{
		p->keynum++;
		p->key[p->keynum] = q->key[pos + 1];
		p->kids[p->keynum] = right->kids[0];
		pnode kids;//临时指针，用于修改关系
		if (p->kids[p->keynum] != NULL)
		{
			kids = p->kids[p->keynum];
			kids->parent = p;
		}
		q->key[pos + 1] = right->key[1];
		right->kids[0] = right->kids[1];
		MoveLeft(right, 1);
	}
	else MergeNode(p, q, right, pos + 1);
}
//从右兄弟借key
void BorrowLeft(pnode p, pnode q, int pos)
{
	//p的右兄弟
	pnode left = q->kids[pos - 1];
	//兄弟有足够多的关键字
	if (left->keynum >= (M + 1) / 2)
	{
		MoveRight(left, 1);
		p->keynum++;
		p->kids[1] = p->kids[0];
		p->key[1] = q->key[pos];
		p->kids[0] = left->kids[left->keynum];

		pnode kids;//临时指针，用于修改关系
		if (p->kids[0] != NULL)
		{
			kids = p->kids[0];
			kids->parent = p;
		}
		q->key[pos ] = left->key[left->keynum];
		left->keynum--;
		
	}
	else
	{
		//调换顺序 使其符合融合要求
		pnode right = p;
		p = left;
		MergeNode(p, q, right, pos);
	}

}
//在节点中删除Key
void DeleteKey(pnode p, int pos)
{
	for (int j = pos + 1; j <= p->keynum; j++)
	{   //前移删除key[i]和kids[i]
		p->key[j - 1] = p->key[j];
		p->kids[j - 1] = p->kids[j];
	}
	p->keynum--;
}
//在整个树中删除Key
void Delete(Tree *root, ElemType k)
{
	status result;
	result = Search((*root), k);
	int found = result.flag;
	if (!found) return;
	pnode p = result.p;
	pnode q;
	int pos = result.pos;

	if (p->kids[pos]!=NULL)
	{
		q = p->kids[pos];
		while (q->kids[0] != NULL) q = q->kids[0];

		p->key[pos] = q->key[1];
		DeleteKey(q, 1);
		p = q;//转换为叶结点的删除
	}
	else DeleteKey(p, pos);

	int mid = (M + 1) / 2;
	while (1)
	{
		if (p == (*root) || p->keynum >= mid - 1) break;
		else 
		{
			q = p->parent;
			//找到p在父节点中的位置
			for (pos = 0; pos <= q->keynum&&q->kids[pos] != p; pos++);

			if (pos == 0)	BorrowRight(p, q, pos);
			else	BorrowLeft(p, q, pos);

			p = q;
		}
	}
	//删除波及到根节点
	if ((*root)->keynum == 0)
	{
		p = (*root)->kids[0];
		free((*root));
		(*root) = p;
		if ((*root) != NULL)	(*root)->parent = NULL;
	}
	return;
}
//释放B树
void Destroy(Tree *root) 
{
	int i;
	pnode p = *root;
	if (p != NULL) 
	{                                    //B树不为空  
		for (i = 0; i <= p->keynum; i++) 
		{                  //递归释放每一个结点 
			Destroy(&(p->kids[i]));
		}
		free(p);
	}
	*root = NULL;
}