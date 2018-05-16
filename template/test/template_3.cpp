//
// Created by hou guoli on 2018/3/28.
//

#include <iostream>

// 计算 N 的阶乘 N!
template<int N>
class aTMP{
public:
    enum { ret = N==0 ? 1 : N * aTMP<N-1>::ret }; // Lazy Instantiation，将产生无限递归!
};

template <>
class aTMP<0>{
public:
    enum { ret = 1};
};

int main(){
    std::cout << aTMP<10>::ret << '\n';
    std::cin.get(); return 0;
}

