//
// Created by hou guoli on 2019/10/23.
//


#include <iostream> // std::cout
#include <mutex>    // std::mutex
#include <pthread.h> // pthread_create

// 内部静态变量的懒汉单例（C++11 线程安全）
///////////////////  内部静态变量的懒汉实现  //////////////////
class SingleInstance
{

public:
    // 获取单实例对象
    static SingleInstance *GetInstance();

    static void deleteInstance();

    // 打印实例地址
    void Print();

private:
    // 禁止外部构造
    SingleInstance();

    // 禁止外部析构
    ~SingleInstance();

    // 禁止外部复制构造
    SingleInstance(const SingleInstance &signal);

    // 禁止外部赋值操作
    const SingleInstance &operator=(const SingleInstance &signal);
};

SingleInstance *SingleInstance::GetInstance()
{
    // 局部静态特性的方式实现单实例
    static SingleInstance signal;
    return &signal;
}

void SingleInstance::deleteInstance()
{

}

void SingleInstance::Print()
{
    std::cout << "我的实例内存地址是:" << this << std::endl;
}

SingleInstance::SingleInstance()
{
    std::cout << "构造函数" << std::endl;
}

SingleInstance::~SingleInstance()
{
    std::cout << "析构函数" << std::endl;
}
///////////////////  内部静态变量的懒汉实现  //////////////////

