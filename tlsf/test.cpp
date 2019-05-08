#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "tlsf.h"
#include "tlsf_help.h"
#include "assert.h"

void test1()
{
    size_t alloc_size = 2642080;
    size_t size = alloc_size + tlsf_size() + tlsf_pool_overhead() + tlsf_alloc_overhead();
    void* memory = malloc(size);
    tlsf_t tlsf = tlsf_create_with_pool(memory,size);
    tlsf_walk_pool(tlsf_get_pool(tlsf),0,0);
    std::cout << "try alloc " << std::hex << alloc_size << std::endl;
    void* ptr = tlsf_malloc(tlsf,alloc_size);
    assert(ptr);
    ::free(memory);
}

#define SIZE (1024 * 1024)
void test2()
{
    void *pdata = malloc(SIZE);
    tlsf_t the_tlsf = tlsf_create_with_pool( pdata, SIZE);

    for( int i = 0; i < SIZE; ++i ) {
        char *pd = (char *) tlsf_malloc(the_tlsf, 20);
        while( pd == NULL )
        {
            void *pdata1 = malloc(SIZE);
            tlsf_add_pool(the_tlsf, pdata1, SIZE);
            pd = (char *)tlsf_malloc(the_tlsf, 20);
            printf("out of memory \n");
        }
        int size = tlsf_size();
        memcpy(pd, "test", 4);
        printf("pd = %0X, i = %d, %s, %d \n",pd, i, pd, size);
        tlsf_free(the_tlsf, pd);
    }
    tlsf_destroy(the_tlsf);
    printf("success \n");
    return;
}

int main(int argc, char** argv)
{
    test2();
    return 0;
}

    
	
