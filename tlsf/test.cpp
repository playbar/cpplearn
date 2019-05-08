#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "tlsf.h"
#include "assert.h"

int main(int argc, char** argv)
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
  return 0;
}

    
	
