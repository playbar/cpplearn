#include "FactoryMethod.hpp"
#include "factory.hpp"
#include "product_2.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/21876069



Product::Product()
{

}

Product::~Product()
{

}

ConcreteProduct::ConcreteProduct()
{
	cout<<"ConcreteProduct ..."<<endl;
}

ConcreteProduct::~ConcreteProduct()
{

}

Factory::Factory()
{

}

Factory::~Factory()
{

}

ConcreteFactory::ConcreteFactory()
{
	cout<<"ConcreteFactory ..."<<endl;
}

ConcreteFactory::~ConcreteFactory()
{

}

Product* ConcreteFactory::CreateProduct()
{
	return new ConcreteProduct();
}


int test_FactoryMethod1()
{
	LeiFangFactory* sf = new LeiFangFactory();
	LeiFeng *s = sf->CreateLeiFeng();
	s->Sweep();

	delete s;
	delete sf;

	/*result:
	�׷�ɨ��
	*/

	return 0;
}

int test_FactoryMethod2()
{
	Factory* fac = new ConcreteFactory();
	Product_2* p = fac->CreateProduct();

	/*result:
		ConcreteFactory ...
		ConcreteProduct ...
	*/

	return 0;
}
