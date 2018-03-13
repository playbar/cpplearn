//
// Created by hou guoli on 2018/3/13.
//

#include <iostream>
#include <type_traits>
#include <cstdint>

template< class T >
struct decay {
private:
    typedef typename std::remove_reference<T>::type U;
public:
    typedef typename std::conditional<
            std::is_array<U>::value,
            typename std::remove_extent<U>::type*,
            typename std::conditional<
                    std::is_function<U>::value,
                    typename std::add_pointer<U>::type,
                    typename std::remove_cv<U>::type
            >::type
    >::type type;
};


void print_separator()
{
    std::cout << "-----\n";
}

int test_1()
{
    std::cout << std::boolalpha;

    std::cout << std::is_same<int, int32_t>::value << '\n';   // true
    std::cout << std::is_same<int, int64_t>::value << '\n';   // false
    std::cout << std::is_same<float, int32_t>::value << '\n'; // false

    print_separator();

    std::cout << std::is_same<int, int>::value << "\n";          // true
    std::cout << std::is_same<int, unsigned int>::value << "\n"; // false
    std::cout << std::is_same<int, signed int>::value << "\n";   // true

    print_separator();

    // unlike other types 'char' is not 'unsigned' and not 'signed'
    std::cout << std::is_same<char, char>::value << "\n";          // true
    std::cout << std::is_same<char, unsigned char>::value << "\n"; // false
    std::cout << std::is_same<char, signed char>::value << "\n";   // false
    return 0;
}

/////////////////

typedef int integer_type;
struct A { int x,y; };
struct B { int x,y; };
typedef A C;

int test_2()
{
    A aa;
    B bb;
    C cc;
    std::cout << std::boolalpha;
    std::cout << "is_same:" << std::endl;
    std::cout << "int, const int: " << std::is_same<int, const int>::value << std::endl;//false
    std::cout << "int, int&: " << std::is_same<int, int&>::value << std::endl;//false
    std::cout << "int, const int&: " << std::is_same<int, const int&>::value << std::endl;//false
    std::cout << "int, integer_type: " << std::is_same<int, integer_type>::value << std::endl;//true
    std::cout << "A, B: " << std::is_same<A,B>::value << std::endl;//false
    std::cout << "A, C: " << std::is_same<A,C>::value << std::endl;//true
//    std::cout << "aa, bb: " << std::is_same<aa, bb>::value << std::endl;
    std::cout << "signed char, std::int8_t: " << std::is_same<signed char,std::int8_t>::value << std::endl;//true
    return 0;
}

///////////////////
template<typename TYPE>
void typeCheck(TYPE data)
{
    if(std::is_same<TYPE,int>::value)
    {
        std::cout<<"int type"<<std::endl;
    }
    else if(std::is_same<TYPE,std::string>::value)
    {
        std::cout<<"string type"<<std::endl;
    }
    else
    {
        std::cout<<"other type"<<std::endl;
    }
}

int test_3()
{
    int a = 1;
    const int& b = a;
    int& c = a;
    int d[12];
    const int& e = d[7];
    typeCheck(a);       //int type
    typeCheck(b);       //int type
    typeCheck(c);       //int type
    typeCheck(d[7]);    //int type
    typeCheck(e);       //int type
    typeCheck(8);       //int type
    system("pause");
    return 0;
}


int test_4()
{
    int a = 1;
    const int& b = a;
    int& c = a;
    int d[12];

    typeCheck<int>(a);        //int type
    typeCheck<const int&>(b);//other type
    typeCheck<int &>(c);        //other type
    typeCheck<const int&>(d[7]);//other type
    typeCheck(8);                //int type
    return 0;
}


/////////////////
template<typename TYPE>
void typeCheckDe(TYPE data)
{
    if(std::is_same<typename std::decay<TYPE>::type,int>::value)
    {
        std::cout<<"int type"<<std::endl;
    }
    else
    {
        std::cout<<"other type"<<std::endl;
    }
}

int test_5()
{
    int a = 1;
    const int& b = a;
    int& c = a;
    int d[12];

    typeCheckDe<int>(a);//int type
    typeCheckDe<const int&>(b);//int type
    typeCheckDe<int &>(c);//int type
    typeCheckDe<const int&>(d[7]);//int type
    typeCheckDe(8);//int type
    return 0;
}

///////////
template <typename T, typename U>
struct decay_equiv : std::is_same<typename std::decay<T>::type, U>::type
{};

int test_6()
{
    std::cout << std::boolalpha
              << decay_equiv<int, int>::value << '\n'
              << decay_equiv<int&, int>::value << '\n'
              << decay_equiv<int&&, int>::value << '\n'
              << decay_equiv<const int&, int>::value << '\n'
              << decay_equiv<int[2], int*>::value << '\n'
              << decay_equiv<int(int), int(*)(int)>::value << '\n';
    return 0;
}

int main()
{
    test_6();
    return 0;
}