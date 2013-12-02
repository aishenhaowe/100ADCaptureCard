#ifndef _DOUBLELINK_H_
#define _DOUBLELINK_H_

#include <stdio.h>
#include "stm32f10x.h"

//typedef int data_t;     /* �û��Զ�����������        */
typedef struct  
{
	uint16_t data;
} data_t;

struct node {           /* ������                  */
    data_t data;        /* ���ݴ洢����              */
    struct node *prev;
    struct node *next;
};

struct link {
    struct node head;   /* �洢����ͷ                */
    int nsize;          /* ��������ṹ�Ĵ�С        */
    int num;            /* ��������������          */
};

void link_init(struct link *l);
void link_release(struct link *l);
int link_add(struct link *l, data_t *data);
void link_del(struct link *l, struct node *n);
struct node *link_find(struct link *l, int (*cmp)(struct node *n, void *key), void *key);
void link_print(struct link *l);
void link_sort(struct link *l, int (*cmp)(void *a, void *b));

#endif
