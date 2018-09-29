#include "regex.hpp"
#include <regex>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Blog: http://blog.csdn.net/fengbingchun/article/details/54835571

int test_regex_match()
{
	std::string pattern{ "\\d{3}-\\d{8}|\\d{4}-\\d{7}" }; // fixed telephone
	std::regex re(pattern);

	std::vector<std::string> str{ "010-12345678", "0319-9876543", "021-123456789"};

	/* std::regex_match:
		判断一个正则表达式(参数re)是否匹配整个字符序列str,它主要用于验证文本
		注意，这个正则表达式必须匹配被分析串的全部，否则返回false;如果整个序列被成功匹配，返回true
	*/

	for (auto tmp : str) {
		bool ret = std::regex_match(tmp, re);
		if (ret) fprintf(stderr, "%s, can match\n", tmp.c_str());
		else fprintf(stderr, "%s, can not match\n", tmp.c_str());
	}

	return 0;
}

int test_regex_search()
{
	std::string pattern{ "http|hppts://\\w*$" }; // url
	std::regex re(pattern);

	std::vector<std::string> str{ "http://blog.csdn.net/fengbingchun", "https://github.com/fengbingchun",
		"abcd://124.456", "abcd https://github.com/fengbingchun 123" };

	/* std::regex_search:
		类似于regex_match,但它不要求整个字符序列完全匹配
		可以用regex_search来查找输入中的一个子序列，该子序列匹配正则表达式re
	*/

	for (auto tmp : str) {
		bool ret = std::regex_search(tmp, re);
		if (ret) fprintf(stderr, "%s, can search\n", tmp.c_str());
		else fprintf(stderr, "%s, can not search\n", tmp.c_str());
	}

	return 0;
}

int test_regex_search2()
{
	std::string pattern{ "[a-zA-z]+://[^\\s]*" }; // url
	std::regex re(pattern);

	std::string str{ "my csdn blog addr is: http://blog.csdn.net/fengbingchun , my github addr is: https://github.com/fengbingchun " };
	std::smatch results;
	while (std::regex_search(str, results, re)) {
		for (auto x : results)
			std::cout << x << " ";
		std::cout << std::endl;
		str = results.suffix().str();
	}

	return 0;
}

int test_regex_replace()
{
	std::string pattern{ "\\d{18}|\\d{17}X" }; // id card
	std::regex re(pattern);

	std::vector<std::string> str{ "123456789012345678", "abcd123456789012345678efgh",
		"abcdefbg", "12345678901234567X" };
	std::string fmt{ "********" };

	/* std::regex_replace:
		在整个字符序列中查找正则表达式re的所有匹配
		这个算法每次成功匹配后，就根据参数fmt对匹配字符串进行替换
	*/

	for (auto tmp : str) {
		std::string ret = std::regex_replace(tmp, re, fmt);
		fprintf(stderr, "src: %s, dst: %s\n", tmp.c_str(), ret.c_str());
	}

	return 0;
}

int test_regex_replace2()
{
	// reference: http://www.cplusplus.com/reference/regex/regex_replace/
	std::string s("there is a subsequence in the string\n");
	std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

	// using string/c-string (3) version:
	std::cout << std::regex_replace(s, e, "sub-$2");

	// using range/c-string (6) version:
	std::string result;
	std::regex_replace(std::back_inserter(result), s.begin(), s.end(), e, "$2");
	std::cout << result;

	// with flags:
	std::cout << std::regex_replace(s, e, "$1 and $2", std::regex_constants::format_no_copy);
	std::cout << std::endl;

	return 0;
}

int testRegex()
{
    regex regBegin(".*R\\\"\\w{4}\\(");
	string strBegin = " R\"vksl(";
//    string sval = " )vksl\"";

	regex regEnd(".*\\)\\w{4}\\\"");
	string strEnd = " )vksl\",";

    smatch rval;
    cout << regex_search(strBegin, rval, regEnd) << endl;

	//regex_match匹配整个字符串
	regex reg1("\\w+day");
	string s1 = "saturday";
	string s2 = "saturday and sunday";
	smatch r1;
	smatch r2;
	cout << boolalpha << regex_match(s1, r1, reg1) << endl;
	cout << boolalpha << regex_match(s2, r2, reg1) << endl;
	cout << "s1匹配结果：" << r1.str() << endl;
	cout << "s2匹配结果：" << r2.str() << endl;
	cout << endl;

	//regex_match只返回第一个匹配结果
	smatch rr1;
	smatch rr2;
	cout << boolalpha << regex_search(s1, rr1, reg1) << endl;
	cout << "s1匹配结果：" << rr1.str() << endl;
	cout << boolalpha << regex_search(s2, rr2, reg1) << endl;
	cout << "s1匹配结果：" << rr2.str() << endl;
	cout << endl;


	//使用iterator返回多个匹配结果
	//结果要用->
	cout << "iterator结果：" << endl;
	sregex_iterator it(s2.begin(), s2.end(), reg1);
	sregex_iterator end;
	for(; it != end; ++it)
	{
		cout << it->str() << endl;
		//cout << *it << endl; 错误
	}

	cout << "token_iterator结果：" << endl;
	sregex_token_iterator tit(s2.begin(), s2.end(), reg1);
	sregex_token_iterator tend;
	for(; tit != tend; ++tit)
	{
		cout << tit->str() << endl;
		cout << *tit << endl;
	}

	//子表达式匹配
	regex reg2("(\\d{1,3}):(\\d{1,3}):(\\d{1,3}):(\\d{1,3})");
	string ip = "0:11:222:333";
	smatch m;
	regex_match(ip, m, reg2);
	cout << "输出：str()" << endl;
	cout << m.str() << endl;
	cout << m.str(1) << endl;
	cout << m.str(2) << endl;
	cout << m.str(3) << endl;
	cout << m.str(4) << endl;

	cout << "输出：[i]" << endl;
	cout << m[0] << endl;
	cout << m[1] << endl;
	cout << m[2] << endl;
	cout << m[3] << endl;
	cout << m[4] << endl;

	//输出结果同上
	//regex_search(ip, m, str2);
	cout << endl;
	string ip2 = "0:11:222:333 4:55:66:7";
	sregex_iterator ip_it(ip2.begin(), ip2.end(), reg2);
	sregex_iterator ip_end;
	for(; ip_it != ip_end; ++ip_it)
	{
		cout << ip_it->str() << endl;
		cout << ip_it->str(1) << endl;
		cout << ip_it->str(2) << endl;
		cout << ip_it->str(3) << endl;
		cout << ip_it->str(4) << endl;
	}

	return 0;

}

void matchFun()
{
	// regex_match
	string str = "Hello_2018";
	smatch result;
	regex pattern("(.{5})_(\\d{4})");   //匹配5个任意单字符 + 下划线 + 4个数字

	if (regex_match(str, result, pattern))
	{
		cout << result[0] << endl;      //完整匹配结果，Hello_2018
		cout << result[1] << endl;      //第一组匹配的数据，Hello
		cout << result[2] << endl;      //第二组匹配的数据，2018
		cout<<"结果显示形式2"<<endl;
		cout<< result.str() << endl;    //完整结果，Hello_2018
		cout<< result.str(1) << endl;   //第一组匹配的数据，Hello
		cout << result.str(2) << endl;  //第二组匹配的数据，2018
	}

//遍历结果
	for (int i = 0; i < result.size(); ++i)
	{
		cout << result[i] << endl;
	}

	//// regex_search
	string str1 = "Hello 2018, Bye 2017";
	smatch result1;
	regex pattern1("\\d{4}");    //匹配四个数字

//迭代器声明
	string::const_iterator iterStart = str1.begin();
	string::const_iterator iterEnd = str1.end();
	string temp;
	if (regex_search(iterStart, iterEnd, result1, pattern1))
	{
		temp = result[0];
		cout << temp << " ";
		iterStart = result[0].second;   //更新搜索起始位置,搜索剩下的字符串
	}

	///
	string str2 = "Hello_2018!";
	regex pattern2("Hello");
	cout << regex_replace(str2, pattern2, "") << endl;    //输出：_2018，将Hello替换为""
	cout << regex_replace(str2, pattern2, "233") << endl; //输出：_2018，将Hello替换为2333

	//
	string str3 = "Hello_2018!";
	regex pattern3("(.{3})(.{2})_(\\d{4})");    //匹配3个任意字符+2个任意字符+下划线+4个数字
	cout << regex_replace(str3, pattern3, "$1$3") << endl; //输出：Hel2018，将字符串替换为第一个和第三个表达式匹配的内容
	cout << regex_replace(str3, pattern3, "$1$3$2") << endl;  //输出：Hel2018lo，交换位置顺序

	///
	cout << regex_match("aaaAAA", regex("a*", regex::icase)) << endl;   //结果为1
	cout << regex_match("aaaAAA", regex("a*")) << endl;                 //结果为0
	return;
}

int main()
{
	test_regex_match();
    testRegex();
	return 0;
}