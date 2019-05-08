/*************************************************************************
	> File Name: list.h
	> Author: Manfred Zhao
	> Mail: manfredzhaoshubo@foxmail.com
	> Created Time: Sun 06 Dec 2015 12:34:54 AM PST
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H

typedef int item;
typedef struct node *link; //定义节点指针

typedef struct node //节点定义
{
    item data; //数据域
    link next; //链域
}NODE;

link make_head(link l);             //生成新空链表L
int is_empty(link l);               //判断链表是否为空
void add_tail(link p,item data);    //在链表的尾部添加
void print_link(link p);            //打印整个链表
link search(link l,item data);      //查询内容为data的链表的位置
void insert(link pos,item data,item value); //插入
void modify(link l,item data,item value);   //修改
void deletel(link l,item data);             //删除
link destory(link l);                       //摧毁整个链表

#endif



