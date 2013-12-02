#include <stdio.h>
#include <stdlib.h>
#include "doubleLink.h"

/* 结构初始化                */
void link_init(struct link *l)
{
    l->nsize = sizeof(struct node);
    l->num = 0;
    l->head.prev = &l->head;
    l->head.next = &l->head;
}

/* 结构置空及链表空间释放    */
void link_release(struct link *l)
{
    struct node *cur, *save;

    for (cur = l->head.next; cur != &l->head; cur = save) {
        save = cur->next;
        free(cur);
    }
    l->head.next = NULL;
    l->head.prev = NULL;
}

/* 增加结点                    */
int link_add(struct link *l, data_t *data)
{
    struct node *newNode;
    if ((newNode = (struct node *)malloc(l->nsize)) == NULL)
        return -1;
    newNode->data = *data;
    newNode->prev = &l->head;
    newNode->next = l->head.next;
    l->head.next->prev = newNode;
    l->head.next = newNode;
    l->num++;

    return 0;
}

/* 移除给定结点                */
void link_del(struct link *l, struct node *n)
{
    n->prev->next = n->next;
    n->next->prev = n->prev;
    l->num--;
    free(n);
}

/* 根据给定条件查找结点        */
struct node *link_find(struct link *l, int (*cmp)(struct node *n, void *key), void *key)
{
    struct node *cur;

    for (cur = l->head.next; cur != &l->head; cur = cur->next)
        if (cmp(cur, key) == 0)
            return cur;
    return NULL;
}

/* 遍历打印链表数据                */
//void link_print(struct link *l)
//{
//    struct node *cur;
//
//    for (cur = l->head.next; cur != &l->head; cur = cur->next)
//        printf("%d ", cur->data);
//    putchar('\n');
//}

/* 交换指定的两个节点的位置			*/
static void swap(struct node *a, struct node *b)
{
    data_t tmp;

    tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}

/* 冒泡法对链表数据排序        */
void link_sort(struct link *l, int (*cmp)(void *a, void *b))
{
    int i, j;
    struct node *cur, *next;
    char flag;

    for (i = 0; i < l->num; i++) {
        cur = l->head.next;
        next = NULL;
        flag = 1;
        for (j = 0; j < l->num - i - 1; j++) {
            next = cur->next;
            if (cmp(&cur->data, &next->data) == 1) {
                swap(cur, next);
                flag = 0;
            }
            cur = next;
        }
        if (flag == 1)
            break;
    }
}
