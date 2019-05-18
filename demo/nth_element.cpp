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

struct President
{
    std::string name;
    std::string country;
    int year;

    President(std::string && p_name, std::string && p_country, int p_year)
            : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(President&& other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};

int main_3()
{
    std::vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);

    std::vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "\nContents:\n";
    for (President const& president : elections) {
        std::cout << president.name << " was elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
    for (President const& president : reElections) {
        std::cout << president.name << " was re-elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
}



int main_2()
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
    end = Numbers.end() ;
    cout << "Before calling nth_element/n" << endl ;
    cout << "Numbers { " ;
    for(it = start; it != end; it++) {
        cout << *it << " ";
    }
    cout << " }/n" << endl ;

    nth_element(start, start+8, end, [](const int &a, const int &b)
    {
        return fabs(a) > fabs(b);
    }) ;

    cout << "After calling nth_element/n" << endl ;
    cout << "Numbers { " ;
    for(it = start; it != end; it++) {
        cout << *it << " ";
    }
    cout << " }/n" << endl ;
    system("pause");

}