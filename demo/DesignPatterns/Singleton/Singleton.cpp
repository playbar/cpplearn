#include <iostream>
#include "Singleton.hpp"
#include "singleton4.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/22584107

Singleton* Singleton::single = NULL;

Singleton_1::Singleton_1()
{
	std::cout << "Singleton ..." << std::endl;
}

Singleton_1* Singleton_1::Instance()
{
	static Singleton_1 state;
	return &state;
}

int test_Singleton1()
{
	Singleton* s1 = Singleton::GetInstance();
	Singleton* s2 = Singleton::GetInstance();

	if (s1 == s2)
		std::cout << "ok" << std::endl;
	else
		std::cout << "no" << std::endl;

	/*result:
		ok
	*/

	return 0;
}

int test_Singleton2()
{
	Singleton_1* sgn = Singleton_1::Instance();

	/*result:
		Singleton ...
	*/

	return 0;
}

// 线程函数
void *PrintHello(void *threadid)
{
	// 主线程与子线程分离，两者相互不干涉，子线程结束同时子线程的资源自动回收
	pthread_detach(pthread_self());

	// 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
	int tid = *((int *)threadid);

	std::cout << "Hi, 我是线程 ID:[" << tid << "]" << std::endl;

	// 打印实例地址
	SingleInstance::GetInstance()->Print();

	pthread_exit(NULL);
}


#define NUM_THREADS 5 // 线程个数

int test_Singleton3()
{
	pthread_t threads[NUM_THREADS] = {0};
	int indexes[NUM_THREADS] = {0}; // 用数组来保存i的值

	int ret = 0;
	int i = 0;

	std::cout << "开始 ... " << std::endl;

	for (i = 0; i < NUM_THREADS; i++)
	{
		std::cout << "创建线程:[" << i << "]" << std::endl;

		indexes[i] = i; //先保存i的值

		// 传入的时候必须强制转换为void* 类型，即无类型指针
		ret = pthread_create(&threads[i], NULL, PrintHello, (void *)&(indexes[i]));
		if (ret)
		{
			std::cout << "Error:无法创建线程," << ret << std::endl;
			return 0;
		}
	}

	// 手动释放单实例的资源
	SingleInstance::deleteInstance();
	std::cout << "结束! " << std::endl;

	return 0;
}