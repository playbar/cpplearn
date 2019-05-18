//
// Created by hou guoli on 2019/1/8.
//

#include "vector"
#include "iostream"
#include "myalloc.h"

using namespace std;

struct TrafficBlockItem
{
    int	tileX;
    int	tileY;
    int	level;
    char etag[33];
} ;

void testBlockItem(){
    int len = sizeof(TrafficBlockItem);
    TrafficBlockItem a[2];
    a[0].level = 1;
    a[0].tileX = 1;
    a[0].tileY = 1;
    memcpy(a[0].etag, "TrafficBlockItem", sizeof(a[0].etag));

    TrafficBlockItem b = a[0];
    std::cout<<a[0].etag<<&a[0].etag<<std::endl;
    std::cout<<b.etag<<&b.etag<<std::endl;

}

void testVector()
{
    std::vector<int> idata;
    for( int i = 0; i < 10; ++i)
    {
        idata.push_back(i);
    }

    for( int j = idata.size()-1; j>= 0; --j)
    {
        std::cout<<idata[j]<<std::endl;
        idata.erase(idata.begin() + j);
    }
    std::cout<<__FUNCTION__ <<std::endl;
}

void testVector1()
{
    std::vector<int> idata;
    for( int i = 0; i < 10; ++i)
    {
        idata.push_back(i);
    }

    for( int j = 0; j < idata.size(); ++j)
    {
        std::cout<<idata[j]<<std::endl;
        idata.erase(idata.begin() + j);

    }
}

struct squareXY{
    int x;
    int y;
};

void testVector2()
{
    squareXY rexy = {6, 7};
    squareXY xy = {2, 3};

    std::vector<squareXY> s(10, xy);
    std::vector<squareXY> res(10, rexy);

    s.resize(5, rexy);
    s = res;

    return;
}

void testVector3()
{
    std::vector<int> v2;
    int nums = 20;
    for (int i = 0; i < nums; ++i){
        v2.push_back(i+1);
        std::cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << std::endl;
    }


}

void testVector4()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;
    v1.resize(200);
    v2.reserve(200);
    v3.reserve(200);
    v4.resize(200);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v2.clear();
    v2.push_back(99);
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;

}

void testVector5()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity()<<endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v2.push_back(99);
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;

    int nums = 20;
    for (int i = 0; i < nums; ++i){
        v2.push_back(i+1);
        cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    }

    cout << endl;

    v1.resize(100);
    v2.resize(100);
    v2.push_back(99);   // 添加一个元素

    v3.reserve(100);
    v4.reserve(100);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v1.resize(200);
    v2.reserve(200);
    v3.reserve(200);
    v4.resize(200);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    v4.push_back(8);

    cout << "v1_size: " << v1.size() << "\t vl_capacity: " << v1.capacity() << endl;
    cout << "v2_size: " << v2.size() << "\t v2_capacity: " << v2.capacity() << endl;
    cout << "v3_size: " << v3.size() << "\t v3_capacity: " << v3.capacity() << endl;
    cout << "v4_size: " << v4.size() << "\t v4_capacity: " << v4.capacity() << endl << endl;

    return;
}

void testVector6(int size)
{
//    float *pfdata = new float[size];

    vector<string, cpl::allocator<string>> vecf;
    vecf.reserve(size);
    for( int i = 0; i  < size; ++i )
    {
        char sz[200] = {0};
        sprintf(sz, "File:%s, %d", __FILE__,  i);
//        vecf[i] = i;
//        vecf.emplace_back(i);
        printf("Fun:%s, index = %d \n", __FUNCTION__, i);
        vecf.push_back(sz);
//        pfdata[i] = i;
    }


    cout<<"size : " << vecf.size()<< ", capacity :"<<vecf.capacity() <<endl;

//    vecf.clear();
    {
//        vector<float> vecfswap;
//        vecfswap.swap(vecf);
    }
//    vecf.resize(1);
    vecf.shrink_to_fit();
//
//    delete pfdata;
    cout<<"size : " << vecf.size()<< ", capacity :"<<vecf.capacity() <<endl;

}

void myalloctest()
{
    int arr[5] = { 0, 1, 2, 3, 4 };
    //unsigned int i;
    cpl::allocator<int> test;
    cpl::allocator<int> test1;

    vector<int, cpl::allocator<int>>iv(arr, arr + 5);
    for (int i = 0; i < iv.size(); i++){
        cout << iv[i] << ' ';
    }
    cout << endl;
}

int main()
{
    testVector6(1024);
    myalloctest();
//    testVector6(20 * 1024 * 1024);
    testVector4();
    testVector5();

//    unsigned int ia = 0xFFFFFFFF;
//    float fa = ia;
//    int flen = sizeof( float);
//    testBlockItem();
//    testVector();
//    testVector1();


    return 0;
}