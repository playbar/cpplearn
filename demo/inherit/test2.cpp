//
// Created by mac on 2019-05-25.
//

#include <iostream>
using namespace std;

class Base1
{
public:
    virtual void fun1(){ cout<<"Base1, fun1" << endl;}
private:
    int m_base1;
};

class Base2
{
public:
    virtual void fun1(){ cout<<"Base2, fun1" << endl;}
    virtual void fun2(){ cout<<"Base2, fun2" << endl;}
private:
    int m_base2;
};

class Derive : virtual public Base1, virtual public Base2
{
public:
    virtual void fun1(){cout<<"Derive, fun1" << endl; }
    virtual void fun3(){ cout<< "Derive, fun3" << endl; }
private:
    int m_derive;
};

int main()
{
    Base1 b1;
    Base2 b2;
    Derive d;

    cout <<"b1:" <<sizeof(b1) << endl;
    cout << "b2:" << sizeof(b2) << endl;
    cout <<"d:" << sizeof(d) << endl;
    b1.fun1();
    b2.fun1();
    d.fun1();
//    system("pause");
    return 0;
}

