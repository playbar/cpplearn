//
// Created by hou guoli on 2018/3/28.
//

#include <iostream>

// 元容器
template<typename T0=void, typename T1=void, typename T2=void, typename T3=void>
class meta_container {
public:
    typedef T0 type;
    typedef meta_container<T1, T2, T3, void> next_node; // 参数移位了
    static const int size = next_node::size + 1; // 非 null_type 模板参数个数
};
template<> // 特例，递归终止
class meta_container<void, void, void, void> {
public:
    typedef void type;
    static const int size = 0;
};

// 访问元容器中的数据
template<typename C, unsigned i>
class get {
public:
    static_assert(i<C::size, "get<C,i>: index exceed num"); // C++11 引入静态断言
    typedef typename get<C,i-1>::c_type::next_node c_type;
    typedef typename c_type::type ret_type;
};
template<typename C>
class get<C, 0> {
public:
    static_assert(0<C::size, "get<C,i>: index exceed num"); // C++11 引入静态断言
    typedef C c_type;
    typedef typename c_type::type ret_type;
};

// 在元容器中查找某个类型，找到返回索引，找不到返回 -1
template<typename T1, typename T2> class same_type { public: enum { ret = false }; };
template<typename T> class same_type<T, T> { public: enum { ret = true }; };

template<bool c, typename Then, typename Else> class IF_ { };
template<typename Then, typename Else>
class IF_<true, Then, Else> { public: typedef Then reType; };
template<typename Then, typename Else>
class IF_<false, Then, Else> { public: typedef Else reType; };

template<typename C, typename T>
class find {
    template<int i> class number { public: static const int ret = i; };

    template<typename C, typename T, int i>
    class find_i {
    public:
        static const int ret = IF_< same_type<get<C,i>::ret_type, T>::ret,
                number<i>, find_i<C,T,i-1> >::reType::ret;
    };
    template<typename C, typename T>
    class find_i<C, T, -1> {
    public:
        static const int ret = -1;
    };
public:
    static const int ret = find_i<C, T, C::size-1>::ret;
};

int main(){
    typedef meta_container<int, int&, const int> mc;
    int a = 9999;
    get<mc, 1>::ret_type aref = a;
    std::cout << mc::size << '\n';
    std::cout << aref << '\n';
    std::cout << find<mc, const int>::ret << '\n';
    std::cout << find<mc, float>::ret << '\n';
    std::cin.get(); return 0;
}


/////////////


// 类型过滤，meta_filter 使用时只用一个参数，设置四个模板参数是因为，模板通例的参数列表
// 必须能够包含特例参数列表，后面三个参数设置默认值为 void 或标签模板
template<typename T> class dummy_template_1 {};
template<typename T0, typename T1> class dummy_template_2 {};
template<typename T0, typename T1 = void,
        template<typename> class tmp_1 = dummy_template_1,
        template<typename, typename> class tmp_2 = dummy_template_2>
class meta_filter { // 通例，不改变类型
public:
    typedef T0 ret_type;
};
// 匹配任何带有一个类型参数模板的实例，将模板实例替换为代表实例
template<template<typename> class tmp_1, typename T>
class meta_filter<tmp_1<T>, void, dummy_template_1, dummy_template_2> {
public:
    typedef tmp_1<int> ret_type;
};
// 匹配任何带有两个类型参数模板的实例，将模板实例替换为代表实例
template<template<typename, typename> class tmp_2, typename T0, typename T1>
class meta_filter<tmp_2<T0, T1>, void, dummy_template_1, dummy_template_2> {
public:
    typedef tmp_2<int, int> ret_type;
};

/////////

//template<typename, typename> class my_tmp_2;
//
//// 自动将 my_tmp_2<float, int> 过滤为 my_tmp_2<int, int>
//typedef meta_container<int, float, my_tmp_2<float, int>> mc2;
//// 自动将 my_tmp_2<char, double> 过滤为 my_tmp_2<int, int>
//std::cout << find<mc2, my_tmp_2<char, double>>::ret << '\n'; // 输出 2
