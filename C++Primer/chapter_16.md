#C++ Primer
##Chapter 16
###16.2
~~~c
#include <iostream>
#include <functional>
#include <list>
#include <string>
#include <vector>
#include "Sales_data.h"

using namespace std;

template<typename T>
int compare(const T &lhs, const T &rhs)
{
	if (less<T>()(lhs, rhs))
		return 1;
	else if (less<T>()(rhs, lhs))
		return -1;
	else
		return 0;
}
int main()
{
	int i = 5, j = 6;
	Sales_data s1;
	Sales_data s2;
	cout << compare(i, j) << endl;
	//cout << compare(s1, s2) << endl;
}
~~~
###16.4
~~~c
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

template <typename T, typename U>
T find2(T &lhs, T &rhs, const U &v)
{
	for (; lhs != rhs && *lhs != v; ++lhs)
		;
	return lhs;
}

int main()
{
	vector<int> ivec{ 1,2,3,23,24 };
	auto iter = find2(ivec.begin(), ivec.end(), 2);
	if (iter != ivec.end())
		cout << *iter << endl;
	list<string> slst{ "Rose", "Micgrady", "Melo", "Paul" };
	auto iter2 = find2(slst.begin(), slst.end(), "Melo");
	if (iter2 != slst.end())
		cout << *iter2 << endl;
}
~~~
###16.5
~~~c
#include <iostream>
using namespace std;

template <typename T, unsigned N>
void print(T(&arr)[N])
{
	for (const auto &k : arr)
		cout << k << " ";
}

int main()
{
	int A[] = { 1,3,4,5,6,7,8 };
	print(A);
}
~~~
###16.6
~~~c
#include <iostream>
#include <iterator>
using namespace std;

template <typename T>
auto begin2(const T &arr)
{
	return arr;
}
template <typename T>
auto end2(const T &arr)
{
	return arr + sizeof(arr) / sizeof(*arr);
}

int main()
{
	int A[] = { 1,3,5,6,7 };
	auto iter = begin2(A);
	auto iter_end = end2(A);
	cout << *iter << endl;
	cout << *(iter_end-1) << endl;
}
~~~
###16.7
~~~c
#include <iostream>
using namespace std;

template<typename T> constexpr
size_t size2(T &arr)
{
	return sizeof(arr) / sizeof(*arr);
}

int main()
{
	int A[] = { 1,3,4,5 };
	cout << size2(A);
	constexpr int i = size2(A);
	int B[i] = { 1,1,1,1 };

}
~~~
###16.11
~~~c
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
	List<elemType>();
	List<elemType>(const List<elemType> &);
	List<elemType>& operator= (const List<elemType> &);
	~List<elemType>();
	void insert(ListItem *ptr, elemType value);
private:
	ListItem<elemType> *front, *end;
};
~~~
###16.12
~~~c
#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <stdexcept>
#include <memory>
using namespace std;

template <typename T> class Blob {
public:
	typedef T value_type;
	typedef typename vector<T>::size_type size_type;

	Blob();
	Blob(initializer_list<T>);

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T &t) { data->push_back(std::move(t)); }
	void pop_back();
	T& back();
	T& operator[](size_t);
private:
	shared_ptr<vector<T>> data;
	void check(size_type, const string&) const;
};
template <typename T>
Blob<T>::Blob():data(make_shared<vector<T>>()) {}

template <typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

template<typename T>
void Blob<T>::check(size_type i, const string &msg) const
{
	if (i >= size())
		throw out_of_range(msg);
}
template<typename T>
void Blob<T>::pop_back()
{
	check(0, "pop_back on empty vector");
	data->pop_back();
}
template <typename T>
T& Blob<T>::back()
{
	check(0, "back on empty vector");
	data->back();
}
template <typename t>
T& Blob<T>::operator[] (size_t i)
{
	check(i, "subscript out of range");
	return (*data)[i];
}
~~~
###16.19 && 16.20
~~~c
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void print(const T &t)
{
	typedef typename T::size_type size_type;
	for (size_type i = 0; i!= t.size(); ++i)
		cout <<t[i] << " ";
}

template <typename T>
void print2(T &lhs, T &rhs)
{
	while (lhs != rhs){
		cout << *lhs << " ";
		++lhs;
	}
}

int main()
{
	vector<int> ivec{ 1,5,7,8,0 };
	print(ivec);
	cout << endl;
	print2(begin(ivec), end(ivec));
}
~~~
