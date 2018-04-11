#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#include "fstream.hpp"

using namespace std;

// Blog: http://blog.csdn.net/fengbingchun/article/details/51570728

/* reference: 
	http://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
	https://www.ntu.edu.sg/home/ehchua/programming/cpp/cp10_IO.html
	http://www.bogotobogo.com/cplusplus/fstream_input_output.php
*/

//打开文件的方式在类ios(是所有流式I/O类的基类)中定义，常用的值如下：
//		ios::app:以追加的方式打开文件
//		ios::ate：文件打开后定位到文件尾，ios:app就包含有此属性
//		ios::binary： 以二进制方式打开文件，缺省的方式是文本方式。两种方式的区别见前文
//		ios::in：文件以输入方式打开（文件数据输入到内存）
//		ios::out：文件以输出方式打开（内存数据输出到文件）
//		ios::nocreate：不建立文件，所以文件不存在时打开失败
//		ios::noreplace：不覆盖文件，所以打开文件时如果文件存在失败
//		ios::trunc：　　如果文件存在，把文件长度设为0
//
//可以用“或”把以上属性连接起来，如ios::out|ios::binary

int test_file_size()
{
	std::ifstream in("./fstream_data.bin", std::ios::binary);
	if (!in.is_open()) {
		std::cout << "fail to open file\n";
		return -1;
	}

	std::streampos begin, end;
	begin = in.tellg();
	in.seekg(0, std::ios::end);
	end = in.tellg();

	in.close();

	std::cout << "this file's size is: " << (end - begin) << " bytes.\n";

	return 0;
}

int test_fstream1()
{
	char data[100];

	// open a file in write mode.
	std::ofstream outfile;
	outfile.open("./fstream.dat");
	if (!outfile.is_open()) {
		std::cout << "fail to open file to write\n";
		return -1;
	}

	std::cout << "Writing to the file" << std::endl;
	std::cout << "Enter your name: ";
	std::cin.getline(data, 100);

	// write inputted data into the file.
	outfile << data << std::endl;

	std::cout << "Enter your age: ";
	std::cin >> data;
	std::cin.ignore();

	// again write inputted data into the file.
	outfile << data << std::endl;

	// close the opened file.
	outfile.close();

	// open a file in read mode.
	std::ifstream infile;
	infile.open("./fstream.dat");
	if (!infile.is_open()) {
		std::cout << "fail to open file to read\n";
		return -1;
	}

	std::cout << "Reading from the file" << std::endl;
	infile >> data;

	// write the data at the screen.
	std::cout << data << std::endl;

	// again read the data from the file and display it.
	infile >> data;
	std::cout << data << std::endl;

	// close the opened file.
	infile.close();

	return 0;
}

int test_fstream2()
{
	/* Testing Simple File IO (TestSimpleFileIO.cpp) */
	std::string filename = "./test.txt";

	// Write to File
	std::ofstream fout(filename.c_str());  // default mode is ios::out | ios::trunc
	if (!fout) {
		std::cerr << "error: open file for output failed!" << std::endl;
		abort();  // in <cstdlib> header
	}
	fout << "apple" << std::endl;
	fout << "orange" << std::endl;
	fout << "banana" << std::endl;
	fout.close();

	// Read from file
	std::ifstream fin(filename.c_str());  // default mode ios::in
	if (!fin) {
		std::cerr << "error: open file for input failed!" << std::endl;
		abort();
	}
	char ch;
	while (fin.get(ch)) {  // till end-of-file
		std::cout << ch;
	}
	fin.close();
	return 0;
}

int test_fstream3()
{
	/* Testing Binary File IO (TestBinaryFileIO.cpp) */
	std::string filename = "./test.bin";

	// Write to File
	std::ofstream fout(filename.c_str(), std::ios::out | std::ios::binary);
	if (!fout.is_open()) {
		std::cerr << "error: open file for output failed!" << std::endl;
		abort();
	}
	int i = 1234;
	double d = 12.34;
	fout.write((char *)&i, sizeof(int));
	fout.write((char *)&d, sizeof(double));
	fout.close();

	// Read from file
	std::ifstream fin(filename.c_str(), std::ios::in | std::ios::binary);
	if (!fin.is_open()) {
		std::cerr << "error: open file for input failed!" << std::endl;
		abort();
	}
	int i_in;
	double d_in;
	fin.read((char *)&i_in, sizeof(int));
	std::cout << i_in << std::endl;
	fin.read((char *)&d_in, sizeof(double));
	std::cout << d_in << std::endl;
	fin.close();

	return 0;
}

int test_fstream4()
{
	std::string theNames = "Edsger Dijkstra: Made advances in algorithms, the semaphore (programming).\n";
	theNames.append("Donald Knuth: Wrote The Art of Computer Programming and created TeX.\n");
	theNames.append("Leslie Lamport: Formulated algorithms in distributed systems (e.g. the bakery algorithm).\n");
	theNames.append("Stephen Cook: Formalized the notion of NP-completeness.\n");

	std::ofstream ofs("./theNames.txt");
	if (!ofs)	{
		std::cout << "Error opening file for output" << std::endl;
		return -1;
	}
	ofs << theNames << std::endl;
	ofs.close();

	char letter;
	int i;
	std::string line;

	std::ifstream reader("./theNames.txt");

	if (!reader) {
		std::cout << "Error opening input file" << std::endl;
		return -1;
	}

	//for (i = 0; !reader.eof(); i++) {
	while (!reader.eof()) {
		reader.get(letter);
		std::cout << letter;

		//getline( reader , line ) ;
		//std::cout << line << std::endl;
	}

	reader.close();

	return 0;
}

//////////////////////////////////////////////////////////////////////////
std::ofstream _file;

int test_init_database()
{
	_file.open("./data.bin");
	if (!_file.is_open()) {
		fprintf(stderr, "open file fail\n");
		return -1;
	}

	return 0;
}

int test_store_database()
{
	for (int i = 0; i < 10; ++i) {
		_file.write((char*)&i, sizeof(i));
	}

	return 0;
}

int test_close_database()
{
	_file.close();
	return 0;
}

int test_fstream5()
{
	test_init_database();

	for (int i = 0; i < 5; ++i) {
		test_store_database();
	}

	test_close_database();

	std::ifstream file("./data.bin");
	if (!file.is_open()) {
		fprintf(stderr, "open file fail\n");
		return -1;
	}

	int a[100];
	for (int i = 0; i < 50; ++i) {
		file.read((char*)&a[i], sizeof(int));
	}

	file.close();

	return 0;
}

//////////////////////////////////////////////////
static void parse_string(char* line, std::string& image_name, std::vector<int>& rect)
{
	std::string str(line);
	rect.resize(0);

	int pos = str.find_first_of(" ");
	image_name = str.substr(0, pos);
	std::string str1 = str.substr(pos + 1, str.length());
	for (int i = 0; i < 4; ++i) {
		pos = str1.find_first_of(" ");
		std::string x = str1.substr(0, pos);
		str1 = str1.erase(0, pos+1);
		rect.push_back(std::stoi(x));
	}
}

int test_fstream6()
{
	std::string name{ "./list.txt" };
	std::ifstream in(name.c_str(), std::ios::in);
	if (!in.is_open()) {
		fprintf(stderr, "open file fail: %s\n", name.c_str());
		return -1;
	}

	int count{ 0 };
	char line[256];
	in.getline(line, 256);
	count = atoi(line);
	std::cout << count << std::endl;
	//while (!in.eof()) {
	for (int i = 0; i < count; ++i) {
		in.getline(line, 256);
		std::cout << "line: "<< line << std::endl;
		std::string image_name{};
		std::vector<int> rect{};
		parse_string(line, image_name, rect);
		std::cout << "image name: " << image_name << std::endl;
		for (auto x : rect)
			std::cout << "  " << x << "  ";
		std::cout << std::endl;
	}

	in.close();
	return 0;
}

//////////////////////////////////////////////
int test_fstream7()
{
	std::string name{ "./list.txt" };
	std::ifstream in(name.c_str(), std::ios::in);
	if (!in.is_open()) {
		fprintf(stderr, "open file fail: %s\n", name.c_str());
		return -1;
	}

	int count{ 0 };
	std::string image_name{};
	int left{ 0 }, top{ 0 }, right{ 0 }, bottom{ 0 };
	in >> count;
	std::cout << "count: " << count << std::endl;
	for (int i = 0; i < count; ++i) {
		in >> image_name >> left >> top >> right >> bottom;
		fprintf(stdout, "image_name: %s, rect: %d, %d, %d, %d\n", image_name.c_str(), left, top, right, bottom);
	}

	in.close();
	return 0;
}

void test_read_file()
{
    const char * filename = "CMakeCache.txt";
    char * buffer;
    long size;
    ifstream in (filename, ios::in|ios::binary|ios::ate);
    size = in.tellg();
    in.seekg (0, ios::beg);
    buffer = new char [size];
    in.read (buffer, size);
    in.sync();
    in.close();
    cout << "the complete file is in a buffer";
    delete[] buffer;
}


int main(int argn, char **argv )
{
    test_read_file();
    return 0;
}