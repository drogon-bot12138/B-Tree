#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int InitQueue(pNode *head)
{
	*head = (pNode)malloc(sizeof(Node));                //分配结点空间 
	if (*head == NULL)  return -1; //分配失败 

	(*head)->next = NULL;
	return 1;
}

pNode CreateNode(pnode p)
{
	pNode q;
	q = (pNode)malloc(sizeof(Node));                //分配结点空间
	if (q != NULL) 
	{                                    //分配成功 
		q->data = p;
		q->next = NULL;
	}
	return q;
}

int Enqueue(pNode p, pnode q)
{
	if (p == NULL)
		return -1;
	while (p->next != NULL)                            //调至队列最后 
		p = p->next;
	p->next = CreateNode(q);                          //生成结点让q进入队列 
	return 1;
}

int Dequeue(pNode p, pnode *q)
{
	pNode aq;
	if (p == NULL || p->next == NULL)                      //删除位置不合理 
		return -1;
	aq = p->next;                                     //修改被删结点aq的指针域
	p->next = aq->next;
	*q = aq->data;
	free(aq);                                       //释放结点aq
	return 1;
}

int IsEmpty(pNode head)
{
	if (head == NULL)                                     //队列不存在 
		return 1;
	if (head->next == NULL)                               //队列为空 
		return 1;
	return 0;                                   //队列非空 
}

//递归释放队列
void DestroyQueue(pNode *head)
{
	pNode p;
	if ((*head) != NULL)
	{
		p = (*head);
		//??
		head = (*head)->next;
		free(p);                                    //逐一释放 
		DestroyQueue(&head);
	}
}
