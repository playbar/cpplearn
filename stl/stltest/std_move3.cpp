//
// Created by hou guoli on 2019/6/5.
//

#include <iostream>
#include <vector>

class B
{
public:
    B() {}
    B(const B&) { std::cout << "B Constructor" << std::endl; }
};

class A
{
public:
    A(): m_b(new B()) { std::cout << "A Constructor" << std::endl; }
    A(const A& src) :
            m_b(new B(*(src.m_b)))
    {
        std::cout << "A Copy Constructor" << std::endl;
    }
    A(A&& src) :
            m_b(src.m_b)
    {
        src.m_b = nullptr;
        std::cout << "A Move Constructor" << std::endl;
    }
    ~A() { delete m_b; }

private:
    B* m_b;
};

static A getA()
{
    A a;
    std::cout << "================================================" << std::endl;
    return a;
}

int main()
{
    A a = getA();
    std::cout << "================================================" << std::endl;
    A a1(a);

    return 0;
}

