#C++ Primer
##Chapter 7
###7.1
~~~c
#include <iostream>
#include <string>
#include "Sales_data.h"
using namespace std;

int main()
{
	Sales_data total;
	string bookNo = "";
	unsigned units_sold = 0;
	double revenue = 0;
	double price = 0;
	if (cin >> bookNo >> units_sold >> price) {
		total.bookNo = bookNo;
		total.units_sold = units_sold;
		total.revenue = units_sold * price;
		Sales_data trans;
		while (cin >> bookNo >> units_sold >> price) {
			trans.bookNo = bookNo;
			trans.units_sold = units_sold;
			trans.revenue = units_sold * price;
			if (trans.bookNo == total.bookNo) {
				total.units_sold += trans.units_sold;
				total.revenue += trans.revenue;
			}
			else {
				cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
				total.bookNo = trans.bookNo;
				total.units_sold = trans.units_sold;
				total.revenue = trans.revenue;
			}
		}
		cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
	}
	else {
		cerr << "No data!" << endl;
		return -1;
	}
	return 0;
}
~~~
###7.2
~~~c
#pragma once
#include <string>
#ifndef SALES_DATA_H
#define SALES_DATA_H
struct Sales_data {
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data &);

	std::string bookNo = "";
	unsigned units_sold = 0;
	double revenue = 0;
};
Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

#endif
~~~
###7.3
~~~c
#include <iostream>
#include <string>
#include "Sales_data.h"
using namespace std;

int main()
{
	Sales_data total;
	double price = 0;
	if (cin >> total.bookNo >> total.units_sold >> price) {
		total.revenue = total.units_sold * price;
		Sales_data trans;
		while (cin >> trans.bookNo >> trans.units_sold >> price) {
			trans.revenue = trans.units_sold * price;
			if (trans.isbn() == total.isbn())
				total.combine(trans);
			else {
				cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
				total.bookNo = trans.bookNo;
				total.units_sold = trans.units_sold;
				total.revenue = trans.revenue;
			}
		}
		cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
	}
	else {
		cerr << "No data!" << endl;
		return -1;
	}
	return 0;
}
~~~
###7.4&&7.5
~~~c
#pragma once
#ifndef PERSON_H
#define PERSON_H
#include <string>
struct Person {
	std::string get_name() const { return name; }
	std::string get_address() const { return address; }

	std::string name;
	std::string address;
};

#endif
~~~
###7.6
~~~c
#pragma once
#include <string>
#ifndef SALES_DATA_H
#define SALES_DATA_H
struct Sales_data {
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data &);

	std::string bookNo = "";
	unsigned units_sold = 0;
	double revenue = 0;
};
Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
Sales_data add(const Sales_data &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &item);	//此处声明若是未标注形参名字，函数的定义不能通过？？？
std::ostream &print(std::ostream &, const Sales_data &);

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

std::istream &read(std::istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = item.units_sold * price;
	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue;
	return os;
}
#endif
~~~
###7.7
~~~c
#include <iostream>
#include <string>
#include "Sales_data.h"
using namespace std;

int main()
{
	Sales_data total;
	if (read(cin, total)) {
		Sales_data trans;
		while (read(cin, trans)) {
			if (trans.isbn() == total.isbn()) 
				total.combine(trans);
			else {
				print(cout, total);
				total = trans;
			}
		}
	}
	else {
		cerr << "No data!" << endl;
		return -1;
	}
	return 0;
}
~~~
###7.9
~~~c
#pragma once
#ifndef PERSON_H
#define PERSON_H
#include <string>
struct Person {
public:
	std::string get_name() const { return name; }
	std::string get_address() const { return address; }

	std::string name;
	std::string address;
};

std::istream &read(std::istream &, Person &);
std::ostream &print(std::ostream &, const Person &person);

std::istream &read(std::istream &is, Person &person)
{
	is >> person.name >> person.address;
	return is;
}

std::ostream &print(std::ostream &os, const Person& person)
{
	os << person.get_name() << " " << person.get_address();
	return os;
}

#endif
~~~
###7.11
~~~c
#include <iostream>
#include <string>
#include "Sales_data.h"
using namespace std;

int main()
{
	string s = "C++ primer";
	Sales_data item1;
	Sales_data item2(s);
	Sales_data item3(s, 2, 79.9);
	Sales_data item4(std::cin);
	print(cout, item1) << endl;
	print(cout, item2) << endl;
	print(cout, item3) << endl;
	print(cout, item4) << endl;
}
~~~
###7.13

###7.14
~~~c
Sales_data(const string& s):bookNo(s), units_sold(0), revenue(0) {}
~~~
###7.15
~~~c
#pragma once
#ifndef PERSON_H
#define PERSON_H
#include <string>
struct Person {
public:
	Person() = default;
	Person(const std::string &n, const std::string &a) :name(n), address(a) {}
	Person(std::istream &is) { read(is, *this); }

	std::string get_name() const { return name; }
	std::string get_address() const { return address; }

	std::string name;
	std::string address;
};

std::istream &read(std::istream &, Person &);
std::ostream &print(std::ostream &, const Person &person);

std::istream &read(std::istream &is, Person &person)
{
	is >> person.name >> person.address;
	return is;
}

std::ostream &print(std::ostream &os, const Person& person)
{
	os << person.get_name() << " " << person.get_address();
	return os;
}

#endif
~~~
###7.23&&7.24
~~~c
#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include <vector>
class Screen {
public:
	typedef std::string::size_type pos;
	Screen() = default;
	Screen(pos h, pos w) :height(h), width(w), contents(h*w, ' ') {}
	Screen(pos h, pos w, char c) :height(h), width(w), contents(h*w, c) {}

	Screen &move(pos r, pos c);
	char get() const;
	char get(pos, pos) const;

	void some_member() const { ++access_ctr; }
private:
	pos cursor = 0;
	pos height = 0;
	pos width = 0;
	std::string contents = "";
	mutable size_t access_ctr;
};
inline
Screen &Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}
inline 
char Screen::get()const
{
	return contents[cursor];
}
inline 
char Screen::get(pos r, pos c) const
{
	pos row = r * width;
	return contents[row + c];
}

#endif
~~~
###7.31
~~~c
class X;
class Y;
class X{
	Y *py;
};
class Y{
	X x;
};
~~~
###7.32
~~~c
class window_mgr{
public:
	typedef std::vector<Screen>::size_type ScreenInedx;
	void clear(ScreenIndex); 
private:
	std::vector<Screen> screens{Screen(24, 80, ' ')};
};

class Screen{
	friend void Window_mgr::clear(ScreenIndex);
public:
	//...
private:
	//...
};

void Window_mgr::clear(ScreenIndex i)
{
	Screen &s = screens[i];
	s.contents = std::string(s.height * s.width, ' ');
}
~~~