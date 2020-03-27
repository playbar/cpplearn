#include "memory_trace.hpp"

class student
{
public:
	student(void)
		: name("")
		, age(-1)
		, sex(-1)
	{
		printf("student(void) be called!\n");
	}

	student(std::string &_name, int _age, int _sex)
		: name(_name)
		, age(_age)
		, sex(_sex)
	{
		printf("student(std::string &_name, int _age, int _sex) be called!\n");
	}

	~student(void)
	{
		printf("~student(void) be called!\n");
	}

	void print(void)
	{
		printf("student : %s, %d, %d\n", name.c_str(), age, sex);
	}


private:
	std::string name;
	int age;
	int sex;
};

void MemoryTraceTest(void)
{
	//测试alloc
	//1.正常释放
	char *str0_alloc = (char *)malloc(13);
	sprintf(str0_alloc, "hello world\n");
	free(str0_alloc);
#ifdef _MEMORY_TRACE
	//2.无效地址
	int int_alloc = 10;
	char *str1_alloc = (char *)&int_alloc;
	free(str1_alloc);
	//3.double free
	free(str0_alloc);
	//4.交叉释放
	char *str2_alloc = (char *)malloc(2);
	delete(str2_alloc);
	delete_array(str2_alloc);
	//5.内存泄漏 str2_alloc指向的内存将被泄漏
	//str2_alloc没有释放，泄漏
#endif

	//测试new
	//1.正常释放
	std::string name("lily");
	student *stdnt1 = new student(name, 29, 0);
	delete(stdnt1);
#ifdef _MEMORY_TRACE
	//2.无效地址
	student stdnt;
	student *stdnt2 = &stdnt;
	delete(stdnt2);
	//3.double free
	delete(stdnt1);
	//4.交叉释放
	student *stdnt3 = new student(name, 29, 0);
	free(stdnt3);
	delete_array(stdnt3);
	//5.内存泄漏,stdnt3指向的内存将被泄漏
	//stdnt3没有释放，泄漏
#endif

	//测试new[]
	//1.正常释放
	int *int0_ptr = new int[3];
	int0_ptr[0] = 1;
	int0_ptr[1] = 2;
	int0_ptr[2] = 3;
	delete_array(int0_ptr);
#ifdef _MEMORY_TRACE
	//2.无效地址
	int arr[3]{ 1,2,3 };
	int *int1_ptr = arr;
	delete_array(int1_ptr);
	//3.double free
	delete_array(int0_ptr);
	//4.交叉释放
	int *int2_ptr = new int[1]{ 1 };
	free(int2_ptr);
	delete(int2_ptr);
	//5.内存泄漏
	//int2_ptr没有释放，泄漏
#endif
}

int main(int argc, char **argv)
{
	MemoryTraceTest();
}
