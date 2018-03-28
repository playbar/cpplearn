//
// Created by hou guoli on 2018/3/28.
//

#include <iostream>
#include <utility>  // std::swap

// static code, 模板元编程版本
template<int i, int j>
class IntSwap {
public: static void swap(int* data);
};

template<int i, int j>
class IntBubbleSortLoop {
public: static void loop(int* data);
};
template<>
class IntBubbleSortLoop<0, 0> {
public: static void loop(int* data) { }
};

template<int n>
class IntBubbleSort {
public: static void sort(int* data);
};
template<>
class IntBubbleSort<0> {
public: static void sort(int* data) { }
};

template<int i, int j>
void IntSwap<i, j>::swap(int* data) {
    if(data[i]>data[j]) std::swap(data[i], data[j]);
}
template<int i, int j>
void IntBubbleSortLoop<i, j>::loop(int* data) {
    IntSwap<j, j+1>::swap(data);
    IntBubbleSortLoop<j<i-1?i:0, j<i-1?(j+1):0>::loop(data);
}
template<int n>
void IntBubbleSort<n>::sort(int* data) {
    IntBubbleSortLoop<n-1, 0>::loop(data);
    IntBubbleSort<n-1>::sort(data);
}

int main() {
    int data[40] = {3,4,2,1};
    IntBubbleSort<2>::sort(data);  IntBubbleSort<3>::sort(data);
    IntBubbleSort<4>::sort(data);  IntBubbleSort<5>::sort(data);
    IntBubbleSort<6>::sort(data);  IntBubbleSort<7>::sort(data);
    IntBubbleSort<8>::sort(data);  IntBubbleSort<9>::sort(data);
    IntBubbleSort<10>::sort(data); IntBubbleSort<11>::sort(data);
#if 0
    IntBubbleSort<12>::sort(data); IntBubbleSort<13>::sort(data);
    IntBubbleSort<14>::sort(data); IntBubbleSort<15>::sort(data);
    IntBubbleSort<16>::sort(data); IntBubbleSort<17>::sort(data);
    IntBubbleSort<18>::sort(data); IntBubbleSort<19>::sort(data);
    IntBubbleSort<20>::sort(data); IntBubbleSort<21>::sort(data);

    IntBubbleSort<22>::sort(data); IntBubbleSort<23>::sort(data);
    IntBubbleSort<24>::sort(data); IntBubbleSort<25>::sort(data);
    IntBubbleSort<26>::sort(data); IntBubbleSort<27>::sort(data);
    IntBubbleSort<28>::sort(data); IntBubbleSort<29>::sort(data);
    IntBubbleSort<30>::sort(data); IntBubbleSort<31>::sort(data);
#endif
    std::cin.get(); return 0;
}

