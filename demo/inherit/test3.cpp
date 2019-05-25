//
// Created by mac on 2019-05-25.
//

#include<iostream>
using namespace std;

class A  //大小为4
{
public:
    A(){cout<<"A" << endl;}
    virtual void fun1(){ cout<< "A, fun1" << endl; }
public:
    int a;
};
class B :virtual public A  //大小为12，变量a,b共8字节，虚基类表指针4
{
public:
    B(){cout<<"B" <<endl;}
    virtual void fun1(){ cout<< "B, fun1" << endl; }
    int b;
};
class C :virtual public A //与B一样12
{
public:
    C(){cout<<"C" <<endl; }
    virtual void fun1(){ cout<< "C, fun1" << endl; }
    int c;
};
class D :public B, public C //24,变量a,b,c,d共16，B的虚基类指针4，C的虚基类指针
{
public:
    D(){cout<<"D"<<endl;}
    virtual void fun1(){ cout<< "D, fun1" << endl; }
    int d;
};

int main()
{
    A a;
    B b;
    C c;
    D d;
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    cout << sizeof(c) << endl;
    cout << sizeof(d) << endl;
    a.fun1();
    b.fun1();
    c.fun1();
    d.fun1();
//    system("pause");
    return 0;
}


