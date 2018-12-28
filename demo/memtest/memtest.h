#ifndef __MEMTEST_H_
#define __MEMTEST_H_

struct Data
{
    int iA;
    int iB;
    int iC;
    int iD;
};

void* MyMemMove(void *dest, const void *src, int nBytes);
void testmemvoe();

#endif // __MEMTEST_H_
