//
// Created by hou guoli on 2019/10/23.
//


#include <iostream> // std::cout
#include <mutex>    // std::mutex
#include <pthread.h> // pthread_create

//  饿汉式单例 （本身就线程安全）
////////////////////////// 饿汉实现 /////////////////////
class SingleInstance
{
public:
    // 获取单实例
    static SingleInstance* GetInstance();

    // 释放单实例，进程退出时调用
    static void deleteInstance();

    // 打印实例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    SingleInstance();
    ~SingleInstance();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstance(const SingleInstance &signal);
    const SingleInstance &operator=(const SingleInstance &signal);

private:
    // 唯一单实例对象指针
    static SingleInstance *g_pSingleInstance;
};

// 代码一运行就初始化创建实例 ，本身就线程安全
SingleInstance* SingleInstance::g_pSingleInstance = new (std::nothrow) SingleInstance;

SingleInstance* SingleInstance::GetInstance()
{
    return g_pSingleInstance;
}

void SingleInstance::deleteInstance()
{
    if (g_pSingleInstance)
    {
        delete g_pSingleInstance;
        g_pSingleInstance = NULL;
    }
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
////////////////////////// 饿汉实现 /////////////////////
