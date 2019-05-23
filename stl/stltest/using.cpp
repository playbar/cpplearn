//
// Created by hou guoli on 2018/3/13.
//

#include "iostream"

class Base {
public:
    Base(int aa, int bb )
    {
        maa = aa;
        mbb = bb;
    }
public:
    int menfcn()
    {
        std::cout<<"Base function"<<std::endl;
        return 0;
    }

protected:
    int maa;
    int mbb;
};


class Derived : public Base
{
public:
    using Base::Base;
    using Base::menfcn;//using声明只能指定一个名字，不能带形参表
    int menfcn(int num)
    {
        std::cout << "Derived function with int : "<< num << std::endl;
        return num;
    }

};

int main()
{
    Base b(3,4);
    Derived d(1, 2);
    b.menfcn();
    d.menfcn();
    d.menfcn(5);
    return 0;
}