/*************************************************************************
	> File Name: test.c
	> Author:Manfred Zhao 
	> Mail: manfredzhaoshubo@foxmail.com
	> Created Time: Tue 08 Dec 2015 03:34:49 AM PST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "doublelist.h"
int main()
{
    int i;
    doublelink header = create_node(0);
    int size = getsize(header);
    if(!size)
        printf("当前为空链表！\n");
    printf("执行插入操作！\n");
    for(i=0;i<5;i++)
    {
        add_tail(header,i+1);
    }
    print_link(header);
}
