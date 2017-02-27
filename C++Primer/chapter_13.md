#C++ Primer
##Chapter 13
###13.5
~~~c
#pragma once
#include <string>
using namespace std;

class HasPtr {
public:
	HasPtr(const string &s = string()) :ps(new string(s)), i(0) {}
	HasPtr(const HasPtr &hp) :ps(new string(*hp.ps)), i(0) {}
private:
	string *ps;
	int i;
};
~~~
###13.8
~~~c
#pragma once
#include <string>
using namespace std;

class HasPtr {
public:
	HasPtr(const string &s = string()) :ps(new string(s)), i(0) {}
	HasPtr(const HasPtr &hp) :ps(new string(*hp.ps)), i(0) {}
	HasPtr& operator=(const HasPtr &hp)
	{
		ps = new string(*hp.ps);
		i = hp.i;
		return *this;
	}

private:
	string *ps;
	int i;
};
~~~
###13.12
~~~c
#include <iostream>
#include "Sales_data.h"
using namespace std;

bool fcn(const Sales_data*, Sales_data);

int main()
{
	Sales_data sd("xxx");
	Sales_data *psd = new Sales_data("yyy");
	cout << "Start" << endl;
	fcn(psd, sd);
	cout << "Finish" << endl;
	delete psd;
}

bool fcn(const Sales_data* trans, Sales_data accum)
{
	Sales_data iteml(*trans), item2(accum);
	return iteml.isbn() != item2.isbn();
}
~~~
###13.14~13.17
~~~c
#include <iostream>
#include <string>
#include <random>
using namespace std;

class numbered{
public:
	numbered() :mysn(rand()) {  }
	numbered(const numbered& n) :mysn(n.mysn) {}
	int mysn;
};

void f(const numbered s)
{
	cout << s.mysn << endl;
}

int main()
{
	numbered a, b = a, c = b;
	numbered d, e;
	f(a);
	f(b);
	f(c);
	f(d);
	f(e);
}
~~~
###13.18&&13.19
~~~c
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
	Employee() = default;
	Employee(const string& s) :name(s), id(factor) { ++factor; }
	Employee(const Employee& e) :name(e.name), id(e.id) {}
	Employee& operator=(const Employee& e) { name = e.name; id = e.id; return *this; }
private:
	string name;
	unsigned id;
	static  unsigned  factor;
};
unsigned Employee::factor = 0;
~~~
###13.30 && 13.31
~~~c
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "hasptr.h"
using namespace std;

int main()
{
	HasPtr p1("haha");
	HasPtr p2("hehe");
	HasPtr p3("a");
	HasPtr p4("utility");
	vector<HasPtr> hvec{ p1, p2, p3,p4 };
	swap(p1, p2);
	sort(hvec.begin(), hvec.end());
	for_each(hvec.cbegin(), hvec.cend(), [](const HasPtr& hp) {cout << hp.get_s() << endl; });
}
~~~
###13.34~13.37
~~~c
#pragma once
#include <iostream>
#include <string>
#include <set>
using namespace std;

class Message {
	friend class Folder;
public:
	explicit Message(const string& str = "") :contents(str) {}
	Message(const Message &m) :contents(m.contents), folders(m.folders) { add_to_Folders(m); }
	Message& operator=(const Message &m)
	{
		remove_from_Folders();
		contents = m.contents;
		folders = m.folders;
		add_to_Folders(m);
		return *this;
	}
	~Message() { remove_from_Folders(); }
	void save(Folder&);
	void remove(Folder&);
	void swap(Message&, Message&);
private:
	string contents;
	set<Folder*> folders;
	void adddFolder(Folder*);
	void remFolder(Folder*);
	void add_to_Folders(const Message&);
	void remove_from_Folders();
};

class Folder {
	friend class Message;
public:
	Folder() = default;
	Folder(const Folder& f) : messages(f.messages) { add_to_Messages(f); }
	Folder& operator=(const Folder& f)
	{
		remove_from_Messages();
		messages = f.messages;
		add_to_Messages(f);
		return *this;
	}
	~Folder() { remove_from_Messages(); }
	void save(Message&);
	void remove(Message&);
private:
	set<Message*> messages;
	void addMsg(Message*);
	void remMsg(Message*);
	void add_to_Messages(const Folder&);
	void remove_from_Messages();
};


void Message::add_to_Folders(const Message& m)
{
	for (auto &f : m.folders)
		f->addMsg(this);
}
void Message::remove_from_Folders()
{
	for (auto &f : folders)
		f->remMsg(this);
}
void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}
void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}
void Message::adddFolder(Folder *f)
{
	folders.insert(f);
}
void Message::remFolder(Folder *f)
{
	folders.erase(f);
}
void Message::swap(Message &lhs, Message &rhs)
{
	using std::swap;
	for (auto &f : rhs.folders)
		f->remMsg(&lhs);
	for (auto &f : lhs.folders)
		f->remMsg(&rhs);
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders, rhs.folders);
	for (auto &f : rhs.folders)
		f->addMsg(&lhs);
	for (auto &f : lhs.folders)
		f->addMsg(&rhs);
}


void Folder::add_to_Messages(const Folder& f)
{
	for (auto &k : f.messages)
		k->adddFolder(this);
}
void Folder::remove_from_Messages()
{
	for (auto &k : messages)
		k->remFolder(this);
}
void Folder::addMsg(Message *m)
{
	messages.insert(m);
}
void Folder::remMsg(Message* m)
{
	messages.erase(m);
}
void Folder::save(Message &m)
{
	messages.insert(&m);
	m.adddFolder(this);
}
void Folder::remove(Message &m)
{
	messages.erase(&m);
	m.remFolder(this);
}
~~~
