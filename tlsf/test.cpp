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

#define SIZE (6636)
void test2()
{
    void *pdata = malloc(SIZE);
    tlsf_t the_tlsf = tlsf_create_with_pool( pdata, SIZE);
    char *pd  = (char*)tlsf_malloc( the_tlsf, 20);
    int size = tlsf_size();
    memcpy(pd, "test", 4);
    printf("%s, %d \n", pd, size);
    tlsf_free( the_tlsf, pd);

    return;
}

int main(int argc, char** argv)
{
    test2();
    return 0;
}

    
	
