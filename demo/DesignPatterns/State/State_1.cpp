#include <iostream>

#include "State_1.hpp"
#include "StateContext.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/33385599

State_3::State_3()
{

}

State_3::~State_3()
{

}

void State_3::OperationInterface(StateContext* con)
{
	std::cout<<"State:: ..."<<std::endl;
}

bool State_3::ChangeState(StateContext* con, State_3* st)
{
	con->ChangeState(st);
	return true;
}

void State_3::OperationChangeState(StateContext* con)
{

}

ConcreteStateA_3::ConcreteStateA_3()
{

}

ConcreteStateA_3::~ConcreteStateA_3()
{

}

void ConcreteStateA_3::OperationInterface(StateContext* con)
{
	std::cout<<"ConcreteStateA::OperationInterface ..."<<std::endl;
}

void ConcreteStateA_3::OperationChangeState(StateContext* con)
{
	OperationInterface(con);
	this->ChangeState(con, new ConcreteStateB_3());
}

ConcreteStateB_3::ConcreteStateB_3()
{

}

ConcreteStateB_3::~ConcreteStateB_3()
{

}

void ConcreteStateB_3::OperationInterface(StateContext* con)
{
	std::cout<<"ConcreteStateB::OperationInterface ..."<<std::endl;
}

void ConcreteStateB_3::OperationChangeState(StateContext* con)
{
	OperationInterface(con);
	this->ChangeState(con, new ConcreteStateA_3());
}