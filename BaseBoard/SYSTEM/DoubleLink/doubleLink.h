#ifndef _DOUBLELINK_H_
#define _DOUBLELINK_H_

#include <stdio.h>
#include "stm32f10x.h"

//typedef int data_t;     /* 用户自定义数据类型        */
typedef struct  
{
	uint16_t data;
} data_t;

struct node {           /* 链表结点                  */
    data_t data;        /* 数据存储区域              */
    struct node *prev;
    struct node *next;
};

struct link {
    struct node head;   /* 存储链表头                */
    int nsize;          /* 单个链表结构的大小        */
    int num;            /* 现在链表结点数量          */
};

void link_init(struct link *l);
void link_release(struct link *l);
int link_add(struct link *l, data_t *data);
void link_del(struct link *l, struct node *n);
struct node *link_find(struct link *l, int (*cmp)(struct node *n, void *key), void *key);
void link_print(struct link *l);
void link_sort(struct link *l, int (*cmp)(void *a, void *b));

#endif
