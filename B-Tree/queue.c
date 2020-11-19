#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int InitQueue(pNode *head)
{
	*head = (pNode)malloc(sizeof(Node));                //������ռ� 
	if (*head == NULL)  return -1; //����ʧ�� 

	(*head)->next = NULL;
	return 1;
}

pNode CreateNode(pnode p)
{
	pNode q;
	q = (pNode)malloc(sizeof(Node));                //������ռ�
	if (q != NULL) 
	{                                    //����ɹ� 
		q->data = p;
		q->next = NULL;
	}
	return q;
}

int Enqueue(pNode p, pnode q)
{
	if (p == NULL)
		return -1;
	while (p->next != NULL)                            //����������� 
		p = p->next;
	p->next = CreateNode(q);                          //���ɽ����q������� 
	return 1;
}

int Dequeue(pNode p, pnode *q)
{
	pNode aq;
	if (p == NULL || p->next == NULL)                      //ɾ��λ�ò����� 
		return -1;
	aq = p->next;                                     //�޸ı�ɾ���aq��ָ����
	p->next = aq->next;
	*q = aq->data;
	free(aq);                                       //�ͷŽ��aq
	return 1;
}

int IsEmpty(pNode head)
{
	if (head == NULL)                                     //���в����� 
		return 1;
	if (head->next == NULL)                               //����Ϊ�� 
		return 1;
	return 0;                                   //���зǿ� 
}

//�ݹ��ͷŶ���
void DestroyQueue(pNode *head)
{
	pNode p;
	if ((*head) != NULL)
	{
		p = (*head);
		//??
		head = (*head)->next;
		free(p);                                    //��һ�ͷ� 
		DestroyQueue(&head);
	}
}
