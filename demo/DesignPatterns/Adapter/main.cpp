#include <iostream>
#include "Adapter.hpp"

class target
{
public:
    virtual ~target() {}
    virtual void request() = 0;
};

class adaptee
{
public:
    void specific_request()
    {
        std::cout << "call specific_request" << std::endl;
    }
};

class adapter : public target
{
public:
    adapter()
    {
        _adaptee = new adaptee(); 
    }

    ~adapter()
    {
        delete _adaptee; 
    }

    void request()
    {
        _adaptee->specific_request();
    }

private:
    adaptee* _adaptee;
};

void testAdapter()
{
    target* t = new adapter();
    t->request();
    delete t;
}

int main()
{
    testAdapter();
    test_Adapter1();
    return 0;
}
