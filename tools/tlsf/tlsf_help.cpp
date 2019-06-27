#include <cstdlib>
#include <cstdio>
#include "tlsf_help.h"



tlsf_t the_tlsf;

void vPortInitMemory(void)
{
    void *pdata = malloc(1024);
    the_tlsf = tlsf_create_with_pool( pdata, 1024);
}

void * pvPortMalloc(size_t xWantedSize)
{
    void * res = tlsf_malloc( the_tlsf, xWantedSize);
    return res;
}

void vPortFree(void *pv)
{
    tlsf_free( the_tlsf, pv);
}

void * pvPortRealloc(void *pv, size_t xWantedSize)
{
    void * res = tlsf_realloc(the_tlsf, pv, xWantedSize);
    return res;
}


LinkList *creat(int n){
    LinkList *head, *node, *end;//定义头节点，普通节点，尾部节点；
    head = (LinkList*)malloc(sizeof(LinkList));//分配地址
    end = head;         //若是空链表则头尾节点一样
    for (int i = 0; i < n; i++) {
        node = (LinkList*)malloc(sizeof(LinkList));
        scanf("%d", &node->score);
        end->next = node;
        end = node;
    }
    end->next = NULL;//结束创建
    return head;
}

void change(LinkList *list,int n) {//n为第n个节点
    LinkList *t = list;
    int i = 0;
    while (i < n && t != NULL) {
        t = t->next;
        i++;
    }
    if (t != NULL) {
        puts("输入要修改的值");
        scanf("%d", &t->score);
    }
    else {
        puts("节点不存在");
    }
}

void delet(LinkList *list, int n) {
    LinkList *t = list, *in;
    int i = 0;
    while (i < n && t != NULL) {
        in = t;
        t = t->next;
        i++;
    }
    if (t != NULL) {
        in->next = t->next;
        free(t);
    }
    else {
        puts("节点不存在");
    }
}


void insert(LinkList *list, int n) {
    LinkList *t = list, *in;
    int i = 0;
    while (i < n && t != NULL) {
        t = t->next;
        i++;
    }
    if (t != NULL) {
        in = (LinkList*)malloc(sizeof(LinkList));
        puts("输入要插入的值");
        scanf("%d", &in->score);
        in->next = t->next;//填充in节点的指针域，也就是说把in的指针域指向t的下一个节点
        t->next = in;//填充t节点的指针域，把t的指针域重新指向in
    }
    else {
        puts("节点不存在");
    }
}

