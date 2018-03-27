//
// Created by hou guoli on 2018/3/27.
//

//template <typename T>
//void swap(T &a, T &b)
//{
//    T temp;
//    temp = a;
//    a = b;
//    b = temp;
//}

//template void swap<int>(int, int); // explicit instrantiation

//template <> void swap<int> (int &, int &);     //explicit specialization
//template <> void swap (int &, int &);     //explicit specialization


//struct job {};
//
//template<typename T>
//void swap(T &, T &);     // template prototype 模板
//
//template<>
//void swap<job>(job &, job &);     // explicit specialization for job 模板具体化
//
//int main()
//{
////    short a, b;
////    swap(a, b); // T 为 short 类型
////    int c, d;
////    swap(c, d); // T 为 int 类型
//
//    template void swap<char>(char &, char &);          // explicit instrantiation for char 模板 显式实例化
//
//    short a, b;
//    swap(a, b);     //implicit template instantiation for short(启用一个模板)
//
//    job n, m;
//    swap(n, m);  // use explicit specialization for job(模板具体化，不启用模板)
//
//    char g, h;
//    swap(g, h);  // use explicit template instantiation for char(启用另一个模板)
//
//    return 0;
//}


// ------------------------------------------------------------------------------
/*** 以下代码参考了 luaTinker 中 关于模板的使用 **/
#include <iostream>
using namespace std;

// "if_<bool, A, B>":类型选择模板(使用模板来实现,根据参数不同匹配不同的模板)
template<bool C, typename A, typename B> struct if_ {};
// 模板具体化(相对于一般模板，有更高的优先调用级；如果和具体化模板匹配，则调用具体化模板)
// 模板的部分具体化(模板的参数依然是三个，只不过第一个参数被默认指定而已)
template<typename A, typename B>         struct if_<true, A, B> {typedef A type;};    // first place
template<typename A, typename B>         struct if_<false, A, B> {typedef B type;};    // second place

int main_1()
{
    if_<true, char, double>::type bb; // 直接匹配 first place 位置部分具体化模板函数
    cout << " the sizeof(bb) is = " << sizeof(bb) << endl;
    if_<false, char, double>::type cc; // 直接匹配 second place 位置部分具体化模板函数
    cout << " the sizeof(cc) is = " << sizeof(cc) << endl;
    /*下面使用两个参数会报 参数不匹配 错误
     *    if_<char, int>::type dd;
     *     cout << " the sizeof(dd) is = " << sizeof(dd) << endl;
     */

    tuple<int, char, string> tupInfo(10, 'A', "hello world");
//    int a = tupInfo.head();
//    int a2 = tupInfo.tail().head();
//    tuple<char, string> tupTail = tupInfo.tail();
    int b = get<0>(tupInfo);
    char c = get<1>(tupInfo);
    string s = get<2>(tupInfo);
    auto tupInfo2 = make_tuple(5, 'B', string("C++ 11"), 4.6);

    return 0;
}

///////////////

template<typename T>
void Print(T value)
{
    cout << value << endl;
}

template<typename Head, typename... Rail>
void Print(Head head, Rail... rail)
{
    cout << head << ",";
    Print(rail...); // 递归调用可变参数模板
}

int main_2(int argc, char *argv[])
{
    Print(1);                  // 输出：1
    Print(1, "hello");         // 输出：1,Hello
    Print(1, "hello", 'H');    // 输出：1,Hello,H
    return 0;
}


///////////////


#include<iostream>
using std::cout;
using std::endl;

template<typename T>
class ManyFriend
{
private:
    T item;
public:
    ManyFriend(const T & i) : item(i) {}
    template<typename C, typename D> friend void show2(C & c, D & d);
};

template <typename C, typename D> void show2(C & c, D & d)
{
    cout << c.item << " , " << d.item << endl;
}

int main()
{
    ManyFriend<int> hfi1(10);
    ManyFriend<int> hfi2(20);
    ManyFriend<double> hfdb(10.5);
    cout  << "hfi1, hfi2 : ";
    show2(hfi1, hfi2);
    cout << "hfdb, hfi2 : ";
    show2(hfdb, hfi2);

    return 0;
}


// output

