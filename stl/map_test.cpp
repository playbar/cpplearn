//
// Created by mac on 2019-05-12.
//

#include "map"
#include <iostream>
using namespace std;

void map_swap_test()
{
    map <int, int> m1, m2, m3;
    map <int, int>::iterator m1_Iter;
    m1.insert ( pair <int, int> ( 1, 10 ) );
    m1.insert ( pair <int, int> ( 2, 20 ) );
    m1.insert ( pair <int, int> ( 3, 30 ) );
    m2.insert ( pair <int, int> ( 10, 100 ) );
    m2.insert ( pair <int, int> ( 20, 200 ) );
    m3.insert ( pair <int, int> ( 30, 300 ) );
    cout << "The original map m1 is:";
    for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
        cout << " " << m1_Iter->second;
    cout << "." << endl;
// This is the member function version of swap
//m2 is said to be the argument map; m1 the target map
    m1.swap( m2 );
    cout << "After swapping with m2, map m1 is:";
    for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
        cout << " " << m1_Iter -> second;
    cout << "." << endl;
    cout << "After swapping with m2, map m2 is:";
    for ( m1_Iter = m2.begin( ); m1_Iter != m2.end( ); m1_Iter++ )
        cout << " " << m1_Iter -> second;
    cout << "." << endl;
// This is the specialized template version of swap
    swap( m1, m3 );
    cout << "After swapping with m3, map m1 is:";
    for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
        cout << " " << m1_Iter -> second;
    cout << "." << endl;
}

void main_sort_test()
{
    map <int, int> m1;
    map <int, int>::iterator m1_Iter;
    m1.insert ( pair <int, int> ( 1, 20 ) );
    m1.insert ( pair <int, int> ( 4, 40 ) );
    m1.insert ( pair <int, int> ( 3, 60 ) );
    m1.insert ( pair <int, int> ( 2, 50 ) );
    m1.insert ( pair <int, int> ( 6, 40 ) );
    m1.insert ( pair <int, int> ( 7, 30 ) );
    cout << "The original map m1 is:"<<endl;
    for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
        cout << m1_Iter->first<<" "<<m1_Iter->second<<endl;
}

void map_test()
{
    multimap<string,string,less<string> >mulmap;
    multimap<string,string,less<string> >::iterator p;
//初始化多重映射mulmap:
    typedef multimap<string,string,less<string> >::value_type vt;
    typedef string s;
    mulmap.insert(vt(s("Tom "),s("is a student")));
    mulmap.insert(vt(s("Tom "),s("is a boy")));
    mulmap.insert(vt(s("Tom "),s("is a bad boy of blue!")));
    mulmap.insert(vt(s("Jerry "),s("is a student")));
    mulmap.insert(vt(s("Jerry "),s("is a beatutiful girl")));
    mulmap.insert(vt(s("DJ "),s("is a student")));
//输出初始化以后的多重映射mulmap:
    for(p=mulmap.begin();p!=mulmap.end();++p)
        cout<<(*p).first<<(*p).second<<endl;
//检索并输出Jerry键所对应的所有的值
    cout<<"find Jerry :"<<endl;
    p=mulmap.find(s("Jerry "));
    while((*p).first=="Jerry ")
    {
        cout<<(*p).first<<(*p).second<<endl;
        ++p;
    }
    cin.get();

}

int main( )
{
    map_swap_test();
    main_sort_test();
    map_test();
}

