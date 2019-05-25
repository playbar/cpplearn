//
// Created by mac on 2019-05-25.
//

#include <iostream>
using namespace std;

class Base
{
public:
    virtual void fun1(){ cout << "Base fun1" << endl; }
    virtual void fun2(){ cout << "Base fun2" << endl; }
private:
    int a;
};

class Derive :  public Base
{
public:
    void fun2(){ cout << "Derive fun2" << endl; }
    virtual void fun3(){}
private:
    int b;
};

int main()
{
    Base b;
    Derive d;
    Base *p = &d;
    p->fun1();
    p->fun2();

    system("ls -ls");
    return 0;
}

