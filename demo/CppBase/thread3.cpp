//
// Created by hou guoli on 2018/2/12.
//

#include <iostream>
#include <thread>
using namespace std;

void t1()
{
    for (int i = 0; i < 20; ++i)
    {
        cout << "t1111\n";
    }
}
void t2()
{
    for (int i = 0; i < 20; ++i)
    {
        cout << "t22222\n";
    }
}
int main()
{
//    thread th1(t1);
//    thread th2(t2);
    thread th1 = std::thread([&]{
        for (int i = 0; i < 20; ++i)
        {
            cout << "t1111\n";
        }
    });

    thread th2 = std::thread([&]{
        for (int i = 0; i < 20; ++i)
        {
            cout << "t22222\n";
        }
    });

    th1.join(); //等待th1执行完
    th2.join(); //等待th2执行完

    cout << "here is main\n\n";

    return 0;
}

