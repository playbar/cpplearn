//
// Created by mac on 2019-05-19.
//

#include <iostream>
#include <vector>
#include "MemLeak.h"
using namespace std;
void   Reverse(int*pa,int count);
int main(int argc, char *argv[])
{
    int *ptr = memLeakcheck_new int[10];
    char *ptr2 = memLeakcheck_new char[9];

    memLeakcheck_delete_array(ptr2);

    for( int i=0;i<mem_stack.m_vec_mem.size();++i )
    {
        printMemStack(mem_stack.m_vec_mem[i].ptr);
    }
    return 0;
}

