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
    float f1 = 0.57007032632827759 / 2;
    int t = static_cast<int>(0.57007032632827759 / 2);

    int a1 = 0xFF99FF;
    int b1 = 0xEEffaa;

    double c1 = a1 * b1;

    double d1 = c1 / 25 * 3;

    int d2 = (a1 * b1) / 25 * 3;

    printf("f1 : %f, t : %d, c1 = %lf, d1 = %lf, d2 = %d \n", f1, t, c1, d1, d2 );

    printf("begin ckeck \n");
    test1();
//    test2();
//    test3();
    printf("end ckeck \n");
}