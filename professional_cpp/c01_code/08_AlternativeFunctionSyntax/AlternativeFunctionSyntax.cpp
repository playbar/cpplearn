#include <iostream>

using std::cout;
using std::endl;

auto func(int i) -> int
{
    return i + 2;
}

auto fun1(char *pstr ) ->char *
{
    return pstr;
}

auto div(double num1, double num2)
{
    if(num2 == 0 )
    {
        return num1;
    }
    return num1/ num2, num1;
}

auto main() -> int
{
    auto data = div(6, 2);
    cout << func(3) << endl;
    cout <<fun1("test") << endl;


	return 0;
}
