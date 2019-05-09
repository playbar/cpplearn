#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "tlsf.h"
#include "tlsf_help.h"
#include "assert.h"
#include "list.h"

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

#define SIZE (1024 * 10)
#define MAL_SIZE (24)
void test2()
{

    void *pdata = malloc(SIZE);
    Node *pNode = make_head(pdata);

    tlsf_t the_tlsf = tlsf_create_with_pool( pdata, SIZE);
    printf("pdata = %p, tlsf = %p \n", pdata, the_tlsf);

    for( int i = 0; i < SIZE; ++i ) {
        char *pd = (char *) tlsf_malloc(the_tlsf, MAL_SIZE);
        while( pd == NULL )
        {
            void *pdata1 = malloc(SIZE);
            add_tail(pNode, pdata1);

            tlsf_add_pool(the_tlsf, pdata1, SIZE);
            pd = (char *)tlsf_malloc(the_tlsf, MAL_SIZE);
            printf("out of memory \n");
        }
        memset(pd, 0, MAL_SIZE);
        int size = tlsf_size();
        memcpy(pd, "test", 4);
        printf("pd = %p, i = %d, %s, %d \n",pd, i, pd, size);
//        tlsf_free(the_tlsf, pd);
    }
    tlsf_destroy(the_tlsf);
    print_link(pNode);
    destory(pNode);
    printf("success \n");
    return;
}

int main(int argc, char** argv)
{
    test2();
    return 0;
}

    
	
