//
// Created by hou guoli on 2020/1/9.
//
//      brew install valgrind
//      valgrind --tool=memcheck --leak-check=full ./valgrind_test


#include <cstdlib>
#include <cstring>
#include <cstdio>

// 写越界
void test1()
{
    char tmp[20];
    for( int j = 0; j < 30; j++ )
    {
        tmp[j] = 'a' + j;
    }
    char* pd = (char*)malloc( 10 );
    for( int i = 0; i < 15; i++ ){
        memcpy( pd, "a", i );
    }
//    free(pd);
}

// overlap
void test2()
{
    char x[50];
    int i;
    for( i = 0; i < 50; i++ ){
        x[i] = i + 1;
    }

    strncpy( x+20, x , 20 );
    strncpy( x + 20, x, 21 );
    strncpy( x, x + 20, 20 );
    strncpy( x, x + 20, 21 );

    x[39] = '\0';
    strcpy(x, x + 20 );

    x[39] = 39;
    x[40] = '\0';
    strcpy( x, x + 20 );

}

// 没有初始化
void test3()
{
    int a, b;
    char*p;
    char*s;

    if ( a == 100 )
    {
        printf("this is a test");
    }

    if ( p == NULL ){
        printf("abc");
    }
}


int main()
{
    printf("begin ckeck \n");
    test1();
//    test2();
//    test3();
    printf("end ckeck \n");
}