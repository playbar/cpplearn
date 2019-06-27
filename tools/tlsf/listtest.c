/*************************************************************************
	> File Name: test.c
	> Author: Manfred Zhao
	> Mail: manfredzhaoshubo@foxmail.com
	> Created Time: Sun 06 Dec 2015 01:18:09 AM PST
 ************************************************************************/
#include <stdio.h>
#include "list.h"
#include <stdlib.h>
int main()
{
    link my_list = NULL;
    link search_list = NULL;
    link destory_list = NULL;
    item data = NULL;
    int i;
    my_list = make_head(data);
    printf("已生成链表my_list\n");
    if(is_empty(my_list))
        printf("经检验my_list是个空链表\n");
    for(i=0;i<5;i++)
    {
        add_tail(my_list,i);
    }
    printf("创建一个整数链表: ");
    print_link(my_list);
    search_list = search(my_list, 6);
    add_tail(my_list,6);
    printf("执行插入后的整数链表: ");
    print_link(my_list);
    search_list = search(my_list,6);
    printf("在数据项为2的链表后插入数据项为8的数据块\n");
    insert(my_list,2,8);
    printf("插入操作后的链表:\n");
    print_link(my_list);
    modify(my_list,4,20);
    printf("更新操作后的链表:\n");
    print_link(my_list);
    delete(my_list,0);
    print_link(my_list);
    destory_list = destory(my_list);
    if(is_empty(destory_list))
        printf("删除后的链表为空链表!\n");
    return 0;
}
