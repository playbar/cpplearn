#include <iostream>

template<int N>
class sumt{
public:
    static const int ret = sumt<N-1>::ret + N;
};

template<>
class sumt<0>{
public: static const int ret = 0;
};

int main() {
    std::cout << sumt<5>::ret << '\n';
    std::cin.get();
    return 0;
}