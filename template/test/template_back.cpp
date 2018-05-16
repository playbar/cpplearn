//
// Created by hou guoli on 2018/3/28.
//

#include <iostream>

// 函数模板
template<typename T>
bool equivalent(const T& a, const T& b){
    return !(a < b) && !(b < a);
}
// 类模板
template<typename T=int> // 默认参数
class bignumber{
    T _v;
public:
    bignumber(T a) : _v(a) { }
    inline bool operator<(const bignumber& b) const; // 等价于 (const bignumber<T>& b)
};
// 在类模板外实现成员函数
template<typename T>
bool bignumber<T>::operator<(const bignumber& b) const{
    return _v < b._v;
}

int main_1()
{
    bignumber<> a(1), b(1); // 使用默认参数，"<>"不能省略
    std::cout << equivalent(a, b) << '\n'; // 函数模板参数自动推导
    std::cout << equivalent<double>(1, 2) << '\n';
    return 0;
}

/////

// 实现一个向量类
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


///////////
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


// 识别两个类型是否相同，提前进入模板元编程^_^
template<typename T1, typename T2> // 通例，返回 false
class theSameType {
public:
    enum { ret = false };
};

template<typename T>               // 特例，两类型相同时返回 true
class theSameType<T, T> {
public:
    enum { ret = true };
};

template<typename T, int i>
class aTMP{

};


// 计算 N 的阶乘 N!
template<int N>
class aTMPN{
public:
    enum { ret = N==0 ? 1 : N * aTMPN<N-1>::ret }; // Lazy Instantiation，将产生无限递归!
};

template<>
class aTMPN<0>{
public:
    enum { ret = 1 };
};

template<typename T>
class aTMP1 {
public:
    void f1() { std::cout << "f1()\n"; }
    void f2() { std::cout << "f2()\n"; } // 敲错键盘了，语义错误：没有 std::ccccout
};

int main(){

    std::cout << aTMPN<10>::ret << '\n';
    aTMP1<int> a;
    a.f1();
    // a.f2(); // 这句代码被注释时，aTMP<int>::f2() 不被实例化，从而上面的错误被掩盖!

    typedef unsigned int uint; // typedef 定义类型别名而不是引入新类型
    typedef uint uint2;
    std::cout << theSameType<unsigned, uint2>::ret << '\n';
    // 感谢 C++11，连续角括号“>>”不会被当做流输入符号而编译错误
    std::cout << theSameType<aTMP<unsigned, 2>, aTMP<uint2, 2>>::ret << '\n';
    std::cout << theSameType<aTMP<int, 2>, aTMP<int, 3>>::ret << '\n';
    return 0;
}