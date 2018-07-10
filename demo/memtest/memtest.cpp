#include "demo/CppBase/move.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <string>

void* MyMemMove(void *dest, const void *src, int nBytes)
{
	void *ret = dest;           //用于返回

	const char *from = static_cast<const char*>(src);
	char *to   = static_cast<char*>(dest);

	if( dest < src ){                   //dest在src的左边
		while( nBytes-- )        //从左往右复制
			*to++ = *from++;
	}else if( dest > src ){                  //dest在src的右边
		from += nBytes - 1;      //从右往左复制
		to   += nBytes - 1;
		while( nBytes-- )
			*to-- = *from--;
	}
	return ret;
}


void testmemvoe()
{
    int arr1[20];
    memset( arr1, 0, sizeof(int) * 20);
    for( int i = 0; i < 10; ++i ){
        arr1[i] = i+1;
    }
    printf("%d\n", arr1[5]);
    printf("%d\n", arr1[4]);
    memmove(arr1 + 2, arr1 + 3, 6 * sizeof(int));
    arr1[4] = 20;
    memmove(arr1 + 3, arr1 + 2, 6 * sizeof(int));
    for( int j = 0; j < 10; ++j)
    {
        printf("%d\n", arr1[j]);
    }
	return;
}

int main()
{
	testmemvoe();
	int *pInt =  (int*)malloc(sizeof(int));
	free(pInt);
	free(pInt);

	return 0;
}