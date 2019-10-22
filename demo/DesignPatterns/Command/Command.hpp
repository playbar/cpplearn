#ifndef FBC_MESSY_TEST_COMMAND_HPP_
#define FBC_MESSY_TEST_COMMAND_HPP_

#include <iostream>
#include <vector>

//¿¾ÈâÊ¦¸µ
class Barbucer
{
public:
	void MakeMutton()
	{
		std::cout << "烤羊肉" << std::endl;
	}

	void MakeChickenWing()
	{
		std::cout << "烤鸡翅膀" << std::endl;
	}
};

//³éÏóÃüÁîÀà
class Command {
protected:
	Barbucer* receiver;
public:
	Command(Barbucer* temp)
	{
		receiver = temp;
	}

	virtual void ExecuteCmd() = 0;
};

//¿¾ÑòÈâÃüÁî
class BakeMuttonCmd : public Command
{
public:
	BakeMuttonCmd(Barbucer* temp) : Command(temp) {}
	virtual void ExecuteCmd()
	{
		receiver->MakeMutton();
	}
};

//¿¾¼¦³á
class ChickenWingCmd : public Command
{
public:
	ChickenWingCmd(Barbucer* temp) : Command(temp) {}

	virtual void ExecuteCmd()
	{
		receiver->MakeChickenWing();
	}
};

//·þÎñÔ±Àà
class Waiter
{
protected:
	std::vector<Command*> m_commandList;
public:
	void SetCmd(Command* temp)
	{
		m_commandList.push_back(temp);
		std::cout << "set command" << std::endl;
	}

	//Í¨ÖªÖ´ÐÐ
	void Notify()
	{
		std::vector<Command*>::iterator p = m_commandList.begin();

		while (p != m_commandList.end()) {
			(*p)->ExecuteCmd();
			p++;
		}
	}
};

// =================================================

class Receiver
{
public:
	Receiver();
	~Receiver();
	void Action();
protected:
private:
};

class Command_1
{
public:
	virtual ~Command_1();
	virtual void Excute() = 0;
protected:
	Command_1();
private:
};

class ConcreteCommand : public Command_1
{
public:
	ConcreteCommand(Receiver* rev);
	~ConcreteCommand();
	void Excute();
protected:
private:
	Receiver* _rev;
};

class Invoker
{
public:
	Invoker(Command_1* cmd);
	~Invoker();
	void Invoke();
protected:
private:
	Command_1* _cmd;
};


int test_Command1();
int test_Command2();


#endif // FBC_MESSY_TEST_COMMAND_HPP_
