#include "StateContext.hpp"
#include "State_1.hpp"

StateContext::StateContext()
{

}

StateContext::StateContext(State_3* state)
{
	this->_state = state;
}

StateContext::~StateContext()
{
	delete _state;
}

void StateContext::OperationInterface()
{
	_state->OperationInterface(this);
}

bool StateContext::ChangeState(State_3* state)
{
	//_state->ChangeState(this, state);
	this->_state = state;

	return true;
}

void StateContext::OperationChangeState()
{
	_state->OperationChangeState(this);
}