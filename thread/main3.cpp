//
// Created by hou guoli on 2019/6/5.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

struct message
{
    int i;
    int j;
};

void *hello(void *args)
{
    message *str = (message*)args;
    printf("child, the tid=%lu, pid=%d\n",pthread_self(),syscall(SYS_gettid));
    printf("the arg.i is %d, arg.j is %d\n",str->i,str->j);
    printf("child, getpid()=%d\n",getpid());
    while(1);
}

int main1(int argc, char *argv[])
{
    struct message test;
    pthread_t thread_id;
    test.i=10;
    test.j=20;
    pthread_create(&thread_id,NULL, hello, &test);
    printf("parent, the tid=%lu, pid=%d\n",pthread_self(),syscall(SYS_gettid));
    printf("parent, getpid()=%d\n",getpid());
    pthread_join(thread_id,NULL);
    return 0;
}

void *thread_one(void *args)
{
    printf("thread_one:int %d main process, the tid=%lu,pid=%ld\n",getpid(),pthread_self(),syscall(SYS_gettid));
}

void *thread_two(void *args)
{
    printf("thread two:int %d main process, the tid=%lu,pid=%ld\n",getpid(),pthread_self(),syscall(SYS_gettid));
}

int main(int argc, char *argv[])
{
    pid_t pid;
    pthread_t tid_one,tid_two;
    if((pid=fork())==-1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        pthread_create(&tid_one,NULL, thread_one,NULL);
        pthread_join(tid_one,NULL);
    }
    else
    {
        pthread_create(&tid_two,NULL, thread_two,NULL);
        pthread_join(tid_two,NULL);
    }
    wait(NULL);
    return 0;
}