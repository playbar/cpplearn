/*************************************************************************
	> File Name: list.c
	> Author: Manfred Zhao
	> Mail: manfredzhaoshubo@foxmail.com
	> Created Time: Sun 06 Dec 2015 01:08:45 AM PST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
link make_head(link l)
{
    l = (link)malloc(sizeof(NODE));
    l->next = NULL;
    return l;
}
link search(link l,item data)
{
    while(l!=NULL)
    {
        if(l->data==data)
            break;
        l = l->next;
    }
    if(l==NULL)
    {
        printf("您要查找的内容在链表中不存在！\n请添加相应内容!\n");
        return NULL;
    }
    else
    {
        printf("查询得到的数据为:%d\n",l->data);
        return l;
    }
}
void deletel(link l,item data)
{
    link tmp;
    item d_data;
    if(!l)
    {
        printf("当前链表为空\n");
        return;
    }
    while(l!=NULL)
    {
        if(l->next!=NULL && l->next->data==data)
        {
            tmp = l->next;
            l->next = tmp->next;
            d_data = tmp->data;
            free(tmp);
            break;
        }
        l = l->next;
    }
    if(l==NULL)
    {
        printf("当前链表中没有找到数值为%d的数据块!\n",data);
        printf("更新失败！\n");
    }
    else
    {
        printf("删除数据项%d成功!\n",d_data);
    }
    
}

void modify(link l,item data,item value)
{
    if(!l)
    {
        printf("当前链表为空\n");
        return;
    }
    while(l!=NULL)
    {
        if(l->data==data)
        {
            l->data = value;
            break;
        }
        l = l->next;
    }
    if(l==NULL)
    {
        printf("当前链表中没有找到数值为%d的数据块!\n",data);
        printf("更新失败！\n");
    }
    else
    {
        printf("更新成功!\n");
    }
    
}
void insert(link pos,item data,item value)
{
    if(!pos)
    {
        printf("当前链表为空\n");
        return;
    }
    while(pos!=NULL)
    {
        if(pos->data==data)
        {
            link temp = (link)malloc(sizeof(NODE));
            temp->data = value;
            temp->next = pos->next;
            pos->next = temp;
            break;
        }
        pos = pos->next;
    }
    if(pos==NULL)
    {
        printf("当前链表中没有找到数值为%d的数据块!\n",data);
        printf("插入失败！\n");
    }
    else
    {
        printf("插入成功!\n");
    }

}
void print_link(link p)
{
    while(p->next != NULL)
    {
        p = p->next;
        printf("%d ",p->data);
    }
    printf("\n");
}

void add_tail(link p,item data)
{
    if(!p)
        return;
    while(p->next != NULL)
        p = p->next;
    link temp = (link)malloc(sizeof(NODE));
    temp->data = data;
    temp->next = p->next;
    p->next = temp;
}
int is_empty(link l)
{
    return l->next == NULL;
}

link destory(link l)
{
    link tmp;
    while(l->next!=NULL)
    {
        tmp = l->next;
        l->next = tmp->next;
        free(tmp);
    }
    return l;
}
