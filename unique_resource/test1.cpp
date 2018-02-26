//
// Created by hou guoli on 2018/2/26.
//

#include <iostream>
#include "unique_resource.hpp"


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

class mytest{
public:
    mytest()
    {
        std::cout << "mytest construct" << std::endl;
    }
    ~mytest()
    {
        std::cout << "mytest desstruct" << std::endl;
    }

    decltype(auto) testunique()
    {
        auto hanle = std_experimental::make_unique_resource(12,  &ReleaseHandle);
        return hanle;
    }
};

int main() {
    auto handle1 = make_unique_handle(1);
    {
        auto handle2 = make_unique_handle(2);
        std::cout << handle2.get() << std::endl; // raw handle access by get()
        // here, handle2 is released.
        mytest test;
        test.testunique();
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

