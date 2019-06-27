/*************************************************************************
	> File Name: doublelist.c
	> Author:Manfred Zhao 
	> Mail: manfredzhaoshubo@foxmail.com
	> Created Time: Tue 08 Dec 2015 03:34:41 AM PST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "doublelist.h"
int link_size = 0;
doublelink create_node(item data)
{
    doublelink temp = (doublelink)malloc(sizeof(DOUBLELIST));
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}
int getsize(doublelink d)
{
    return link_size;   
}
void add_tail(doublelink d,item data)
{
    doublelink temp = (doublelink)malloc(sizeof(DOUBLELIST));
    temp->data = data;
 
    while(d->next != NULL)
        d = d->next;
 
    temp->prev = d;
    temp->next = d->next;
    d->next = temp;
    link_size++;
}
void print_link(doublelink d)
{
    int i;
    printf("双向链表为: ");
    for(i=0;i<link_size;i++)
    {
        printf("%d ",d->next->data);
        d = d->next;
    }
    printf("\n");
}
