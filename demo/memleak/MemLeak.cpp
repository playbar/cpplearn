//
// Created by mac on 2019-05-19.
//

#include "MemLeak.h"
#include<iostream>
#include <stdarg.h>
#include <string.h>
using namespace std;

MemStack mem_stack;
char memMsg[1000];

void* operator new(size_t size, const char* file, unsigned int line) {
    void* ptr = malloc(size);
    mem_stack.Insert(ptr, file, line, size);
    return ptr;
}

void* operator new[](size_t size, const char* file, unsigned int line) {
    return operator new(size, file, line);
}

void printMemStack(void* ptr)
{
    mem_stack.Print(ptr);
}

MemStack::MemStack() {
    m_vec_mem.clear();
}

MemStack::~MemStack() {
    vector<MemInfo>().swap(m_vec_mem);
}

void MemStack::Insert(void* ptr, const char* file, unsigned int line, size_t size) {
    MemInfo node;
    node.ptr = ptr;
    node.file = file;
    node.line=line;
    node.size = size;
    m_vec_mem.push_back(node);
}

void MemStack::Delete(void* ptr) {
    if(ptr == NULL)
        return;
    vector<MemInfo>::iterator itor = m_vec_mem.begin();
    while(itor!=m_vec_mem.end())
    {
        if((*itor).ptr == ptr)
        {
            itor = m_vec_mem.erase(itor);
        }else{
            ++itor;
        }
    }
}

void debugString(string log)
{
    cout<<log<<endl;
}

void MemStack::Print(void* ptr) {
    if (ptr == NULL)
    {
        return;
    }
    MemInfo *node_tep = NULL;
    vector<MemInfo>::iterator itor = m_vec_mem.begin();
    while(itor!=m_vec_mem.end())
    {
        if((*itor).ptr == ptr)
        {
            node_tep = &(*itor);
        }
        ++itor;
    }
    if ( node_tep == NULL ){
        debugString("not exist");
        return;
    }
    size_t size = (long) ((void*)(node_tep->size));
    const char* f_name = node_tep->file;
    unsigned int f_line = node_tep->line;
    sprintf(memMsg, "memleakcheck_debug record file: %s line: %d, size_t: %d ", f_name, f_line, size);
    debugString(memMsg);

    sprintf(memMsg, "memleakcheck_debug record memSize = %d\0", m_vec_mem.size());
    debugString(memMsg);
}

