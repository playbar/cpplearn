#ifndef FBC_MESSY_TEST_DECORATOR_HPP_
#define FBC_MESSY_TEST_DECORATOR_HPP_

#include <string>
#include <vector>
#include <iostream>

//��
class Person_1
{
private:
	std::string m_strName;
public:
	Person_1(std::string strName)
	{
		m_strName = strName;
	}

	Person_1() {}

	virtual void Show()
	{
		std::cout << "Person_1" << m_strName << std::endl;
	}
};

//װ����
class Finery : public Person_1
{
protected:
	Person_1* m_Component_2;
public:
	void Decorate(Person_1* Component_2)
	{
		m_Component_2 = Component_2;
	}

	virtual void Show()
	{
		m_Component_2->Show();
	}
};

//T��
class TShirts : public Finery
{
public:
	virtual void Show()
	{
		std::cout << "T Shirts" << std::endl;
		m_Component_2->Show();
	}
};

//����
class BigTrouser : public Finery
{
public:
	virtual void Show()
	{
		std::cout << "Big Trouser" << std::endl;
		m_Component_2->Show();
	}
};

// ===============================================================
class Component_2
{
public:
	virtual ~Component_2();
	virtual void Operation();
protected:
	Component_2();
private:
};

class ConcreteComponent_2 : public Component_2
{
public:
	ConcreteComponent_2();
	~ConcreteComponent_2();
	void Operation();
protected:
private:
};

class Decorator : public Component_2
{
public:
	Decorator(Component_2* com);
	virtual ~Decorator();
	void Operation();
protected:
	Component_2* _com;
private:
};

class ConcreteDecorator : public Decorator
{
public:
	ConcreteDecorator(Component_2* com);
	~ConcreteDecorator();
	void Operation();
	void AddedBehavior();
protected:
private:
};


int test_Decorator1();
int test_Decorator2();

#endif // FBC_MESSY_TEST_DECORATOR_HPP_
