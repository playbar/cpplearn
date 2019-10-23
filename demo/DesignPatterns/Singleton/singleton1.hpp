//
// Created by hou guoli on 2019/10/23.
//
// 普通懒汉式单例 （ 线程不安全 ）
#include <iostream> // std::cout
#include <mutex>    // std::mutex
#include <pthread.h> // pthread_create

class SingleInstance
{

public:
    // 获取单例对象
    static SingleInstance *GetInstance();

    // 释放单例，进程退出时调用
    static void deleteInstance();

    // 打印单例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    SingleInstance();
    ~SingleInstance();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstance(const SingleInstance &signal);
    const SingleInstance &operator=(const SingleInstance &signal);

private:
    // 唯一单例对象指针
    static SingleInstance *m_SingleInstance;
};

//初始化静态成员变量
SingleInstance *SingleInstance::m_SingleInstance = NULL;

SingleInstance* SingleInstance::GetInstance()
{

    if (m_SingleInstance == NULL)
    {
        m_SingleInstance = new (std::nothrow) SingleInstance;  // 没有加锁是线程不安全的，当线程并发时会创建多个实例
    }

    return m_SingleInstance;
}

void SingleInstance::deleteInstance()
{
    if (m_SingleInstance)
    {
        delete m_SingleInstance;
        m_SingleInstance = NULL;
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
///////////////////  普通懒汉式实现 -- 线程不安全  //////////////////


