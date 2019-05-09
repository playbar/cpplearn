#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* make_head(void* data)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}
Node* search(Node* node,void* data)
{
    while(node!=NULL)
    {
        if(node->data==data)
            break;
        node = node->next;
    }
    if(node==NULL)
    {
        printf("您要查找的内容在链表中不存在！\n请添加相应内容!\n");
        return NULL;
    }
    else
    {
        printf("查询得到的数据为:%d\n",node->data);
        return node;
    }
}
void deletel(Node* node, void* data)
{
    Node* tmp;
    void* d_data;
    if(!node)
    {
        printf("当前链表为空\n");
        return;
    }
    while(node!=NULL)
    {
        if(node->next!=NULL && node->next->data==data)
        {
            tmp = node->next;
            node->next = tmp->next;
            d_data = tmp->data;
            free(tmp);
            break;
        }
        node = node->next;
    }
    if(node==NULL)
    {
        printf("当前链表中没有找到数值为%d的数据块!\n",data);
        printf("更新失败！\n");
    }
    else
    {
        printf("删除数据项%d成功!\n",d_data);
    }
    
}

void modify(Node* node, void* data, void* value)
{
    if(!node)
    {
        printf("当前链表为空\n");
        return;
    }
    while(node!=NULL)
    {
        if(node->data==data)
        {
            node->data = value;
            break;
        }
        node = node->next;
    }
    if(node==NULL)
    {
        printf("当前链表中没有找到数值为%d的数据块!\n",data);
        printf("更新失败！\n");
    }
    else
    {
        printf("更新成功!\n");
    }
    
}
void insert(Node* pos, void* data, void* value)
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
            Node* temp = (Node*)malloc(sizeof(Node));
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
void print_link(Node* node)
{
    if( node != NULL )
    {
        printf("%p \n",node->data);
    }
    while(node->next != NULL)
    {
        node = node->next;
        printf("%p \n",node->data);
    }
    printf("\n");
}

void add_tail(Node* node, void* data)
{
    if(!node)
        return;
    while(node->next != NULL)
        node = node->next;
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = node->next;
    node->next = temp;
}
int is_empty(Node* node)
{
    return node->next == NULL;
}

void destory(Node* node)
{
    Node* tmp;
    while(node->next!=NULL)
    {
        tmp = node->next;
        node->next = tmp->next;
        free(tmp->data);
        tmp->data = NULL;
        free(tmp);
    }
    if( node != NULL )
    {
        free(node->data);
        free(node);
        node->data = NULL;
    }
    return;
}
