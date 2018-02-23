#ifndef FBC_MESSY_TEST_UNORDERED_MAP_HPP_
#define FBC_MESSY_TEST_UNORDERED_MAP_HPP_

#include "string"
using namespace std;

struct person
{
    string name;
    int age;

    person(string name, int age)
    {
        this->name =  name;
        this->age = age;
    }

    bool operator== (const person& p) const
    {
        return name==p.name && age==p.age;
    }
};

#ifdef __cplusplus
extern "C" {
#endif

int test_unordered_map1();
int test_unordered_map2();
int test_unordered_map3();
int test_unordered_map4();
//size_t hash(const person& p);

#ifdef __cplusplus
}
#endif




#endif // FBC_MESSY_TEST_UNORDERED_MAP_HPP_
