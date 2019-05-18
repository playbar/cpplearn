//
// Created by hou guoli on 2018/8/6.
//

# include<stdio.h>
# include <stdlib.h>
# include <string.h>
typedef struct node {
    char name[20];
    struct node * next;
}ListNode;

typedef ListNode * LinkList;

LinkList InitRing(int totalNumberOfPeople, LinkList linklist)
{
    ListNode *footer, *slider;//*footer是表尾，*slider是游标
    char name[20];
    int i;

    footer = NULL;
    linklist = slider = (ListNode *)malloc(sizeof(ListNode));
    if (linklist == NULL)
    {
        printf("内存分配错误。");
        exit(1);
    }

    getchar();

    for (i = 1;i < totalNumberOfPeople;i++)
    {
        printf("第%d个人的名字\n", i);
        scanf("%s",name);
        strcpy(slider->name, name);

        footer = (ListNode *)malloc(sizeof(LinkList));

        if (footer == NULL)
        {
            printf("内存分配错误");
            exit(1);
        }

        slider->next = footer;
        slider = footer;
    }

    printf("第%d个人的名字\n", i);
    scanf("%s",name);
    strcpy(footer->name, name);
    footer->next = linklist;
    printf("\n");

    return linklist;
}

LinkList DeleteDeath(int totalNumberOfPeople, int countOffLimits, LinkList linklist)
{
    int i, j;
    ListNode *slider, *deletePeople;

    slider = linklist;

    for (i = 1;i <= totalNumberOfPeople / 2;i++)
    {
        for (j = 1;j <= countOffLimits-2;j++)
            slider = slider->next;

        deletePeople = slider->next;
        slider->next = deletePeople->next;
        slider = slider->next;
        printf("%s ", deletePeople->name);
        if (i % 5 == 0) printf("\n");
        free(deletePeople);
    }
    printf("\n");

    return linklist;
}

void OutRing(LinkList linklist)
{
    LinkList slider;
    int i = 1;

    slider = linklist;

    do {
        printf("%s ", slider->name);
        if (i % 5 == 0) printf("\n");
        i++;
        slider = slider->next;
    } while (slider != linklist);

}

int main()
{
    int totalNumberOfPeople, countOffLimits;
    LinkList linklist = NULL;

    printf("请输入总人数：\n");
    scanf("%d", &totalNumberOfPeople);
    printf("请输入报数上限：\n");
    scanf("%d", &countOffLimits);

    linklist = InitRing(totalNumberOfPeople, linklist);//建立循环单链链表函数

    printf("出局名单如下:\n");
    linklist = DeleteDeath(totalNumberOfPeople, countOffLimits, linklist);

    printf("\n");

    printf("生存者名单如下:\n");

    OutRing(linklist);

    return 0;
}

