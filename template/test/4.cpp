//
// Created by hou guoli on 2018/3/28.
//

#include <iostream>

// 通例为空，若不匹配特例将报错，很好的调试手段（这里是 bool 就无所谓了）
template<bool c, typename Then, typename Else> class IF_ { };
template<typename Then, typename Else>
class IF_<true, Then, Else> { public: typedef Then reType; };
template<typename Then, typename Else>
class IF_<false,Then, Else> { public: typedef Else reType; };

//// 隐含要求： Condition 返回值 ret，Statement 有类型 Next
template<template<typename> class Condition, typename Statement>
class WHILE_ {
    template<typename Statement> class STOP { public: typedef Statement reType; };
public:
    typedef typename
    IF_<Condition<Statement>::ret,
            WHILE_<Condition, typename Statement::Next>,
            STOP<Statement>>::reType::reType
            reType;
};

// 计算 1^e+2^e+...+n^e
template<int n, int e>
class sum_pow {
    template<int i, int e> class pow_e{ public: enum{ ret=i*pow_e<i,e-1>::ret }; };
    template<int i> class pow_e<i,0>{ public: enum{ ret=1 }; };
    // 计算 i^e，嵌套类使得能够定义嵌套模板元函数，private 访问控制隐藏实现细节
    template<int i> class pow{ public: enum{ ret=pow_e<i,e>::ret }; };
    template<typename stat>
    class cond { public: enum{ ret=(stat::ri<=n) }; };
    template<int i, int sum>
    class stat { public: typedef stat<i+1, sum+pow<i>::ret> Next;
        enum{ ri=i, ret=sum }; };
public:
    enum{ ret = WHILE_<cond, stat<1,0>>::reType::ret };
};

int main() {
    std::cout << sum_pow<10, 2>::ret << '\n';
    std::cin.get(); return 0;
}