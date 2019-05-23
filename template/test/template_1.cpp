//
// Created by hou guoli on 2018/3/28.
//

#include <iostream>

// 函数模板
template<typename T>
bool equivalent(const T& a, const T& b){
    return !(a < b) && !(b < a);
}

namespace test {
// 类模板
    template<class T=int, class T1 = float> // 默认参数
    class bignumber {
    public:
        T _v;
        T1 _v1;
    public:
        bignumber(T a, T1 b = 5.0f) : _v(a), _v1(b) {}

        inline bool operator<(const bignumber &b) const; // 等价于 (const bignumber<T>& b)
        void showdata();
    };

// 在类模板外实现成员函数
    template<class T, class T1>
    bool bignumber<T, T1>::operator<(const bignumber &b) const {
        return _v < b._v;
    }

    template<class T, class T1>
    void bignumber<T, T1>::showdata() {
        printf("%d, %f \n", _v, _v1);
    }

    template<class T, class T1>
    inline bool
    operator ==(const bignumber<T, T1>& x1, const bignumber<T, T1> &x2)
    {
        return x1._v == x2._v && x1._v1 == x2._v1;
    };
}

int main()
{
    test::bignumber<> a(1), b(1); // 使用默认参数，"<>"不能省略
    a.showdata();
    b.showdata();
    if(a == b)
        printf("equal");
    else
        printf("no equal");

    std::cout << equivalent(a, b) << '\n'; // 函数模板参数自动推导
    std::cout << equivalent<double>(1, 2) << '\n';
    return 0;
}
