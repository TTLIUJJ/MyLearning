#C++ Primer
##Chapter 11
###11.3 && 11.4
~~~c
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <string>
#include <iterator>
using namespace std;

int main()
{
	map<string, size_t> words_count;
	set<string> words{ "a","an","the" };
	string s = "";
	while (cin >> s) {
		auto iter = find_if(s.begin(), s.end(), [](char c) {return ispunct(c); });
		for (auto & i : s)
			i = tolower(i);
		string s2 = "";
		copy(s.begin(), iter, back_inserter(s2));
		if (words.find(s2) == words.end())
			++words_count[s2];
	}
	for (const auto &j : words_count)
		cout << j.first << " " << j.second << endl;
}
~~~
###11.7
~~~c
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	map<string, vector<string>> family;
	string line;
	while (getline(cin, line)) {
		istringstream members(line);
		string names;
		string name;
		members >> name;
		while (members >> names)
			family[name].push_back(names);
	}
	for (const auto & i : family) {
		for (const auto &j : i.second)
			cout << i.first << " " << j << "; ";
		cout << endl;
	}
}
~~~
###11.12 && 11.13
~~~c
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
using namespace std;

int main()
{
	vector<string> svec{ "a","o","e" };
	vector<int> ivec{ 1,2,0 };
	pair<string, int> p;
	vector<pair<string, int>> pvec1, pvec2, pvec3;
	for (size_t i = 0; i < svec.size(); ++i) {
		pvec1.push_back(make_pair(svec[i], ivec[i]));			//the best one
		pvec2.push_back(pair<string, int>(svec[i], ivec[i]));	// the next one
		pvec3.push_back(pair<string, int>{svec[i], ivec[i]});	// the last one
	}
	for (vector<pair<string, int>>::size_type i = 0; i < pvec1.size(); ++i) {
		cout << pvec1[i].first << " " << pvec1[i].second << endl;
		cout << pvec2[i].first << " " << pvec2[i].second << endl;
		cout << pvec3[i].first << " " << pvec3[i].second << endl;
	}
}
~~~
###11.14
~~~c
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
using namespace std;

int main()
{
	map<string, vector<pair<string, string>>> family_ex;
	string line;
	while (getline(cin, line)) {
		istringstream words(line);
		string first_name;
		string second_name;
		string birsthday;
		words >> first_name;
		words >> second_name;
		words >> birsthday;
		family_ex[first_name].push_back(make_pair(second_name, birsthday));
	}
	for (const auto &i : family_ex) {
		for (const auto &j : i.second) {
			cout << i.first << " " << j.first << " " << j.second << endl;
		}
	}
}
~~~
