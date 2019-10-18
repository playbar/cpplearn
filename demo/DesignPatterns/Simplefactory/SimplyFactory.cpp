#include "SimplyFactory.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/24872725

int test_SimplyFactory1()
{
	//CCalculatorFactory* calFactory = new CCalculatorFactory();
	EnProductType type = NONE;
	double a = 10, b = 2;

	type = ADD;
	//COperation* operation = calFactory->CreateOperation(type, a, b);
	COperation* operation = CCalculatorFactory::CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = SUB;
	//operation = calFactory->CreateOperation(type, a, b);
	operation = CCalculatorFactory::CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = MUL;
	//operation = calFactory->CreateOperation(type, a, b);
	operation = CCalculatorFactory::CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = DIV;
	//operation = calFactory->CreateOperation(type, a, b);
	operation = CCalculatorFactory::CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	/*if (calFactory) {
	delete calFactory;
	calFactory = NULL;
	}*/

	/*result
		COperation constructor
		CAddOperation constructor
		12
		CAddOperation destructor
		COperation destructor
		COperation constructor
		CSubOperation constructor
		8
		CSubOperation destructor
		COperation destructor
		COperation constructor
		CMulOperation constructor
		20
		CMulOperation destructor
		COperation destructor
		COperation constructor
		CDivOperation constructor
		5
		CDivOperation destructor
		COperation destructor
	*/

	return 0;
}

int test_SimplyFactory2()
{
	CCalculatorFactory* calFactory = new CCalculatorFactory();
	EnProductType type = NONE;
	double a = 10, b = 2;

	type = ADD;
	COperation* operation = calFactory->CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = SUB;
	operation = calFactory->CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = MUL;
	operation = calFactory->CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	type = DIV;
	operation = calFactory->CreateOperation(type, a, b);
	if (operation) {
		std::cout << operation->GetResult() << std::endl;
		delete operation;
		operation = NULL;
	}

	if (calFactory) {
		delete calFactory;
		calFactory = NULL;
	}

	return 0;
}
