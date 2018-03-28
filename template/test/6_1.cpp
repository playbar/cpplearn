//
// Created by hou guoli on 2018/3/28.
//

#include <iostream> // std::cout

// 模板基类，定义接口，具体实现由模板参数，即子类实现
template <typename E>
class base {
public:
    void f1() { static_cast<E&>(*this).f1(); } // 直接调用子类实现
    int f2() const { static_cast<const E&>(*this).f1(); }
};

// 子类

class dirived1 : public base<dirived1> {
public:
    void f1() { /* ... */ }
    int f2() const { /* ... */ }
};

template<typename T>
class dirived2 : public base<dirived2<T>> {
public:
    void f1() { /* ... */ }
    int f2() const { /* ... */ }
};

/////////

// A CRTP base class for Vecs with a size and indexing:
template <typename E>
class VecExpr {
public:
    double operator[](int i) const
    {
        return static_cast<E const&>(*this)[i];
    }

    operator E const&() const
    {
        return static_cast<const E&>(*this);
    } // 向下类型转换

};

// The actual Vec class:
class Vec : public VecExpr<Vec>
{
    double _data[1000];
public:
    double&  operator[](int i) { return _data[i]; }
    double operator[](int i) const { return _data[i]; }
    template <typename E>
    Vec const& operator=(VecExpr<E> const& vec)
    {
        E const& v = vec;
        for (int i = 0; i<1000; ++i)
            _data[i] = v[i];
        return *this;
    }
    // Constructors
    Vec() { }
    Vec(double v)
    {
        for(int i=0; i<1000; ++i)
            _data[i] = v;
    }

};

template <typename E1, typename E2>
class VecDifference : public VecExpr<VecDifference<E1, E2> >
{
    E1 const& _u;
    E2 const& _v;
public:
    VecDifference(VecExpr<E1> const& u, VecExpr<E2> const& v) : _u(u), _v(v) { }
    double operator[](int i) const
    {
        return _u[i] - _v[i];
    }
};

template <typename E>
class VecScaled : public VecExpr<VecScaled<E> >
{
    double _alpha;
    E const& _v;
public:
    VecScaled(double alpha, VecExpr<E> const& v) : _alpha(alpha), _v(v) { }
    double operator[](int i) const
    {
        return _alpha * _v[i];
    }
};

// Now we can overload operators:
template <typename E1, typename E2>
VecDifference<E1, E2> const
operator-(VecExpr<E1> const& u, VecExpr<E2> const& v)
{
    return VecDifference<E1, E2>(u, v);
}

template <typename E> VecScaled<E> const
operator*(double alpha, VecExpr<E> const& v)
{
    return VecScaled<E>(alpha, v);
}

int main() {
    Vec u(3), v(1);
    double alpha=9;
    Vec y;
    y = alpha*(u - v);
    std::cout << y[999] << '\n';
    return 0;
}

