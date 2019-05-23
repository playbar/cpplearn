#ifndef FBC_MESSY_TEST_STATIC_CAST_HPP_
#define FBC_MESSY_TEST_STATIC_CAST_HPP_

#include <iostream>

// reference: https://msdn.microsoft.com/zh-cn/library/c36yw7x9.aspx
class B1 {
public:
	B1() { std::cout<<"B1" << std::endl; };
	virtual ~B1() {std::cout<<"~B1" << std::endl;};
	virtual void Test(){std::cout<<"B1 test, "<<mB1<<std::endl;}
    int mB1 = 1;
};

class C1 : public B1 {
public:
	C1(){std::cout << "C1" << std::endl; }
	virtual ~C1(){std::cout << "~C1" << std::endl; }
	virtual void Test(){ std::cout << "C1 test, "<< mC1 << std::endl;}
    int mC1 = 2;
};


class D1 : public B1 {
public:
	D1(){std::cout << "D1" << std::endl; }
	virtual ~D1(){std::cout << "~D1" << std::endl; }
	virtual void Test(){ std::cout << "D1 test, " << mD1<< std::endl;}
    int mD1 = 3;
};

class DD1 : public D1 {
public:
	DD1(){std::cout << "DD1" << std::endl; }
	virtual ~DD1(){std::cout << "~DD1" << std::endl; }
	virtual void Test(){ std::cout << "DD1 test, " << mDD1 << std::endl;}
    int mDD1 = 4;
};

class CCTest {
public:
	void setNumber(int);
	void printNumber() const;
private:
	int number;
};

class B2 { };
class C2 : public B2 { };
class D2 : public C2 { };

class A3 { virtual void f(); };
class B3 { virtual void f(); };

class B4 { virtual void f(); };
class D4 : public B4 { virtual void f(); };

// Returns a hash code based on an address
unsigned short Hash(void *p);

void test_static_cast1();
void test_static_cast2(B1* pb, D1* pd);
void test_static_cast3(B1* pb);
void test_static_cast4();
void test_static_cast5();
void test_static_cast6();
void test_static_cast7();
void test_static_cast8();
void test_static_cast9();
void test_static_cast10();
void test_static_cast11();

#endif // FBC_MESSY_TEST_STATIC_CAST_HPP_