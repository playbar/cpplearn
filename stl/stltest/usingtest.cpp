//
// Created by hou guoli on 2018/2/7.
//



#include <iostream>
using namespace std;

class Base
{
public:
    int menfcn()
    {
        cout<<"Base function"<<endl;
        return 0;
    }
};
class Derived : Base
{
public:
    using Base::menfcn;//using声明只能指定一个名字，不能带形参表
    int menfcn(int num)
    {
        cout << "Derived function with int : "<< num << endl;
        return num;
    }
};

int main_1()
{
    Base b; Derived d;
    b.menfcn();
    d.menfcn();//如果去掉Derived类中的using声明，会出现错误：error C2660: 'Derived::menfcn' : function does not take 0 arguments
    std::cin.ignore(std::cin.gcount()+1);//清空缓冲区
    std::cin.get();//暂停程序执行
}



