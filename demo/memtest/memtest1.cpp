//
// Created by hou guoli on 2018/7/10.
//

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>

#include <thread>

#define BUF_LEN 1024

using namespace std;

int buf[BUF_LEN] = {0};
int* p = &buf[512];

void func2() {
    char* q = reinterpret_cast<char*>(p);
    *q = 0xFF;
}

void func1() {
    long pageSize = sysconf(_SC_PAGESIZE);
    void *pageStart = (void*)((long)p - (long)p % pageSize);

    int rst = mprotect(pageStart, pageSize, PROT_READ);
    if ( rst == -1 )
        printf("mprotect failed: %s", strerror(errno));
    sleep(10);
}

int main() {
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

    return 0;
}