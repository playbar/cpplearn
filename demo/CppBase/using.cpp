//
// Created by hou guoli on 2018/3/13.
//

#include "vector"

class Base {
public:
    Base(int aa, int bb )
    {
        maa = aa;
        mbb = bb;
    }
protected:
    int size() const {return maa; }
protected:
    int maa;
    int mbb;
};


class Derived : public Base
{
    using Base::Base;
};

int main()
{
    Derived der(1, 2);
    return 0;
}