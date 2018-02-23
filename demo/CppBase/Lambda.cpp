#include "Lambda.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52653313

/*
[]		Capture nothing (or, a scorched earth strategy?)
[&]		Capture any referenced variable by reference
[=]		Capture any referenced variable by making a copy
[=, &foo]	Capture any referenced variable by making a copy, but capture variable foo by reference
[bar]		Capture bar by making a copy; don't copy anything else
[this]		Capture the this pointer of the enclosing class

1).[]不捕获任何变量。
2).[&]捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。
3).[=]捕获外部作用域中所有变量，并作为副本在函数体中使用(按值捕获)。
4).[=,&foo]按值捕获外部作用域中所有变量，并按引用捕获foo变量。
5).[bar]按值捕获bar变量，同时不捕获其他变量。
6).[this]捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。
如果已经使用了&或者=，就默认添加此选项。捕获this的目的是可以在lamda中使用当前类的成员函数和成员变量。

 lambda表达式的语法归纳如下：
[ caputrue ] ( params ) opt -> ret { body; };
1).capture是捕获列表；
2).params是参数表；(选填)
3).opt是函数选项；可以填mutable,exception,attribute（选填）
mutable说明lambda表达式体内的代码可以修改被捕获的变量，并且可以访问被捕获的对象的non-const方法。
exception说明lambda表达式是否抛出异常以及何种异常。
attribute用来声明属性。
4).ret是返回值类型。(选填)
5).body是函数体。
*/

///////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/lambda
int test_lambda1()
{

	int a = 1, b = 1, c = 1;

	auto m1 = [a, &b, &c]() mutable
    {
        std::cout << a << b << c << '\n';
		auto m2 = [a, b, &c]() mutable
        {
			std::cout << a << b << c << '\n';
			a = 4; b = 4; c = 4;
		};
		a = 3; b = 3; c = 3;
		m2();
	};

	a = 2; b = 2; c = 2;

	m1();// calls m2() and prints 123

	std::cout << a << b << c << '\n'; // prints 234

	return 0;
}

///////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/lambda
int test_lambda2()
{
	std::vector<int> c = { 1, 2, 3, 4, 5, 6, 7 };
	int x = 5;
	c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());

	std::cout << "c: ";
	std::for_each(c.begin(), c.end(), [](int i){ std::cout << i << ' '; });
	std::cout << '\n';

	// the type of a closure cannot be named, but can be inferred with auto
	auto func1 = [](int i) { return i + 4; };
	std::cout << "func1: " << func1(6) << '\n';

	// like all callable objects, closures can be captured in std::function
	// (this may incur unnecessary overhead)
	std::function<int(int)> func2 = [](int i) { return i + 4; };
	std::cout << "func2: " << func2(6) << '\n';

	return 0;
}

///////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd293608.aspx
int test_lambda3()
{
	// The following example contains a lambda expression that explicitly captures the variable n by value
	// and implicitly captures the variable m by reference:
	int m = 0;
	int n = 0;
	[&, n](int a) mutable {
		m = ++n + a;
		std::cout << m << ", " << n << std::endl;
	}(4);

	// Because the variable n is captured by value, its value remains 0 after the call to the lambda expression.
	// The mutable specification allows n to be modified within the lambda.
	std::cout << m << ", " << n << std::endl;

	return 0;
}

//////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd293608.aspx
template <typename C>
void print(const std::string& s, const C& c)
{
	std::cout << s;

	for (const auto& e : c) {
		std::cout << e << " ";
	}

	std::cout << std::endl;
}

void fillVector(std::vector<int>& v)
{
	// A local static variable.
	static int nextValue = 1;

	// The lambda expression that appears in the following call to
	// the generate function modifies and uses the local static 
	// variable nextValue.
	generate(v.begin(), v.end(), [] { return nextValue++; });
	//WARNING: this is not thread-safe and is shown for illustration only
}

int test_lambda4()
{
	// The number of elements in the vector.
	const int elementCount = 9;

	// Create a vector object with each element set to 1.
	std::vector<int> v(elementCount, 1);

	// These variables hold the previous two elements of the vector.
	int x = 1;
	int y = 1;

	// Sets each element in the vector to the sum of the 
	// previous two elements.
	generate_n(v.begin() + 2,
		elementCount - 2,
		[=]() mutable throw() -> int { // lambda is the 3rd parameter
		// Generate current value.
		int n = x + y;
		// Update previous two values.
		x = y;
		y = n;
		return n;
	});
	print("vector v after call to generate_n() with lambda: ", v);

	// Print the local variables x and y.
	// The values of x and y hold their initial values because 
	// they are captured by value.
	std::cout << "x: " << x << " y: " << y << std::endl;

	// Fill the vector with a sequence of numbers
	fillVector(v);
	print("vector v after 1st call to fillVector(): ", v);
	// Fill the vector with the next sequence of numbers
	fillVector(v);
	print("vector v after 2nd call to fillVector(): ", v);

	return 0;
}

/////////////////////////////////////////////////
// reference: http://blogorama.nerdworks.in/somenotesonc11lambdafunctions/

template<typename T>
std::function<T()> makeAccumulator(T& val, T by) {
	return [=, &val]() {
		return (val += by);
	};
}

int test_lambda5()
{
	int val = 10;
	auto add5 = makeAccumulator(val, 5);
	std::cout << add5() << std::endl;
	std::cout << add5() << std::endl;
	std::cout << add5() << std::endl;
	std::cout << std::endl;

	val = 100;
	auto add10 = makeAccumulator(val, 10);
	std::cout << add10() << std::endl;
	std::cout << add10() << std::endl;
	std::cout << add10() << std::endl;

	return 0;
}

////////////////////////////////////////////////////////
// reference: http://blogorama.nerdworks.in/somenotesonc11lambdafunctions/
class Foo_lambda {
public:
	Foo_lambda() {
		std::cout << "Foo_lambda::Foo_lambda()" << std::endl;
	}

	Foo_lambda(const Foo_lambda& f) {
		std::cout << "Foo_lambda::Foo_lambda(const Foo_lambda&)" << std::endl;
	}

	~Foo_lambda() {
		std::cout << "Foo_lambda~Foo_lambda()" << std::endl;
	}
};

int test_lambda6()
{
	Foo_lambda f;
	auto fn = [f]() { std::cout << "lambda" << std::endl; };
	std::cout << "Quitting." << std::endl;
	fn();
	return 0;
}

template<typename Cal>
static void display(Cal cal)
{
	fprintf(stderr, "start\n");
	cal();
}

int test_lambda7()
{
	int num { 1 };
	// create callback
	auto fun = [&](){
		if (num % 5 == 0) {
			fprintf(stderr, "****** reset ******\n");
			fprintf(stderr, "num = %d\n", num);

			num = 0;
		} else {
			fprintf(stderr, "++++++ continue ++++++\n");
			fprintf(stderr, "num = %d\n", num);
		}

		num++;
	};

	for (int i = 0; i < 20; i++) {
		fprintf(stderr, "========= i = %d\n", i);
		display(fun);
	}

	return 0;
}

class A
{
public:
    int i_ = 0;

    void func(int x,int y)
    {
//        auto x1 = [] { return i_; };                             //error,没有捕获外部变量
        auto x2 = [=] { return i_ + x + y; };               //OK
        auto x3 = [&] { return i_ + x + y; };               //OK
        auto x4 = [this] { return i_; };                        //OK
//        auto x5 = [this] { return i_ + x + y; };            //error,没有捕获x,y
        auto x6 = [this, x, y] { return i_ + x + y; };    //OK
        auto x7 = [this] { return i_++; };                   //OK
    };


};

void testCode()
{
    int a=0 , b=1;
//    auto f1 = [] { return a; };                        //error,没有捕获外部变量
    auto f2 = [&] { return a++; };                      //OK
    auto f3 = [=] { return a; };                         //OK
//    auto f4 = [=] {return a++; };                     //error,a是以复制方式捕获的，无法修改
//    auto f5 = [a] { return a+b; };                     //error,没有捕获变量b
    auto f6 = [a, &b] { return a + (b++); };      //OK
    auto f7 = [=, &b] { return a + (b++); };     //OK
}

void testCode1()
{
    int a = 0;
    auto f = [=] { return a; };
    a+=1;
    std::cout << f() << std::endl;       //输出0

    a = 0;
    auto ff = [&a] { return a; };
    a+=1;
    std::cout << ff() <<std::endl;       //输出1
}

void testCode2()
{
    int a = 0;
//    auto f1 = [=] { return a++; };                       //error
    auto f2 = [=] () mutable { return a++; };       //OK

    typedef void(*Ptr)(int*);

    Ptr p = [](int* p) { delete p; };              //OK
//    Ptr p1 = [&] (int* p) { delete p; };         //error
}

void testCode3()
{
    std::vector<int> coll = { 1, 2, 3, 4, 5, 6 };
    int even_count = 0;
    for_each(coll.begin(), coll.end(), [&even_count](int val){
        if(!(val & 1)){
            ++ even_count;
        }
    });
    std::cout << "The number of even is " << even_count << std::endl;

    int count = std::count_if( coll.begin(), coll.end(), [](int x){ return x > 10; });

    count = std::count_if( coll.begin(), coll.end(), [](int x){ return x < 10; });

    count = std::count_if( coll.begin(), coll.end(), [](int x){ return x > 5 && x<10; });


    std::cout << "The number of count is " << count << std::endl;

    return;
}


int main()
{
	test_lambda7();
}