#ifndef FBC_MESSY_TEST_FACTORY_METHOD_HPP_
#define FBC_MESSY_TEST_FACTORY_METHOD_HPP_

#include <iostream>

//实例基类，相当于Product（为了方便，没用抽象）
class LeiFeng
{
public:
	virtual void Sweep()
	{
		std::cout << "雷锋扫地" << std::endl;
	}
};

//学雷锋的大学生相当于ConcreteProduct
class Student : public LeiFeng
{
public:
	virtual void Sweep()
	{
		std::cout << "大学生扫地" << std::endl;
	}
};

//学雷锋的志愿者，相当于ConcreteProduct
class Volenter : public LeiFeng
{
public:
	virtual void Sweep()
	{
		std::cout << "志愿者扫地" << std::endl;
	}
};

//工厂基类 Creator
class LeiFangFactory
{
public:
	virtual LeiFeng* CreateLeiFeng()
	{
		return new LeiFeng();
	}
};

//工厂具体类
class StudentFactory : public LeiFangFactory
{
public:
	virtual LeiFeng* CreateLeiFeng()
	{
		return new Student();
	}
};

class VolenterFactory : public LeiFangFactory
{
public:
	virtual LeiFeng* CreateLeiFeng()
	{
		return new Volenter();
	}
};


////////////////




class Product
{
public:
	virtual ~Product() = 0;
protected:
	Product();
private:
};

class ConcreteProduct : public Product
{
public:
	~ConcreteProduct();
	ConcreteProduct();

protected:
private:
};



class Factory
{
public:
	virtual ~Factory() = 0;
	virtual Product* CreateProduct() = 0;
protected:
	Factory();
private:
};

class ConcreteFactory : public Factory
{
public:
	~ConcreteFactory();
	ConcreteFactory();
	Product* CreateProduct();
protected:
private:
};


int test_FactoryMethod1();
int test_FactoryMethod2();

#endif // FBC_MESSY_TEST_FACTORY_METHOD_HPP_
