//
// Created by hou guoli on 2018/3/14.
//

#include <iostream>
#include <type_traits>

using  namespace   std;




int main()
{
    typedef     integral_constant<int, 111>     IC;
    cout << "value " << IC::value << endl;
    cout << "value_type   " << typeid(IC::value_type).name() << endl;
    cout << "type  " << typeid(IC::type).name() << endl;
    IC   ic;
    int   c1 = ic;  //调用的operator value_type()
    cout << c1 << endl;
    int  c2 = ic();//调用的 operator()()
    cout << c1 << endl;
    cout << integral_constant<char,  'a'>::value <<endl;

/*
非型别模版参数必须是整型或者和整型兼容的，  double和float不行
cout << integral_constant<double, 12.23>::value << endl;
cout << integral_constant<float, 12.23f>::value << endl;
*/

    cout << true_type::value << endl;
//    cout << bool_constant <false>::value << endl;
//    cout << factorial<5>::value<<endl;  // constexpr (no calculations on runtime)

    return 0;
}