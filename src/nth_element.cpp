//
// Created by hou guoli on 2018/2/9.
//


#pragma warning(disable: 4786)

#include <cmath>
#include "iostream"
#include "algorithm"
#include "functional"
#include "vector"

using namespace std;


int main()

{

    const int VECTOR_SIZE = 50 ;



    vector<int> Numbers(VECTOR_SIZE) ;



    vector<int>::iterator start, end, it ;



    // Initialize vector Numbers

    for(int i=0;i<50;++i){

        Numbers[i]=i;

    }

/*由于赋值时是有序的，下面random_shuffle()方法将这些数据的顺序打乱*/

    random_shuffle(Numbers.begin(),Numbers.end());



// location of first element of Numbers

    start = Numbers.begin() ;



    // one past the location last element of Numbers

    end = Numbers.end() ;



    cout << "Before calling nth_element/n" << endl ;



    // print content of Numbers

    cout << "Numbers { " ;

    for(it = start; it != end; it++)

        cout << *it << " " ;

    cout << " }/n" << endl ;



    /*

      * partition the elements by the 8th element，

    *（notice that 0th is the first element）

    */

    nth_element(start, start+8, end, [](const int &a, const int &b)
    {
        return fabs(a) > fabs(b);
    }) ;



    cout << "After calling nth_element/n" << endl ;



    cout << "Numbers { " ;

    for(it = start; it != end; it++)

        cout << *it << " " ;

    cout << " }/n" << endl ;

    system("pause");

}