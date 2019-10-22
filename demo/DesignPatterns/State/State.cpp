#include "State.hpp"
#include "State_1.hpp"
#include "StateContext.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/33385599

Work::Work()
{
	current = new ForenoonState();
}

int test_State1()
{
	Work* mywork = new Work();
	mywork->hour = 9;
	mywork->Writeprogram();
	mywork->hour = 14;
	mywork->Writeprogram();

	/*result
		现在的精神无敌好
		execute
		不行了，还是睡觉吧
	*/

	return 0;
}

int test_State2()
{
	State_3* st = new ConcreteStateA_3();
	StateContext* con = new StateContext(st);
	con->OperationChangeState();
	con->OperationChangeState();
	con->OperationChangeState();

	if (con != NULL)
		delete con;

	if (st != NULL)
		st = NULL;

	/*result
		ConcreteStateA::OperationInterface ...
		ConcreteStateB::OperationInterface ...
		ConcreteStateA::OperationInterface ...
	*/

	return 0;
}
