//
// Created by hou guoli on 2018/3/28.
//

#include <utility>  // std::swap
#include <iostream>
#include <string.h> // memcpy

// dynamic code, 普通函数版本
void bubbleSort(int* data, int n)
{
    for(int i=n-1; i>0; --i) {
        for(int j=0; j<i; ++j)
            if (data[j]>data[j+1]) std::swap(data[j], data[j+1]);
    }
}
// 数据长度为 4 时，手动循环展开
inline void bubbleSort4(int* data)
{
#define COMP_SWAP(i, j) if(data[i]>data[j]) std::swap(data[i], data[j])
    COMP_SWAP(0, 1);
    COMP_SWAP(1, 2);
    COMP_SWAP(2, 3);
    COMP_SWAP(0, 1);
    COMP_SWAP(1, 2);
    COMP_SWAP(0, 1);
}

// 递归函数版本，指导模板思路，最后一个参数是哑参数（dummy parameter），仅为分辨重载函数
class recursion { };
void bubbleSort(int* data, int n, recursion)
{
    if(n<=1)
        return;
    for(int j=0; j<n-1; ++j)
    {
        if(data[j]>data[j+1])
            std::swap(data[j], data[j+1]);
    }
    bubbleSort(data, n-1, recursion());
}

// static code, 模板元编程版本
template<int i, int j>
inline void IntSwap(int* data) { // 比较和交换两个相邻元素
    if(data[i]>data[j])
        std::swap(data[i], data[j]);
}

template<int i, int j>
inline void IntBubbleSortLoop(int* data) { // 一次冒泡，将前 i 个元素中最大的置换到最后
    IntSwap<j, j+1>(data);
    IntBubbleSortLoop<j<i-1?i:0, j<i-1?(j+1):0>(data);
}
template<>
inline void IntBubbleSortLoop<0, 0>(int*) { }

template<int n>
inline void IntBubbleSort(int* data) { // 模板冒泡排序循环展开
    IntBubbleSortLoop<n-1, 0>(data);
    IntBubbleSort<n-1>(data);
}
template<>
inline void IntBubbleSort<1>(int* data) { }


int main_1() {
    double t1, t2, t3; const int num=100;
    int data[4]; int inidata[4]={3,4,2,1};
    for(int i=0; i<num; ++i)
    {
        memcpy(data, inidata, 4);
        bubbleSort(data, 4);
    }
    for(int i=0; i<num; ++i)
    {
        memcpy(data, inidata, 4);
        bubbleSort4(data);
    }
    for(int i=0; i<num; ++i)
    {
        memcpy(data, inidata, 4);
        IntBubbleSort<4>(data);
    }
    std::cout << t1/t3 << '\t' << t2/t3 << '\n';
    return 0;
}

