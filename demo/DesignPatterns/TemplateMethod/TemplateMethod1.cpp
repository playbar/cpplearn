#include <iostream>

using namespace std;

class Library
{

public:
	void Step1()
	{
		cout << "Step1" << endl;
	}

	void Step3()
	{
		cout << "Step3" << endl;
	}

	void Step5()
	{
		cout << "Step5" << endl;
	}
};

class Application
{
  public:
	bool Step2()
	{
		cout << "myStep2" << endl;
		return true;
	}

	void Step4()
	{
		cout << "myStep4" << endl;
	}
};

int test_TemplateMethod3()
{
	Library lib;
	Application app;

	lib.Step1();

	if (app.Step2())
	{
		lib.Step3();
	}

	for (int i = 0; i < 4; i++)
	{
		app.Step4();
	}

	lib.Step5();
	return 0;
}
