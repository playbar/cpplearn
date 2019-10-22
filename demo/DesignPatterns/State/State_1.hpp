#ifndef FBC_MESSY_TEST_STATE1_HPP_
#define FBC_MESSY_TEST_STATE_HPP_

class StateContext;

class State_3
{
public:
	State_3();
	virtual ~State_3();
	virtual void OperationInterface(StateContext*) = 0;
	virtual void OperationChangeState(StateContext*) = 0;
protected:
	bool ChangeState(StateContext* con, State_3* st);
};

class ConcreteStateA_3 : public State_3
{
public:
	ConcreteStateA_3();
	virtual ~ConcreteStateA_3();
	virtual void OperationInterface(StateContext*);
	virtual void OperationChangeState(StateContext*);
protected:
private:
};

class ConcreteStateB_3 : public State_3
{
public:
	ConcreteStateB_3();
	virtual ~ConcreteStateB_3();
	virtual void OperationInterface(StateContext*);
	virtual void OperationChangeState(StateContext*);
protected:
private:
};

#endif // FBC_MESSY_TEST_STATE_HPP_