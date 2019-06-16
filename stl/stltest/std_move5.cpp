//
// Created by hou guoli on 2019/6/5.
//

#include <iostream>
#include <vector>

int gIndex = 0;

class B
{
public:
    B()
    {
        gIndex++;
        mib = gIndex;
        std::cout << "B Constructor" << std::endl;
    }
    B(const B& b) {
        mib = b.mib;
        std::cout << "B Copy Constructor" << std::endl;
    }
    ~B() {
        std::cout << "B Destructor" << std::endl;
    }
    int mib;
};

class A
{
public:
    A(): m_pb(new B()) { std::cout << "A Constructor" << std::endl; }
    A(const A& src) : m_pb(new B(*(src.m_pb)))
    {
        std::cout << "A Copy Constructor" << std::endl;
    }
    A(A&& src) : m_pb(src.m_pb)
    {
        src.m_pb = nullptr;
        std::cout << "A Move Constructor" << std::endl;
    }
    A& operator=(const A& src) noexcept
    {
        if (this == &src)
            return *this;

        delete m_pb;
        m_pb = new B(*(src.m_pb));
        std::cout << "operator=(const A& src)" << std::endl;
        return *this;
    }
    A& operator=(A&& src) noexcept
    {
        if (this == &src)
            return *this;

        delete m_pb;
        m_pb = src.m_pb;
        src.m_pb = nullptr;
        std::cout << "operator=(const A&& src)" << std::endl;
        return *this;
    }
    ~A()
    {
        std::cout << "A Destructor" << std::endl;
        delete m_pb;
    }

private:
    B* m_pb;
    B mp;

};

static A getA()
{
    A a;
    std::cout << "================================================" << std::endl;
    return a;
}

A getMoveA()
{
    A a1;
    return std::move(a1);
}

int main()
{
    auto aa = getMoveA();
    A a = getA();//移动构造
    std::cout << "================================================" << std::endl;
    A a1(a);//拷贝构造
    std::cout << "================================================" << std::endl;
    A a2(std::move(a1));//移动构造
    std::cout << "================================================" << std::endl;
    a2 = getA();//移动赋值
    std::cout << "================================================" << std::endl;
    a2 = a1;//拷贝赋值
    return 0;
}

