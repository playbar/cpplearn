#ifndef FBC_MESSY_TEST_SET_HPP_
#define FBC_MESSY_TEST_SET_HPP_

int test_set_cplusplus();
int test_set_cppreference();


class TestA
{
public:
    int ma;

    TestA(){
        ma = 10;
    }
    ~TestA(){
        ma = 0;
    }
};

#endif // FBC_MESSY_TEST_SET_HPP_
