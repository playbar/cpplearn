//
// Created by hou guoli on 2018/3/28.
//

#include <iostream>

template<typename T, int N>
class Vec{
    T _v[N];
    // ... // 模板通例（primary template），具体实现
};

template<>
class Vec<float, 4>{
    float _v[4];
    // ... // 对 Vec<float, 4> 进行专门实现，如利用向量指令进行加速
};

template<int N>
class Vec<bool, N>{
    char _v[(N+sizeof(char)-1)/sizeof(char)];
    // ... // 对 Vec<bool, N> 进行专门实现，如用一个比特位表示一个bool
};


//////////

template<typename T, int i> class cp00; // 用于模板型模板参数

// 通例
template<typename T1, typename T2, int i, template<typename, int> class CP>
class TMP;

// 完全特例化
template<>
class TMP<int, float, 2, cp00>;

// 第一个参数有const修饰
template<typename T1, typename T2, int i, template<typename, int> class CP>
class TMP<const T1, T2, i, CP>;

// 第一二个参数为cp00的实例且满足一定关系，第四个参数为cp00
template<typename T, int i>
class TMP<cp00<T, i>, cp00<T, i+10>, i, cp00>;

// 编译错误!，第四个参数类型和通例类型不一致
//template<template<int i> CP>
//class TMP<int, float, 10, CP>;

////////////////


// 识别两个类型是否相同，提前进入模板元编程^_^
template<typename T1, typename T2> // 通例，返回 false
class theSameType
{
public:
    enum { ret = false };
};

template<typename T>               // 特例，两类型相同时返回 true
class theSameType<T, T>
{
public: enum { ret = true };
};

template<typename T, int i> class aTMP { };

int main(){
    typedef unsigned int uint; // typedef 定义类型别名而不是引入新类型
    typedef uint uint2;
    std::cout << theSameType<unsigned, uint2>::ret << '\n';
    std::cout << theSameType<aTMP<unsigned, 2>, aTMP<uint2, 2>>::ret << '\n';  // 感谢 C++11，连续角括号“>>”不会被当做流输入符号而编译错误
    std::cout << theSameType<aTMP<int, 2>, aTMP<int, 3>>::ret << '\n';
    std::cin.get(); return 0;
}
