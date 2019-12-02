#ifndef __SMARTPTR_TEST_H__
#define __SMARTPTR_TEST_H__

using namespace std;

class Point
{
private:
    int x, y;
public:
    Point(int xVal = 0, int yVal = 0) :x(xVal), y(yVal) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }
};


//模板类作为友元时要先有声明
template <typename T> class SmartPtr;

//辅助类
template <typename T> class RefPtr
{
private:
    //该类成员访问权限全部为private，因为不想让用户直接使用该类
    friend class SmartPtr<T>;      //定义智能指针类为友元，因为智能指针类需要直接操纵辅助类

    //构造函数的参数为基础对象的指针
    RefPtr(T *ptr) :p(ptr), count(1) { }

    //析构函数
    ~RefPtr() { delete p; }
    //引用计数
    int count;

    //基础对象指针
    T *p;
};

//智能指针类
template <typename T> class SmartPtr
{
public:
    SmartPtr(T *ptr) :rp(new RefPtr<T>(ptr)) { }      //构造函数
    SmartPtr(const SmartPtr<T> &sp) :rp(sp.rp) { ++rp->count; }  //复制构造函数
    SmartPtr& operator=(const SmartPtr<T>& rhs)       //重载赋值操作符
    {
        ++rhs.rp->count;        //首先将右操作数引用计数加1，
        if (--rp->count == 0)   //然后将引用计数减1，可以应对自赋值
            delete rp;
        rp = rhs.rp;
        return *this;
    }

    T & operator *()        //重载*操作符
    {
        return *(rp->p);
    }
    T* operator ->()       //重载->操作符
    {
        return rp->p;
    }
    ~SmartPtr()            //析构函数
    {
        if (--rp->count == 0)    //当引用计数减为0时，删除辅助类对象指针，从而删除基础对象
            delete rp;
        else
        {
            cout << "还有" << rp->count << "个指针指向基础对象" << endl;
        }
    }
private:
    RefPtr<T> *rp;  //辅助类对象指针
};


//////////

class Woman;
class Man
{
private:
    std::weak_ptr<Woman> _wife;
//    std::shared_ptr<Woman> _wife;
public:

    Man()
    {
        std::cout << "create man\n";
    }

    void setWife(std::shared_ptr<Woman> woman)
    {
        _wife = woman;
    }

//    void doSomthing()
//    {
//        if(_wife.lock())
//        {
//        }
//    }

    ~Man()
    {
        std::cout << "kill man\n";
    }
};

class Woman
{
private:
    std::weak_ptr<Man> _husband;
//    std::shared_ptr<Man> _husband;
public:
    Woman()
    {
        std::cout <<"create woman\n";
    }

    void setHusband(std::shared_ptr<Man> man)
    {
        _husband = man;
    }
    ~Woman()
    {
        std::cout <<"kill woman\n";
    }
};


#endif

