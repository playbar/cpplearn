//
// Created by hou guoli on 2018/3/28.
//


/////////
// 整合成一个类模板实现，看着好，但引入了 代码膨胀
#include <iostream>
#include <utility>  // std::swap

// 整合成一个类模板实现，看着好，但引入了 代码膨胀
template<int n>
class IntBubbleSortC {
    template<int i, int j> static void IntSwap(int* data);
    template<int i, int j> static void IntBubbleSortLoop(int* data);
    template<> static void IntBubbleSortLoop<0, 0>(int*){};
public:
    static void sort(int* data);
};
template<>
class IntBubbleSortC<0> {
public:
    static void sort(int* data) { }
};

template<int n> template<int i, int j>
void IntBubbleSortC<n>::IntSwap(int* data) {
    if(data[i]>data[j]) std::swap(data[i], data[j]);
}
template<int n> template<int i, int j>
void IntBubbleSortC<n>::IntBubbleSortLoop(int* data) {
    IntSwap<j, j+1>(data);
    IntBubbleSortLoop<j<i-1?i:0, j<i-1?(j+1):0>(data);
}

//template<int n> template <>
//void IntBubbleSortC<n>::IntBubbleSortLoop<0, 0>(int*) { }

template<int n>
void IntBubbleSortC<n>::sort(int* data) {
    IntBubbleSortLoop<n-1, 0>(data);
    IntBubbleSortC<n-1>::sort(data);
}

int main() {
    int data[40] = {3,4,2,1};
    IntBubbleSortC<2>::sort(data);  IntBubbleSortC<3>::sort(data);
    IntBubbleSortC<4>::sort(data);  IntBubbleSortC<5>::sort(data);
    IntBubbleSortC<6>::sort(data);  IntBubbleSortC<7>::sort(data);
    IntBubbleSortC<8>::sort(data);  IntBubbleSortC<9>::sort(data);
    IntBubbleSortC<10>::sort(data); IntBubbleSortC<11>::sort(data);
#if 0
    IntBubbleSortC<12>::sort(data); IntBubbleSortC<13>::sort(data);
    IntBubbleSortC<14>::sort(data); IntBubbleSortC<15>::sort(data);
    IntBubbleSortC<16>::sort(data); IntBubbleSortC<17>::sort(data);
    IntBubbleSortC<18>::sort(data); IntBubbleSortC<19>::sort(data);
    IntBubbleSortC<20>::sort(data); IntBubbleSortC<21>::sort(data);

    IntBubbleSortC<22>::sort(data); IntBubbleSortC<23>::sort(data);
    IntBubbleSortC<24>::sort(data); IntBubbleSortC<25>::sort(data);
    IntBubbleSortC<26>::sort(data); IntBubbleSortC<27>::sort(data);
    IntBubbleSortC<28>::sort(data); IntBubbleSortC<29>::sort(data);
    IntBubbleSortC<30>::sort(data); IntBubbleSortC<31>::sort(data);
#endif
    std::cin.get(); return 0;
}