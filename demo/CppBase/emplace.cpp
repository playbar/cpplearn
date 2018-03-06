#include "emplace.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <tuple>
#include <utility>

using namespace std;

// Blog: http://blog.csdn.net/fengbingchun/article/details/78670376

namespace emplace_ {

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/vector/vector/emplace_back/
int test_emplace_1()
{
{
	/*
		template <class... Args>
		void emplace_back (Args&&... args);
	*/
	std::vector<int> myvector = { 10, 20, 30 };

	myvector.emplace_back(100);
	myvector.emplace_back(200);

	std::cout << "myvector contains:";
	for (auto& x : myvector)
		std::cout << ' ' << x;
	std::cout << '\n';
}

{
	/*
		template <class... Args>
		iterator emplace (const_iterator position, Args&&... args);
	*/
	std::vector<int> myvector = { 10, 20, 30 };

	auto it = myvector.emplace(myvector.begin() + 1, 100);
	myvector.emplace(it, 200);
	myvector.emplace(myvector.end(), 300);

	std::cout << "myvector contains:";
	for (auto& x : myvector)
		std::cout << ' ' << x;
	std::cout << '\n';
}

	return 0;
}

///////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/container/vector/emplace_back
namespace {
struct President {
	std::string name;
	std::string country;
	int year;

	President(std::string p_name, std::string p_country, int p_year)
		: name(std::move(p_name)), country(std::move(p_country)), year(p_year)
	{
		std::cout << "I am being constructed.\n";
	}
	President(President&& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		std::cout << "I am being moved.\n";
	}
	President& operator=(const President& other) = default;
};
}

int test_emplace_2()
{
	/*
		The following code uses emplace_back to append an object of type President to a std::vector.
		It demonstrates how emplace_back forwards parameters to the President constructor and shows
		how using emplace_back avoids the extra copy or move operation required when using push_back.
	*/
	std::vector<President> elections;
	std::cout << "emplace_back:\n";
	elections.emplace_back("Nelson Mandela", "South Africa", 1994);

	std::vector<President> reElections;
	std::cout << "\npush_back:\n";
	reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

	std::cout << "\nContents:\n";
	for (President const& president : elections) {
		std::cout << president.name << " was elected president of "
			<< president.country << " in " << president.year << ".\n";
	}
	for (President const& president : reElections) {
		std::cout << president.name << " was re-elected president of "
			<< president.country << " in " << president.year << ".\n";
	}

	return 0;
}

////////////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back
int test_emplace_3()
{
	/*
		template <class... Args>
		pair<iterator,bool> emplace (Args&&... args);
	*/
	typedef std::tuple<int, double, std::string> Complicated;

	std::map<int, Complicated> m;
	int anInt = 4;
	double aDouble = 5.0;
	std::string aString = "C++";

	// cross your finger so that the optimizer is really good
	//m.insert(/*std::make_pair*/std::pair<int, Complicated>(4, Complicated(anInt, aDouble, aString)));
	m.insert(std::make_pair(4, Complicated(anInt, aDouble, aString)));

	// should be easier for the optimizer
	m.emplace(6, Complicated(anInt, aDouble, aString));
	/*
		std::piecewise_construct: This constant value is passed as the first argument to construct a pair object
		to select the constructor form that constructs its members in place by forwarding the elements of two
		tuple objects to their respective constructor.
	*/
	m.emplace(std::piecewise_construct, std::make_tuple(8), std::make_tuple(anInt, aDouble, aString));

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: https://corecplusplustutorial.com/difference-between-emplace_back-and-push_back-function/
namespace {
class Dat {
	int i;
	std::string ss;
	char c;

public:
	Dat(int ii, std::string s, char cc) :i(ii), ss(s), c(cc) { }

	~Dat() { }
};
}

int test_emplace_4()
{
	std::vector<Dat> vec;
	vec.reserve(3);

	vec.push_back(Dat(89, "New", 'G')); // efficiency lesser
	//vec.push_back(678, "Newer", 'O'); // error,push_back can¡¯t accept three arguments
	vec.emplace_back(890, "Newest", 'D'); // work fine, efficiency is also more

	return 0;
}



} // namespace emplace_


////////////////

// Book结构，保存书本信息
struct SBook
{
	SBook() : bookName(""), price(0)
	{
		std::cout << "default construct: " << bookName << std::endl;
	}
	SBook(std::string bookName_, int price_) : bookName(bookName_), price(price_)
	{
		std::cout << "construct: " << bookName << std::endl;
	};
	SBook(const SBook& rhs) : bookName(rhs.bookName), price(rhs.price)
	{
		std::cout << "copy construct: " << bookName << std::endl;
	}
	~SBook()
	{
		std::cout << "deconstruct: " << bookName << std::endl;
	}

	bool operator <(const SBook& rhs) const
	{
		return bookName < rhs.bookName;
	}
	std::string bookName;
	int price;
};


int test_emplace_5() {
// 测试vector
	vector <SBook> books;
// 预先分配，否则整个vector在容量不够的情况下重新分配内存
	books.reserve(100);

	std::cout << "test push_back:" << endl;
	books.push_back(SBook("C++从入门到放弃", 1));
	std::cout << endl;

	std::cout << "test emplace_back:" << endl;
	books.emplace_back("水浒传", 2);
	std::cout << endl;

	std::cout << "test emplace_back default:" << endl;
	books.emplace_back();
	auto &book = books.back();
	book.bookName = "红楼梦";
	book.price = 5;
	std::cout << endl;

	std::cout << "test emplace:" << endl;
	auto it = books.emplace(books.end());
	it->bookName = "西游记";
	it->price = 3;
	std::cout << endl;

	std::cout << "output all books: " << endl;
	for_each(books.begin(), books.end(), [](const SBook &book) -> void {
		std::cout << book.bookName << endl;
	});
	std::cout<<endl;
// test set
	std::set<SBook>bookSet;

	std::cout << "test bookSet insert:" << endl;
	bookSet.insert(SBook("十万个为什么", 1));
	std::cout << endl;

	std::cout << "test bookSet emplace:" << endl;
	bookSet.emplace("新华字典", 2);
	std::cout << endl;

	std::cout << "output bookset: " << endl;
	for_each(bookSet.begin(), bookSet.end(), [](const SBook &book) -> void {
		std::cout << book.bookName << endl;
	});
	std::cout << endl;
}

class A {
public:
	void print() { printf("Hello\n"); }
};

class B {
public:
	virtual void print() { printf("World\n"); }
};

int main(int argc, const char** argv) {
	A* pA = (A*)NULL;
	B* pB = (B*)NULL;
//	B *pB = new B();
	pA->print();
	pB->print();
	return 0;
}



int main_2(int args, char **argv)
{
	test_emplace_5();
	return 0;

}