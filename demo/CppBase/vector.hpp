#ifndef FBC_MESSY_TEST_VECTOR_HPP
#define FBC_MESSY_TEST_VECTOR_HPP

int test_vector_init();
int test_vector_access();
int test_vector_operation();
int test_vector_two_dimension();

class Vec5f
{
public:
    Vec5f(){
        std::cout<<"vec5f construct default" << std::endl;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        e = 0;
    }
    Vec5f(float _a, float _b, float _c, float _d, float _e)
            :a(_a), b(_b), c(_c), d(_d), e(_e){
        std::cout<<"vec5f construct" << std::endl;
    }
    float a;
    float b;
    float c;
    float d;
    float e;
};


#endif // FBC_MESSY_TEST_VECTOR_HPP
