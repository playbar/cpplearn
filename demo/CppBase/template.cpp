#include <iostream>
#include <string>
#include <stdexcept>
#include "template.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51339659

void test_template1()
{
	int a = 3, b = 7;
	float x = 3.0, y = 7.0;
	//Calling template function
	std::cout << maximum<int>(a, b) << std::endl; //输出 7
	std::cout << maximum(a, b) << std::endl; //自动补充类型声明,输出 7
	std::cout << maximum<double>(x, y) << std::endl; //输出 7
}

void test_template2()
{
	int i = 39;
	int j = 20;
	std::cout << "Max(i, j): " << Max(i, j) << std::endl;

	double f1 = 13.5;
	double f2 = 20.7;
	std::cout << "Max(f1, f2): " << Max(f1, f2) << std::endl;

	std::string s1 = "Hello";
	std::string s2 = "World";
	std::cout << "Max(s1, s2): " << Max(s1, s2) << std::endl;
}

void test_template3()
{
	try {
		Stack<int>         intStack;  // stack of ints 
		Stack<std::string> stringStack;    // stack of strings 

		// manipulate int stack 
		intStack.push(7);
		std::cout << intStack.top() << std::endl;

		// manipulate string stack 
		stringStack.push("hello");
		std::cout << stringStack.top() << std::endl;
		stringStack.pop();
		//stringStack.pop();
	} catch (std::exception const& ex) {
		std::cerr << "Exception: " << ex.what() << std::endl;
		return;
	}
}

void test_template4()
{
	pair <int> myints(100, 75);
	pair <float> myfloats(100.0, 75.0);

	std::cout << myints.module() << std::endl;
	std::cout << myfloats.module() << std::endl;
}

void test_template5()
{
	PrintType<int> type_int;
	std::cout << type_int.type()<<std::endl;

	PrintType<float> type_float;
	std::cout << type_float.type() << std::endl;

	PrintType<std::string> type_string;
	std::cout << type_string.type() << std::endl;
}

void test_template6()
{
	int ret = 0, a = 5, b = 7;
	ret = max_mum(a, b);
	std::cout << ret << std::endl;
}

void test_template7()
{
	A<int> a;
	a.f();
}

////////////////

void Printf(const char *s)
{
	while (*s)
	{
		if (*s == '%'&&*++s != '%')
		{
			throw ("invalid formatstring: missing arguments");
		}
		std::cout << *s++;
	}
}


template<typename T,typename...Args>
void Printf(const char * s, T value, Args... args)
{
	while (*s)
	{
		if (*s=='%'&&*++s!='%')
		{
			std::cout << value;
			return Printf(++s, args...);
		}
		std::cout << *s++;
	}

	throw ("extraarguments provided to Printf");

}

///////////////
double Sum(int count, ...)
{
	va_list ap;
	double sum = 0;

	va_start(ap, count);

	for (int i = 0; i < count; ++i)
	{
		double arg = va_arg(ap, double);
		sum += arg;
	}

	va_end(ap);

	return sum;
}

double Sum2()
{
	return 0;
}

template<typename T1, typename... T2> double Sum2(T1 p, T2... arg)
{
	double ret = p + Sum2(arg...);
	return ret;
}




template<typename... A> class BMW{};

template<typename Head, typename... Tail>
class BMW<Head, Tail...> : public BMW<Tail...>
{
public:
	BMW()
	{
		printf("type: %s\n", typeid(Head).name());
	}

	Head head;
};

template<> class BMW<>{};
BMW<int, char, float> car;

int main()
{
	double ret1 = Sum(4, 1.0, 2.0, 3.0, 4.0);
	double ret2 = Sum2(1.0, 2.0, 3.0, 4.0);

	Printf<std::string>("hello %s\n", std::string("world"));
	return 0;
}

///////////////
