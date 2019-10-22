#include "Command.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/36221901

Receiver::Receiver()
{

}

Receiver::~Receiver()
{

}

void Receiver::Action()
{
	std::cout<<"Receiver action ..."<<std::endl;
}


Command_1::Command_1()
{

}

Command_1::~Command_1()
{

}

void Command_1::Excute()
{

}

ConcreteCommand::ConcreteCommand(Receiver* rev)
{
	this->_rev = rev;
}

ConcreteCommand::~ConcreteCommand()
{
	delete this->_rev;
}

void ConcreteCommand::Excute()
{
	_rev->Action();
	std::cout << "ConcreteCommand ..." << std::endl;
}

Invoker::Invoker(Command_1* cmd)
{
	_cmd = cmd;
}

Invoker::~Invoker()
{
	delete _cmd;
}

void Invoker::Invoke()
{
	_cmd->Excute();
}

int test_Command1()
{
	//店里添加烤肉师傅、菜单、服务员等顾客
	Barbucer* barbucer = new Barbucer();
	Command* cmd = new BakeMuttonCmd(barbucer);
	Command* cmd2 = new ChickenWingCmd(barbucer);
	Waiter* girl = new Waiter();

	//点菜
	girl->SetCmd(cmd);
	girl->SetCmd(cmd2);

	//服务员通知
	girl->Notify();

	/*result
		增加定单
		增加定单
		烤羊肉
		烤鸡翅膀
	*/

	return 0;
}

int test_Command2()
{
	Receiver* rev = new Receiver();
	Command_1* cmd = new ConcreteCommand(rev);
	Invoker* inv = new Invoker(cmd);
	inv->Invoke();

	/*result
		Receiver action ...
		ConcreteCommand ...
	*/

	return 0;
}
