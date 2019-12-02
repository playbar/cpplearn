#include "jemalloc/jemalloc.h"
#include <sys/time.h>
#include <printf.h>
#include "stdlib.h"

#ifndef uint64_t
typedef unsigned long long uint64_t;
#endif


void jemalloctime(char *pmsg)
{
    struct timeval tv;
    struct tm *tmp_ptr = NULL;
    gettimeofday(&tv,NULL);
    tmp_ptr = localtime(&tv.tv_sec);

    printf("%d-%02d-%02d %02d:%02d:%02d.%.04d, %s\n",
           tmp_ptr->tm_year + 1900,
           tmp_ptr->tm_mon + 1,
           tmp_ptr->tm_mday,
           tmp_ptr->tm_hour,
           tmp_ptr->tm_min,
           tmp_ptr->tm_sec,
           tv.tv_usec,
           pmsg);
    return;
}



static inline void time_func(uint64_t nwarmup, uint64_t niter, void (*func)(void))
{
	uint64_t i;
    jemalloctime("time begin");
	for (i = 0; i < nwarmup; i++) {
		func();
	}
	for (i = 0; i < niter; i++) {
		func();
	}
    jemalloctime("time end");
}


void compare_funcs(uint64_t nwarmup, uint64_t niter, const char *name_a,
    void (*func_a), const char *name_b, void (*func_b))
{


	time_func(nwarmup, niter, func_a);
	time_func(nwarmup, niter, func_b);


}

static void malloc_free(void)
{
	/* The compiler can optimize away free(malloc(1))! */
	void *p = malloc(1);
	if (p == NULL) {
		return;
	}
	free(p);
}

static void mallocx_free(void)
{
	void *p = malloc(1);
	if (p == NULL)
	{
		return;
	}
	free(p);
}


static void malloc_dallocx(void)
{
	void *p = malloc(1);
	if (p == NULL) {
		return;
	}
	dallocx(p, 0);
}

static void malloc_sdallocx(void)
{
	void *p = malloc(1);
	if (p == NULL) {
		return;
	}
	sdallocx(p, 1, 0);
}

static void malloc_mus_free(void)
{
	void *p;

	p = malloc(1);
	if (p == NULL) {
		return;
	}
	malloc_usable_size(p);
	free(p);
}

static void malloc_sallocx_free(void)
{
	void *p;

	p = malloc(1000);
	if (p == NULL)
	{
		return;
	}
	if (sallocx(p, 0) < 1) {
	}
	free(p);
}


static void malloc_nallocx_free(void)
{
	void *p;

	p = malloc(2000);
	if (p == NULL)
	{
		return;
	}
	if (nallocx(1, 0) < 1)
	{
	}
	free(p);
}



int main(void)
{

	compare_funcs(10*1000*1000, 100*1000*1000, "sallocx",
				  malloc_sallocx_free, "nallocx", malloc_nallocx_free);

//	compare_funcs(10*1000*1000, 100*1000*1000, "malloc_usable_size",
//				  malloc_mus_free, "sallocx", malloc_sallocx_free);
//
//	compare_funcs(10*1000*1000, 100*1000*1000, "dallocx", malloc_dallocx,
//				  "sdallocx", malloc_sdallocx);
//
//	compare_funcs(10*1000*1000, 100*1000*1000, "free", malloc_free,
//				  "dallocx", malloc_dallocx);
//
//	compare_funcs(10*1000*1000, 100*1000*1000, "malloc",
//				  malloc_free, "mallocx", mallocx_free);


}
