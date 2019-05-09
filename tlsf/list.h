/*************************************************************************
	> File Name: list.h
	> Author: Manfred Zhao
	> Mail: manfredzhaoshubo@foxmail.com
	> Created Time: Sun 06 Dec 2015 12:34:54 AM PST
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H


struct Node //节点定义
{
    void* data; //数据域
    Node *next; //链域
};


#ifdef __cplusplus
extern "C"{
#endif

Node* make_head(void* data);             //生成新空链表L
int is_empty(Node* node);               //判断链表是否为空
void add_tail(Node* node, void* data);    //在链表的尾部添加
void print_link(Node* node);            //打印整个链表
Node* search(Node* node, void* data);      //查询内容为data的链表的位置
void insert(Node* pos, void* data, void* value); //插入
void modify(Node* node, void* data, void* value);   //修改
void deletel(Node* node, void* data);             //删除
void destory(Node* node);                       //摧毁整个链表


#ifdef __cplusplus
}
#endif


#endif



