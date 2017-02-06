#C++ Primer
##Chapter 10
###10.1 && 10.2
~~~c
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
using namespace std;

int main()
{
	vector<int> ivec{ 1,2,3,4,5,6,2,3,4,5,3,4 };
	list<string> slst{ "a","an","the","the","an","the" };
	
	auto i_cnt = count(ivec.cbegin(), ivec.cend(), 4);
	auto s_cnt = count(slst.cbegin(), slst.cend(), "the");

	cout << i_cnt << " " << s_cnt << endl;
}
~~~
###10.3 && 10.4 && 10.5
~~~c
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
using namespace std;

int main()
{
	vector<int> ivec{ 1,2,3,4 };
	auto i_sum = accumulate(ivec.cbegin(), ivec.cend(), 0);
	cout << i_sum << endl;
	
	vector<double> dvec{ 1.1,2.2,3.3,4.4 };
	auto d_sum_to_int = accumulate(dvec.cbegin(), dvec.cend(), 0);
	auto d_sum_to_double = accumulate(dvec.cbegin(), dvec.cend(), 0.0);

	cout << d_sum_to_int << " " << d_sum_to_double << endl;

	vector<char *> roster1{ "Mike", "KK" };
	//vector<char *> roster2{ "Mile", "KK" }; 
	//vector<string> roster1{ string("Mike"), string("KK") };
	vector<string> roster2{ string("Mike"),string("KK") };
	cout << equal(roster1.cbegin(), roster1.cend(), roster2.cbegin(), roster2.cend()) << endl;

}
~~~
###10.6 && 10.7
~~~c
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	vector<int> ivec{ 1,2,3,0,1,2,3,4 };
	fill_n(ivec.begin(), ivec.size(), 0);
	for (const auto &i : ivec)
		cout << i << " ";
	cout << endl;
	//10.7 a 
	vector<int> vec;
	list<int> lst;
	int i;
	while (cin >> i)
		lst.push_back(i);
	fill_n(back_inserter(vec), lst.size(), 0);
	copy(lst.cbegin(), lst.cend(), vec.begin());	//To be sure that vec has enough memory.
	for (const auto &j : vec)
		cout << j << " ";
	cout << endl;
	//10.7 b
	vector<int> vec2;
	vec2.resize(10);	//vec2.reverse(10) is wrong!!!
	fill_n(vec2.begin(), 10, 1);
	for (const auto &z : vec2)
		cout << z << " ";
	cout << endl;

	return 0;
}
~~~
###10.9 && 10.11
~~~c
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void elimDups(vector<string> &);
bool isShorter(const string &, const string&);

int main()
{
	vector<string> words{ "I", "can", "can", "a", "can","in", "a", "can" };
	vector<string> words2(words);
	elimDups(words);
	for (const auto &i : words)
		cout << i << " ";
	cout << endl;

	//10.11
	elimDups(words2);
	stable_sort(words2.begin(), words2.end(), isShorter);
	for (const auto &k : words2)
		cout << k << " ";
	cout << endl;

	return 0;
}

void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto ptr_unique = unique(words.begin(), words.end());
	words.erase(ptr_unique, words.end());
}
bool isShorter(const string &s1, const string& s2)
{
	return s1.size() < s2.size();
}
~~~
###10.12
~~~c
#include <iostream>
#include <vector>
#include <algorithm>
#include "Sales_data.h"
using namespace std;

bool compareIsbn(const Sales_data &, const Sales_data &);

int main()
{
	Sales_data i1("C++ Pimer");
	Sales_data i2("C Primer Plus");
	Sales_data i("D Primer");
	Sales_data i3("C Primer");
	Sales_data i4("C++ primer Plus");
	Sales_data i5("1234");
	vector<Sales_data> svec{ i ,i1,i2,i3,i5,i4 };
	vector<Sales_data> svec2(svec);

	sort(svec.begin(), svec.end(), compareIsbn);
	for (const auto & j : svec)
		cout << j.isbn() << endl;

}

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}
~~~
###10.13
~~~c
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool greater5(const string&);

int main()
{
	vector<string> svec{"C", "C++", "Java", "JavaScript", "Python", "Object-C"};
	auto iter = partition(svec.begin(), svec.end(), greater5);
	cout << "Not less than 5:" << endl;
	for (auto beg = svec.cbegin(); beg != iter; ++beg)
		cout << *beg << " ";
	cout << endl;
	cout << "Less than 5:" << endl;
	for (auto endd = svec.cend() ; iter != endd; ++iter)
		cout << *iter <<" ";
	cout << endl;

	return 0;
}

bool greater5(const string&s) 
{
	return s.size() >= 5;
}
~~~
###10.14 && 10.15
~~~c
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void func(const int c);

int main()
{
	auto f = [](const int i, const int j) {return i + j; };
	cout << f(1, 4) << endl;
	
	func(1);
	
}

void func(const int c)
{
	vector<int> ivec{ 1,3,5,7 };
	for_each(ivec.begin(), ivec.end(), [c](const int j) {cout << j + c << " "; });

	cout << endl;
}
~~~
###10.17
~~~c
#include <iostream>
#include <vector>
#include <algorithm>
#include "Sales_data.h"
using namespace std;

int main()
{
	Sales_data i1("C++ Pimer");
	Sales_data i2("C Primer Plus");
	Sales_data i("D Primer");
	Sales_data i3("C Primer");
	Sales_data i4("C++ primer Plus");
	Sales_data i5("1234");
	vector<Sales_data> svec{ i ,i1,i2,i3,i5,i4 };
	
	sort(svec.begin(), svec.end(), [](const Sales_data &s1, const Sales_data &s2)
									{return s1.isbn() < s2.isbn(); });
	for (const auto & j : svec)
		cout << j.isbn() << endl;
}
~~~
###10.18 && 10.19
~~~c
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void func_18(vector<string> &, vector<string>::size_type);
void func_19(vector<string> &, vector<string>::size_type);
void elimDups(vector<string>&);

int main()
{
	vector<string> svec{"I", "can", "can", "a", "can", "in", "a", "can", "surprise", "!"};
	vector<string> svec2(svec);
	func_18(svec, 2);
	cout << "------------------------------------------" << endl;
	func_19(svec2, 2);
}

void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto ptr_unique = unique(words.begin(), words.end());
	words.erase(ptr_unique, words.end());
}

void func_18(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	auto iter = partition(words.begin(), words.end(), [sz](const string &s)
													{return sz <= s.size(); });
	for_each(words.begin(), iter, [](const string& s) {cout << s << " "; });

}

void func_19(vector<string> &words, vector<string>::size_type sz) 
{	
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string &s1, const string &s2)
											{return s1.size() < s2.size(); });
	auto iter = partition(words.begin(), words.end(), [sz](const string &s)
	{return sz <= s.size(); });
	for_each(words.begin(), iter, [](const string& s) {cout << s << " "; });

}
~~~
###10.20 && 10.21
~~~c
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	vector<string> svec{ "C++", "JavaScript", "Python", "Object-C", "Java" };
	vector<string>::size_type sz = 6;
	auto cnt = count_if(svec.cbegin(), svec.cend(), [sz](const string& s) {return s.size() >= sz; });
	cout << cnt << endl;

	//10.21
	int x = 7;
	auto f = [&x]()mutable {while (x != 0) --x; return x == 0; };
	cout << f();
}
~~~
###10.22 && 10.24
~~~c
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;

bool check_size(const string &, string::size_type);
bool check_size2(int, int);
int main()
{
	vector<string> svec{ "C++", "JavaScript", "Python", "Object-C", "Java" };
	auto cnt = count_if(svec.cbegin(), svec.cend(), bind(check_size, _1, 6));
	cout << cnt << endl;
	//10.24
	string s("abcd");
	vector<int> ivec{ 1,3,5,7,9 };
	auto x = find_if(ivec.cbegin(), ivec.cend(), bind(check_size2, s.size(), _1));
	cout << *x << endl;
}

bool check_size(const string &s, string::size_type sz)
{
	return s.size() >= sz;
}

bool check_size2(int a, int b)
{
	return a < b;
}
~~~
###10.25
~~~c
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;

void elimDups(vector<string>&);
bool check_size(const string&, string::size_type);
int main()
{
	vector<string> svec{ "I", "can", "can", "a", "can", "in", "a", "can", "surprise", "!" };
	elimDups(svec);
	auto iter = partition(svec.begin(), svec.end(), bind(check_size, _1, 6));
	for_each(svec.begin(), iter, [](const string &s) {cout << s << " ";  });
}
void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto ptr_unique = unique(words.begin(), words.end());
	words.erase(ptr_unique, words.end());
}
bool check_size(const string &s, string::size_type sz)
{
	return s.size() >= sz;
}
~~~
###10.27 && 10.28
~~~c
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	vector<int> ivec{ 1,2,3,4,5,2,3,4,2,3 };
	vector<int> ivec2;
	sort(ivec.begin(), ivec.end());
	unique_copy(ivec.cbegin(), ivec.cend(), inserter(ivec2, ivec2.begin()));
	for (const auto &i : ivec2)
		cout << i << " ";
	cout << endl;
	//10.28
	list<int> ivec3{ 1,2,3,4,5,6,7,8,9 };
	list<int> ivec_r{ 9,8,7,6,5,4,3,2,1 };
	list<int> ivec4, ivec5, ivec6;
	copy(ivec3.cbegin(), ivec3.cend(), inserter(ivec4, ivec4.begin()));
	copy(ivec3.cbegin(), ivec3.cend(), back_inserter(ivec5));
	copy(ivec3.cbegin(), ivec3.cend(), front_inserter(ivec6));
	cout << (ivec3 == ivec4) << endl;
	cout << (ivec3 == ivec5) << endl;
	cout << (ivec_r == ivec6) << endl;
}
~~~
###10.29~10.31
~~~c
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("ttlj.txt");
	istream_iterator<string> in_iter(in), eof;
	ostream_iterator<string> out_iter(cout, "\n");
	vector<string> svec(in_iter, eof);
	copy(svec.cbegin(), svec.cend(), out_iter);
	//10.30
	istream_iterator<int> in_iter2(cin), eof2;
	ostream_iterator<int> out_iter2(cout, " ");
	vector<int> ivec(in_iter2, eof2);
	
	sort(ivec.begin(), ivec.end());
	copy(ivec.cbegin(), ivec.cend(), out_iter2);
	cout << endl;
	//10.31
	vector<int> ivec2(ivec);
	unique_copy(ivec2.cbegin(), ivec2.cend(), out_iter2);
}
~~~
###10.33
~~~c
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("int.txt");
	ofstream odd("odd.txt"), even("even.txt");
	istream_iterator<int> in_iter(in), eof;
	ostream_iterator<int> out_iter1(odd, " ");
	ostream_iterator<int> out_iter2(even, "\n");
	vector<int> ivec(in_iter, eof);
	copy_if(ivec.cbegin(), ivec.cend(), out_iter1, [](const int j) {return j % 2 == 1; });
	copy_if(ivec.cbegin(), ivec.cend(), out_iter2, [](const int j) {return j % 2 == 0; });

}
~~~
###10.34~10.37
~~~c
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	vector<int> ivec{ 1,2,3,4,5,6 };
	for_each(ivec.crbegin(), ivec.crend(), [](const int j){cout << j << " "; });
	cout << endl;
	//10.35
	for (auto beg = ivec.begin(); beg != ivec.end(); ++beg)
		cout << *beg << " ";
	cout << endl;
	//10.36
	list<int> lst{ 2,4,1,0,1,6,4,3,0,3,3 };
	auto iter = find(lst.crbegin(), lst.crend(), 0);
	cout << *iter << endl;
	cout << *++iter << endl;
	//10.37
	vector<int> ivec2 {11, 22, 33, 44, 55, 66, 77, 88, 99};
	list<int> lst2;
	copy(ivec2.rbegin() + 1, ivec2.rbegin() + 6, back_inserter(lst2));
	for (const auto &i : lst2)
		cout << i << " ";
}
~~~

