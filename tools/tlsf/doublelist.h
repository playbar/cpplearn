/*************************************************************************
	> File Name: doublelist.h
	> Author:Manfred Zhao 
	> Mail: manfredzhaoshubo@foxmail.com
	> Created Time: Tue 08 Dec 2015 03:33:33 AM PST
 ************************************************************************/

#ifndef _DOUBLELIST_H
#define _DOUBLELIST_H
typedef struct doublelist *doublelink; //定义双向链表节点指针
typedef int item;   //数据的类型
typedef struct doublelist   //链表结构体
{
    item data;
    doublelink next;
    doublelink prev;
}DOUBLELIST;
doublelink create_node(item data);  //创建一个链表的节点
int getsize(doublelink d);  //获取链表的大小
void add_tail(doublelink d,item data);  //从尾部添加链表
void print_link(doublelink d);  //打印整个链表的信息
#endif
 
