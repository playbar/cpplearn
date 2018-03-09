#ifndef FBC_MESSY_TEST_STRING_HPP_
#define FBC_MESSY_TEST_STRING_HPP_

int test_string_init();
int test_string_base();
int test_string_cctype();
int test_string_func();
int test_string_ifstream_to_string();

void test_strcat();



class String
{
public:
    String(const char *str = 0);// 普通构造函数
    String(const String &other);// 拷贝构造函数
    ~String(void);// 析构函数
    String & operator = (const String &other);// 赋值函数
private:
    char *m_data;// 用于保存字符串
};


#endif // FBC_MESSY_TEST_STRING_HPP_
