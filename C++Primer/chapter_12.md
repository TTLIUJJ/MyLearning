#C++ Primer
##Chapter 12
###12.2
~~~c
#pragma once
#ifndef STRBLOB_H
#define STRBLOB_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <initializer_list>

class StrBlob{
public:
	typedef std::vector<std::string>::size_type size_type;

	StrBlob() :data(std::shared_ptr<std::vector<std::string>>()) {}
	StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

	size_type size() const { return data->size(); }
	bool empty()const { return data->empty(); }
	void push_back(const std::string &s) { data->push_back(s); }
	void pop_back() { check(0, "pop_back on empty StrBlob"); return data->pop_back(); }
	std::string& front() { check(0, "front on empty StrBlob"); return data->front(); }
	std::string& back() { check(0, "back on empty StrBlob"); return data->back(); }
private:
	void check(size_type, const std::string&);

	std::shared_ptr<std::vector<std::string>> data;
};

inline
void StrBlob::check(size_type i, const std::string &msg)
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

#endif
~~~
###12.6
~~~c
#include <iostream>
#include <vector>
#include <new>
using namespace std;

void input_data(vector<int> *);
void output_data(vector<int> *);
int main()
{
	vector<int> *p = new vector<int>();
	input_data(p);
	output_data(p);
	delete p;
}

void input_data(vector<int>* p)
{
	int i;
	while (cin >> i)
		p->push_back(i);
}
void output_data(vector<int> *p)
{
	for (const auto &k : *p)
		cout << k << " ";
}
~~~
