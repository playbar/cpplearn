//
// Created by hou guoli on 2019/1/8.
//

#include <mach/task_info.h>
#include <mach/mach_init.h>
#include <mach/task.h>
#import  <mach/mach.h>
#include "vector"
#include "myalloc.h"
#include "smartptr_test.h"
#include "assert.h"

#import <sys/types.h>
#import <sys/sysctl.h>
#import <mach/host_info.h>
#import <mach/mach_host.h>
#import <mach/task_info.h>
#import <mach/task.h>


using namespace std;

void test_unique_ptr()
{
    //智能指针的创建
    unique_ptr<int> u_i; 	//创建空智能指针
    u_i.reset(new int(3)); 	//绑定动态对象
    unique_ptr<int> u_i2(new int(4));//创建时指定动态对象

//所有权的变化
    int *p_i = u_i2.release();	//释放所有权
    unique_ptr<string> u_s(new string("abc"));
    unique_ptr<string> u_s2 = std::move(u_s); //所有权转移(通过移动语义)，u_s所有权转移后，变成“空指针”
    u_s2.reset(u_s.release());	//所有权转移
    u_s2=nullptr;//显式销毁所指对象，同时智能指针变为空指针。与u_s2.reset()等价

}

void test_auto_ptr()
{
    auto_ptr<string> films[5] =
            {
            auto_ptr<string> (new string("Fowl Balls")),
            auto_ptr<string> (new string("Duck Walks")),
            auto_ptr<string> (new string("Chicken Runs")),
            auto_ptr<string> (new string("Turkey Errors")),
            auto_ptr<string> (new string("Goose Eggs"))
    };
    auto_ptr<string> pwin;
    pwin = films[2]; // films[2] loses ownership. 将所有权从films[2]转让给pwin，此时films[2]不再引用该字符串从而变成空指针

    cout << "The nominees for best avian baseballl film are\n";
    for(int i = 0; i < 5; ++i)
    {
        cout << *films[i] << endl;
    }
    cout << "The winner is " << *pwin << endl;

}

void test_shared_ptr()
{
    //定义一个基础对象类指针
    int* ia = new int(10);
    {
        SmartPtr<int> sptr1(ia);
        cout <<"sptr1:"<<*sptr1<<endl;
        {
            SmartPtr<int> sptr2(sptr1);
            cout <<"sptr2:"<<*sptr2<<endl;
            *sptr2=5;
            {
                SmartPtr<int> sptr3=sptr1;
                cout <<"sptr3:"<<*sptr3<<endl;
            }
        }
    }
    //此时count=0；pa对象被delete掉
    cout << *ia << endl;

}

/*
weak_ptr<T> w;	 	//创建空 weak_ptr，可以指向类型为 T 的对象。
weak_ptr<T> w(sp);	//与 shared_ptr 指向相同的对象，shared_ptr 引用计数不变。T必须能转换为 sp 指向的类型。
w=p;				//p 可以是 shared_ptr 或 weak_ptr，赋值后 w 与 p 共享对象。
w.reset();			//将 w 置空。
w.use_count();		//返回与 w 共享对象的 shared_ptr 的数量。
w.expired();		//若 w.use_count() 为 0，返回 true，否则返回 false。
w.lock();			//如果 expired() 为 true，返回一个空 shared_ptr，否则返回非空 shared_ptr。
 */
void test_weak_ptr()
{
    shared_ptr<int> sp(new int(10));
    assert(sp.use_count() == 1);
    weak_ptr<int> wp(sp); 	//从shared_ptr创建weak_ptr
    assert(wp.use_count() == 1);
    if (!wp.expired())		//判断weak_ptr观察的对象是否失效
    {
        shared_ptr<int> sp2 = wp.lock();//获得一个shared_ptr
        *sp2 = 100;
        assert(wp.use_count() == 2);
    }
    assert(wp.use_count() == 1);
    cout << "int:" << *sp << endl;
}

void test_weak_ptr_1()
{
    std::shared_ptr<Man> m(new Man());
    std::shared_ptr<Woman> w(new Woman());
    if (m && w) {
        m->setWife(w);
        w->setHusband(m);
    }
    return;
}

int main()
{
    test_unique_ptr();
//    test_auto_ptr();
    test_shared_ptr();
    test_weak_ptr_1();
    test_weak_ptr();
    return 0;
}