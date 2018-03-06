//
// Created by hou guoli on 2018/2/26.
//

#include <iostream>
#include "unique_resource.hpp"

class mytest;

// some dummy resource functions
using handle_t = int;
decltype(auto) GenHandle(handle_t i)
{
    std::cout<< "get handle " << i << std::endl;
    return i;
}
decltype(auto) ReleaseHandle(handle_t handle) {
    std::cout << "release handle " << handle << std::endl;
}

decltype(auto) make_unique_handle(handle_t i) {
    return std_experimental::make_unique_resource(
            GenHandle(i), &ReleaseHandle);
}

class RenderBuffer {
public:
    mytest* context;
    void operator()(int) const
    {
        std::cout<< context << std::endl;
    }

    RenderBuffer(mytest *ptest)
    {
        context = ptest;
    }

    RenderBuffer(const RenderBuffer &rb) : context(0)
    {
        operator=(rb);
//        context = rb.context;
    }

    RenderBuffer& operator=(const RenderBuffer &rb)
    {
        context = rb.context;
        return *this;
    }

    ~RenderBuffer()
    {
        std::cout << "RenderBuffer desstruct" << std::endl;
    }

};

class mytest{
public:
    using UniqueProgram = std_experimental::unique_resource<int, RenderBuffer>;
    mytest():mhandle{12,  {this} }
    {
//        RenderBuffer buffer(this);
//        mhandle = std_experimental::make_unique_resource(12,  buffer);
        std::cout << "mytest construct" << std::endl;
    }
    ~mytest()
    {
        std::cout << "mytest desstruct" << std::endl;
    }

    decltype(auto) testunique()
    {
//        RenderBuffer buffer = {this};
        UniqueProgram hanle{12,  {this}};
        return hanle;
    }

private:
    std_experimental::unique_resource<int, RenderBuffer> mhandle;
};

int main() {
    union {
        int i;
        char x[2];
        char m[4];
    } data;

    data.x[0] = 10;
    data.x[1] = 1;
    printf("%d", data.i);


    {
        mytest test;
//        test.testunique();
    }
    auto handle1 = make_unique_handle(1);
    {
        auto handle2 = make_unique_handle(2);
        std::cout << handle2.get() << std::endl; // raw handle access by get()
        // here, handle2 is released.

    }

    auto handle3 = make_unique_handle(3);
    handle3.reset(); // release handle explicitly
    {
        auto handle4 = make_unique_handle(4);
        auto raw_handle4 = handle4.release(); // strip RAII wrapper
        ReleaseHandle(raw_handle4); // now, we should release handle by hand.
    }
    {
        auto handle5 = make_unique_handle(5);
        auto handle6 = std::move(handle5); // move construct
        handle6.reset(GenHandle(6)); // reset raw handle
    }

    std::cout << "Bye!" << std::endl;
}

