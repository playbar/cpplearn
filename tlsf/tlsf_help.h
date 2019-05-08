#ifndef __TLSF_HELP_H__
#define __TLSF_HELP_H__


#include "tlsf.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef struct student{
    int score;
    struct student *next;
} LinkList;


void vPortInitMemory(void);

void * pvPortMalloc(size_t xWantedSize);

void vPortFree(void *pv);

void * pvPortRealloc(void *pv, size_t xWantedSize);

#ifdef __cplusplus
}
#endif


#endif

