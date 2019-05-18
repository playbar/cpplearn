#ifndef __MEMLEAK_H__
#define __MEMLEAK_H__

#include <stddef.h>
#include <iostream>
#include <vector>
using namespace std;
struct MemInfo {
public:
    void* ptr;
    const char* file;
    unsigned int line;
    size_t size;
};

class MemStack {
public:
    vector<MemInfo>m_vec_mem;
public:
    MemStack();
    ~MemStack();
    void Insert(void* ptr, const char* file, unsigned int line, size_t size);
    void Delete(void* ptr);
    void Print(void* ptr);
};
void* operator new(size_t size, const char* file, unsigned int line);
void* operator new[](size_t size, const char* file, unsigned int line);
extern MemStack mem_stack;
#define memLeakcheck_new new(__FILE__,__LINE__)

#define memLeakcheck_delete(x) do {	\
	mem_stack.Delete(x); \
	delete (x);	\
} while(0)
#define memLeakcheck_delete_array(x) do {	\
	mem_stack.Delete(x); \
	delete[] (x);	\
} while(0)

void printMemStack(void* ptr);
#endif

