#include "decltype.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52504519

/*
 * decltype和auto都可以用来推断类型，但是二者有几处明显的差异：
 * 1.auto忽略顶层const，decltype保留顶层const；
 * 2.对引用操作，auto推断出原有类型，decltype推断出引用；
 * 3.对解引用操作，auto推断出原有类型，decltype推断出引用；
 * 4.auto推断时会实际执行，decltype不会执行，只做分析。
 * 总之在使用中过程中和const、引用和指针结合时需要特别小心。
 */

//////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/decltype
struct A { double x; };
const A* a = new A{ 0 };

decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u); // return type depends on template parameters

int test_decltype1()
{
	int i = 33;
	decltype(i) j = i * 2;

	std::cout << "i = " << i << ", " << "j = " << j << '\n';

	auto f = [](int a, int b) -> int
	{
		return a * b;
	};

	decltype(f) g = f; // the type of a lambda function is unique and unnamed
	i = f(2, 2);
	j = g(3, 3);

	std::cout << "i = " << i << ", " << "j = " << j << '\n';

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd537655.aspx
template<typename T1, typename T2>
auto Plus(T1&& t1, T2&& t2) ->
decltype(std::forward<T1>(t1) +std::forward<T2>(t2))
{
	return std::forward<T1>(t1) +std::forward<T2>(t2);
}

class X
{
	friend X operator+(const X& x1, const X& x2)
	{
		return X(x1.m_data + x2.m_data);
	}

public:
	X(int data) : m_data(data) {}
	int Dump() const { return m_data; }
private:
	int m_data;
};

int test_decltype2()
{
	// Integer 
	int i = 4;
	std::cout << "Plus(i, 9) = " << Plus(i, 9) << std::endl;

	// Floating point
	float dx = 4.0;
	float dy = 9.5;
	std::cout << std::setprecision(3) << "Plus(dx, dy) = " << Plus(dx, dy) << std::endl;

	// String
	std::string hello = "Hello, ";
	std::string world = "world!";
	std::cout << Plus(hello, world) << std::endl;

	// Custom type
	X x1(20);
	X x2(22);
	X x3 = Plus(x1, x2);
	std::cout << "x3.Dump() = " << x3.Dump() << std::endl;

	return 0;
}

///////////////////////////////////////////////////
// reference: http://thbecker.net/articles/auto_and_decltype/section_06.html
struct S {
	S(){ m_x = 42; }
	int m_x;
};

int x;
const int cx = 42;
const int& crx = x;
const S* p = new S();

// x is declared as an int: x_type is int.
typedef decltype(x) x_type;

// auto also deduces the type as int: a_ is an int.
auto a_ = x;

// cx is declared as const int: cx_type is const int.
typedef decltype(cx) cx_type;

// auto drops the const qualifier: b is int.
auto b = cx;

// crx is declared as const int&: crx_type is const int&.
typedef decltype(crx) crx_type;

// auto drops the reference and the const qualifier: c is an int.
auto c = crx;

// S::m_x is declared as int: m_x_type is int
// Note that p->m_x cannot be assigned to. It is effectively
// constant because p is a pointer to const. But decltype goes
// by the declared type, which is int.
typedef decltype(p->m_x) m_x_type;

// auto sees that p->m_x is const, but it drops the const
// qualifier. Therefore, d is an int.
auto d = p->m_x;

int getSize();

int test1(void)
{
    int tempA = 2;

    /*1.dclTempA为int*/
    decltype(tempA) dclTempA;
    dclTempA = 3;
    /*2.dclTempB为int，对于getSize根本没有定义，但是程序依旧正常，因为decltype只做分析，并不调用getSize，*/
    decltype(getSize()) dclTempB;

    return 0;
}

void test2()
{
    double tempA = 3.0;
    const double ctempA = 5.0;
    const double ctempB = 6.0;
    const double *const cptrTempA = &ctempA;

    /*1.dclTempA推断为const double（保留顶层const，此处与auto不同）*/
    decltype(ctempA) dclTempA = 4.1;
    /*2.dclTempA为const double，不能对其赋值，编译不过*/
//    dclTempA = 5;
    /*3.dclTempB推断为const double * const*/
    decltype(cptrTempA) dclTempB = &ctempA;
    /*4.输出为4（32位计算机）和5*/
    std::cout<<sizeof(dclTempB)<<"    "<<*dclTempB<<std::endl;
    /*5.保留顶层const，不能修改指针指向的对象，编译不过*/
//    dclTempB = &ctempB;
    /*6.保留底层const，不能修改指针指向的对象的值，编译不过*/
//    *dclTempB = 7.0;
}

void test3()
{
    int tempA = 0;
    int &refTempA = tempA;

    /*1.dclTempA为引用，绑定到tempA*/
    decltype(refTempA) dclTempA = tempA;
    /*2.dclTempB为引用，必须绑定到变量，编译不过*/
//    decltype(refTempA) dclTempB = 0;
    /*3.dclTempC为引用，必须初始化，编译不过*/
//    decltype(refTempA) dclTempC;
    /*4.双层括号表示引用，dclTempD为引用，绑定到tempA*/
    decltype((tempA)) dclTempD = tempA;

    const int ctempA = 1, &crefTempA = ctempA;

    /*5.dclTempE为常量引用，可以绑定到普通变量tempA*/
    decltype(crefTempA) dclTempE = tempA;
    /*6.dclTempF为常量引用，可以绑定到常量ctempA*/
    decltype(crefTempA) dclTempF = ctempA;
    /*7.dclTempG为常量引用，绑定到一个临时变量*/
    decltype(crefTempA) dclTempG = 0;
    /*8.dclTempH为常量引用，必须初始化，编译不过*/
//    decltype(crefTempA) dclTempH;
    /*9.双层括号表示引用,dclTempI为常量引用，可以绑定到普通变量tempA*/
    decltype((ctempA))  dclTempI = ctempA;
}

void test4()
{
    int tempA = 2;
    int *ptrTempA = &tempA;
    /*1.常规使用dclTempA为一个int *的指针*/
    decltype(ptrTempA) dclTempA;
    /*2.需要特别注意，表达式内容为解引用操作，dclTempB为一个引用，引用必须初始化，故编译不过*/
//    decltype(*ptrTempA) dclTempB;
}

int main(int argc, char** argv)
{
    test1();
    test2();
    test3();
    test4();
    test_decltype1();
    test_decltype2();
    return 0;
}