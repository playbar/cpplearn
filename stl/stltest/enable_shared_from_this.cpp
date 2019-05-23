//
// Created by hou guoli on 2018/3/12.
//

#include <memory>

class Base;
class Derived;

void function1(std::shared_ptr<Base> derived)
{
    // ...
}

void function2(std::shared_ptr<Derived> derived)
{
    // ...
}

class Base : public std::enable_shared_from_this<Base>
{
public:
    Base() { /* ... */ }
    virtual  ~Base() { }

    void method()
    {
        // ...

        // 传递该类shared_ptr托管的this指针
        function1(shared_from_this());
    }
    // ...

private:
    // ...
};



class Derived : public Base
{
public:
    Derived() { }

    ~Derived() { }

    void method()
    {
        // ...

        // 错误：不存在用户定义的从“std::shared_ptr<Base>”到“std::shared_ptr<Derived>”的适当转换
//        function2(shared_from_this());
        // shared_from_this()的返回值类型为std::shared_ptr<Base>，使用std::dynamic_pointer_cast<Derived>函数将其转为std::shared_ptr<Derived>类型
        std::shared_ptr<Derived> pointer = std::dynamic_pointer_cast<Derived>(shared_from_this());
        function2(pointer);
    }

private:
    // ...
};



int main()
{
    std::shared_ptr<Derived> derived = std::make_shared<Derived>();
    derived->method();
    return 0;
}


//1. 使用std::dynamic_pointer_cast<T>()需要基类中存在虚函数，这是由于这个转换函数使用输入的
//        类型和目标类型中是否存在相同签名的虚函数作为转换能否成功的标识。最简单也是正确的解决方法
//        是将基类中的析构函数声明为虚函数。
//2. 不能在构造函数中使用shared_form_this()。这是由于std::enable_share_from_this在实现时
//        使用了一个对象的weak_ptr，而这个weak_ptr需要对象的shared_ptr进行初始化。由于此时对象
//        尚未构造完成，所以会抛出std::bad_weak_ptr的异常。关于这点目前没有较为完美的方案，
//        可以尝试写一个init()函数，在对象构造后手动调用。或是手动写一个std::shared_ptr<Derived>(this)使用，
//        但这种解决方案可能造成循环引用。