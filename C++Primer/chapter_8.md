#C++ Primer
##Chapter 8
###8.1 && 8.2
~~~c
#include <iostream>
#include <vector>
using namespace std;

istream &test(istream &is);
int main()
{
	if (test(cin).good()) {
		cout << " OK !";
	}
}

istream &test(istream &is)
{
	int i = 0;
	vector<int> ivec;
	is >> i;
	while (!is.eof()) {
		ivec.push_back(i);
		is >> i;
	}
	for (auto &a : ivec)
		cout << a << " ";
	is.clear();
	
	return is;
}
~~~
###8.4 && 8.5
~~~c
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void func_8_4();
void func_8_5();

int main()
{
	func_8_4();
	func_8_5();
}

void func_8_4()
{
	ifstream in("ttlj.txt", istream::in);
	string s = "";
	vector<string> svec;
	while (getline(in, s))
		svec.push_back(s);
	in.close();
	for (auto &i : svec)
		cout << i << endl;
}

void func_8_5()
{
	ifstream in("ttlj.txt", istream::in);
	string s = "";
	vector<string> svec;
	while (in >> s) {
		svec.push_back(s);
	}
	in.close();
	for (auto &i : svec)
		cout << i << endl;

}
~~~
###8.6
~~~c
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	ifstream in(argv[1]);
	string s = "";
	while (getline(in, s))
		cout << s << endl;
	in.close();

	return 0;
}
~~~
###8.7
~~~c
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	string s = "";
	while (getline(in, s))
		out << s << endl;
	in.close();
	out.close();
}
~~~
###8.8
~~~c
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	ifstream in(argv[1]);
	ofstream out(argv[2], ofstream::app);
	string s = "";
	while (getline(in, s))
		out << s << endl;
	in.close();
	out.close();
}
~~~
###8.10
~~~c
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	vector<string> svec;
	fstream in("ttlj.txt");
	string line = "";
	while (getline(in, line)) {
		svec.push_back(line);
	}
	
	for (auto &i : svec) {
		istringstream record(i);
		string word = "";
		while (record >> word)
			cout << word << "|||";
		cout << endl;
	}
}
~~~
###8.11
~~~c
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct PersonInfo {
	string name;
	vector<string> phones;
};

int main()
{
	string line, word;
	vector<PersonInfo> people;
	istringstream record;
	
	while (getline(cin, line)) {
		PersonInfo info;
		record.clear();
		record.str(line);
		record >> info.name;
		while (record >> word)
			info.phones.push_back(word);
		people.push_back(info);
	}
	for (auto &i : people) {
		cout << i.name << " ";
		for (auto &j : i.phones)
			cout << j << " ";
		cout << endl;
	}

}
~~~