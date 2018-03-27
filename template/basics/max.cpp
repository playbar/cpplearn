/* The following code example is taken from the book
 * "C++ Templates - The Complete Guide"
 * by David Vandevoorde and Nicolai M. Josuttis, Addison-Wesley, 2002
 *
 * (C) Copyright David Vandevoorde and Nicolai M. Josuttis 2002.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
#include <iostream>
#include <string>
#include "max.hpp"

template <typename T>
T const& min(T const& a, T const& b)
{
    return ( (a < b) ? a : b );
}

template <typename T1, typename T2>
T1 const& mymin(T1 const& a, T2 const& b)
{
    return ( (a < b) ? a : b );
}

int main()
{
    int i = 42;
    std::cout << "max(7,i):   " << ::max(7,i) << std::endl;
    std::cout << "min(7,i):   " << ::min(7, i) << std::endl;
    std::cout << "mymin(7,i):   " << ::mymin(7, i) << std::endl;

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1,f2): " << ::max(f1,f2) << std::endl;

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1,s2): " << ::max(s1,s2) << std::endl;

    std::cout << "max(7,f1): " << ::max<float>(7, f1) << std::endl;
}
