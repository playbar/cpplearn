
#include "vector"
//#include "string"
//#include "myalloc.h"
//#include "iostream"

void testVector6(int size)
{
//    float *pfdata = new float[size];

    sgi::vector<int> vecf;
    vecf.reserve(size);
    for( int i = 0; i  < size; ++i )
    {
        char sz[200] = {0};
        sprintf(sz, "File:%s, %d", __FILE__,  i);
//        vecf[i] = i;
//        vecf.emplace_back(i);
        printf("Fun:%s, index = %d \n", __FUNCTION__, i);
        vecf.push_back(i);
//        pfdata[i] = i;
    }

    printf("size : %d, capacity = %d", vecf.size(), vecf.capacity() );

//    vecf.clear();
    {
//        vector<float> vecfswap;
//        vecfswap.swap(vecf);
    }
//    vecf.resize(1);
//    vecf.shrink_to_fit();
//
//    delete pfdata;
    printf("size : %d, capacity = %d", vecf.size(), vecf.capacity() );
}

int main()
{
    const int len = 10080934;
    char *pdata = new char[len + 1];
    memset(pdata, 0, len + 1);
    pdata[len] = '\o';

//    testVector6(1 * 1024 * 1024);
    sgi::vector<int> v1;
    for(int j = 0; j < 10; ++j)
    {
        v1.push_back(j);
    }
    for( int i = 0; i < v1.size(); ++i )
    {
        printf("%d \n", v1[i]);
    }

    return 0;
}


