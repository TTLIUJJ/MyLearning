#C++ Primer
##Chapter 15
###15.3
~~~c
class Quote {
public:
	Quote() = default;
	Quote(const string& s, double p) :bookNo(s), price(p) {}
	string isbn()const { return bookNo; }
	virtual double net_price(size_t n)const { return n*price; }
	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price = 0.0;
};
~~~
~~~c
double print_total(ostream& os, const Quote& q, size_t n)
{
	double ret = q.net_price(n);
	os << "ISBN: " << q.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}
~~~
###15.5
~~~c
class Bulk_Quote :public Quote {
public:
	Bulk_Quote() = default;
	Bulk_Quote(const string& s, double p, size_t n, double d) :
		Quote(s, p), min_qty(n), discount(d) {}
	double net_price(size_t n) const override;
private:
	size_t min_qty = 0;
	double discount = 0.0;
};

double Bulk_Quote::net_price(size_t n) const
{
	double total = 0.0;
	if (n > min_qty)
		return total = price * n *(1 - discount);
	else
		return total = price * n;
}
~~~
###15.6
~~~c
#include <iostream>
#include <string>
#include "Quote.h"
using namespace std;

int main()
{
	Quote q("C++ primer", 79.1);
	print_total(cout, q, 10);
	Bulk_Quote bq("OS",67, 10, 0.1);
	print_total(cout, bq, 100);
	print_total(cout, bq, 1);
	
}
~~~
###15.7
~~~c
#include <iostream>
#include <string>
#include "Quote.h"
using namespace std;

class Bulk_Quote2 :public Quote {
public:
	Bulk_Quote2() = default;
	Bulk_Quote2(const string& s, double p, size_t n, double d) :
		Quote(s, p), max_qty(n), discount(d) {}
	double net_price(size_t n) const override
	{
		double ret = 0.0;
		if (n > max_qty)
			return ret = max_qty * price * (1 - discount) + (n - max_qty)*price;
		else
			return ret = n * price *(1 - discount);
	}
private:
	size_t max_qty = 0;
	double discount = 0.0;
};

int main()
{
	Bulk_Quote2 bq("C++prime", 79, 10, 0.1);
	print_total(cout, bq, 11);
	print_total(cout, bq, 1);
}
~~~
###15.11
~~~c
void Quote::debug() const
{
	cout << "Quote: " << "bookNo = " << bookNo << " price = " << price << endl;
}
void Bulk_Quote::debug()const
{
	cout << "Bulk_Quote: " << "bookNo = " << isbn() << " price = " << price
		<< " min_qty = " << min_qty << " discount = " << discount << endl;
}
~~~
###15.13
~~~c
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
	string name() { return basename; }
	virtual void print(ostream& os) { os << basename; }
private:
	string basename;
};
class derived :public Base {
public:
	void print(ostream& os) override { Base::print(os); os << " " << i; }
private:
	int i = 0;
};
~~~
###15.14
~~~c
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
	string name() 
	{
		cout << "Base: name()";
		return basename; 
	}
	virtual void print(ostream& os) { os << "Base: print()" << basename; }
private:
	string basename;
};
class derived :public Base {
public:
	void print(ostream& os) override { os << "Derived: prnt() "; Base::print(os); os << " " << i; }
private:
	int i = 0;
};

int main()
{
	Base bobj;
	derived dobj;
	Base *bp1 = &bobj;
	Base *bp2 = &dobj;
	Base &br1 = bobj;
	Base &br2 = dobj;
	bobj.print(cout);
	cout << endl;
	dobj.print(cout);
	cout << endl;
	bp1->name();
	cout << endl;
	bp2->name();
	cout << endl;
	br1.print(cout);
	cout << endl;
	br2.print(cout);
	cout << endl;
}
~~~
###15.15
~~~c
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Quote {
public:
	Quote() = default;
	Quote(const string& s, double p) :bookNo(s), price(p) {}
	string isbn()const { return bookNo; }
	virtual double net_price(size_t n)const { return n*price; }
	virtual void debug()const;
	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price = 0.0;
};
class Disc_Quote : public Quote {
public:
	Disc_Quote() = default;
	Disc_Quote(const string& s, double p, size_t q, double d) :
		Quote(s, p), quantity(q), discount(d) {}
	double net_price(size_t) const = 0;
protected:
	size_t quantity = 0;
	double discount = 0.0;
};
class Bulk_Quote :public Disc_Quote {
public:
	Bulk_Quote() = default;
	Bulk_Quote(const string& s, double p, size_t n, double d) :
		Disc_Quote(s, p, n, d) {};
	double net_price(size_t n) const override;
	void debug() const override;
};

double print_total(ostream& os, const Quote& q, size_t n)
{
	double ret = q.net_price(n);
	os << "ISBN: " << q.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

double Bulk_Quote::net_price(size_t n) const
{
	double total = 0.0;
	if (n > quantity)
		return total = price * n *(1 - discount);
	else
		return total = price * n;
}
void Quote::debug() const
{
	cout << "Quote: " << "bookNo = " << bookNo << " price = " << price << endl;
}
void Bulk_Quote::debug()const
{
	cout << "Bulk_Quote: " << "bookNo = " << isbn() << " price = " << price
		<< " min_qty = " << quantity << " discount = " << discount << endl;
}
~~~
###15.16 && 15.17
~~~c
#include <iostream>
#include <string>
#include "Quote.h"
using namespace std;

class Bulk_Quote2 :public Disc_Quote {
public:
	Bulk_Quote2() = default;
	Bulk_Quote2(const string& s, double p, size_t n, double d) :
		Disc_Quote(s, p, n, d) {}
	double net_price(size_t n) const override
	{
		double ret = 0.0;
		if (n > quantity)
			return ret = quantity * price * (1 - discount) + (n - quantity)*price;
		else
			return ret = n * price *(1 - discount);
	}
};

int main()
{
	Bulk_Quote2 bq("C++prime", 79, 10, 0.1);
	print_total(cout, bq, 11);
	print_total(cout, bq, 1);
	//15.17
	//Disc_Quote dq("C++", 1, 1, 1);
}
~~~
###15.18 ~ 15.20
~~~c
#include <iostream>
using namespace std;

class Base {
public:
	void pub_mem() { cout << "Base: pub_mem()"; }
protected:
	int prot_mem = 0;
private:
	char priv_men = '.';
};

struct Pub_Derv :public Base {
	int f() { return prot_mem; }
	void memfcn(Base &b) { b = *this; }	//public属性的成员函数
};
struct Prot_Derv :protected Base {
	void memfcn(Base &b) { b = *this; }
};
struct Priv_Derv :private Base {
	int f1() const { return prot_mem; }
	void memfcn(Base &b) { b = *this; }
};
struct Derived_from_Public :public Pub_Derv {
	int use_base() { return prot_mem; }
	void memfcn(Base &b) { b = *this; }
};
struct Derived_from_Protected :public Prot_Derv {
	void memfcn(Base &b) { b = *this; }
};
struct Derived_from_Private :public Priv_Derv {
	int use_base() { return 0; }
	//“Base”不可访问，因为“Priv_Derv”使用“private”从“Base”继承
	//void memfcn(Base &b) { b = *this; }
};

int main()
{
	Pub_Derv d1;
	Base *p = &d1;
	Priv_Derv d2;
	//p = &d2;
	Prot_Derv d3;
	//p = &d3;
	Derived_from_Public dd1;
	p = &dd1;
	Derived_from_Private dd2;
	//p = &dd2;
	Derived_from_Protected dd3;
	//p = &dd3;
	//“类型转换”: 从“Derived_from_Protected *”到“Base *”的转换存在，但无法访问

}
~~~
###15.21&&15.22
~~~c
#include <iostream>
using namespace std;

class Check {
public:
	Check() = default;
	Check(unsigned u) :r(u) {}
	virtual unsigned area() { return r*r; }
protected:
	unsigned r = 0;
};

class Circle :public Check {
public:
	Circle() = default;
	Circle(unsigned u) :Check(u) {}
	unsigned area() override { return r * r * 3.14; }
};

class Ball : public  Check {
public :
	Ball() = default;
	Ball(unsigned u) :Check(u) {}
	unsigned area()override { return 4 * 3.14 * r * r; }
};
class Cone : public Circle {
public:
	Cone(unsigned u1, unsigned u2) :Circle(u1), h(u2) {}
	unsigned area() override { return  0.5 * (2 * 3.14*r)*h + 3.14 * r * r; }
private:
	unsigned h = 0;
};
~~~
###15.26
~~~c
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Quote {
public:
	Quote() = default;
	Quote(const string& s, double p) :bookNo(s), price(p) { cout << "Quote: Quote(...)   "; }
	Quote(const Quote &q) :bookNo(q.bookNo), price(q.price) { cout << "Quote: Quote(const...)   "; }
	Quote& operator= (const Quote &q)
	{ 
		if (this != &q) 
		{ bookNo = q.bookNo; price = q.price; }
		cout << "Quote: Quote operator=()   ";
		return *this; 
	}
	string isbn()const { return bookNo; }
	virtual double net_price(size_t n)const { return n*price; }
	virtual void debug()const;
	virtual ~Quote() { cout << "~Quote()" << endl; }
private:
	string bookNo;
protected:
	double price = 0.0;
};
class Disc_Quote : public Quote {
public:
	Disc_Quote() = default;
	Disc_Quote(const string& s, double p, size_t q, double d) :
		Quote(s, p), quantity(q), discount(d) {	cout << "Disc_Quote: Disc_Quote(...)   ";	}
	Disc_Quote(const Disc_Quote &dq) :Quote(dq), quantity(dq.quantity), discount(dq.discount)
				{ cout << "Disc_Quote: Disc_Quote(const...)   ";	}
	Disc_Quote& operator=(const Disc_Quote &dq)
	{
		if (this != &dq) {
			Quote::operator=(dq);
			quantity = dq.quantity;
			discount = dq.discount;
		}
		cout << "Disc_Quote: Disc_Quote operator= (...)   ";
		return *this;
	}
	double net_price(size_t) const = 0;
	~Disc_Quote() override { cout << "~Disc_Quote()" << endl; }
protected:
	size_t quantity = 0;
	double discount = 0.0;
};
class Bulk_Quote :public Disc_Quote {
public:
	Bulk_Quote() = default;
	Bulk_Quote(const string& s, double p, size_t n, double d) :
		Disc_Quote(s, p, n, d) { cout << "Buld_Quote: Bulk_Quote(...)   "; }
	Bulk_Quote(const Bulk_Quote &bq) :Disc_Quote(bq) { cout << "Bulk_Quote: Bulk_Quote(const...)   "; }
	Bulk_Quote& operator=(const Bulk_Quote &bq)
	{
		if (this != &bq) {
			Disc_Quote::operator=(bq);
		}
		cout << "Bulk_Quotr: Bulk_Quote operator=()   ";
		return *this;
	}

	double net_price(size_t n) const override;
	void debug() const override;
	~Bulk_Quote()override { cout << "~Bulk_Quote()" << endl; }
};

double print_total(ostream& os, const Quote& q, size_t n)
{
	double ret = q.net_price(n);
	os << "ISBN: " << q.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

double Bulk_Quote::net_price(size_t n) const
{
	double total = 0.0;
	if (n > quantity)
		return total = price * n *(1 - discount);
	else
		return total = price * n;
}
void Quote::debug() const
{
	cout << "Quote: " << "bookNo = " << bookNo << " price = " << price << endl;
}
void Bulk_Quote::debug()const
{
	cout << "Bulk_Quote: " << "bookNo = " << isbn() << " price = " << price
		<< " min_qty = " << quantity << " discount = " << discount << endl;
}
~~~
~~~c
#include <iostream>
#include "Quote.h"
using namespace std;

int main()
{
	Quote q1("C++", 10);
	cout << endl;
	Quote q2(q1);
	cout << endl;
	Quote q3("C", 1);
	q3 = q1;
	cout << endl;
	//Disc_Quote dq1("C++", 1, 1, 0.1);	//Disc_Quote是抽象基类
	Bulk_Quote bq1("C++", 1, 1, 0.1);
	cout << endl;
	Bulk_Quote bq2(bq1);
	cout << endl;
	Bulk_Quote bq3("C", 1, 1, 0.1);
	cout << endl;
	bq3 = bq1;
	cout << endl;
}
~~~
###15.28 && 15.29
~~~c
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Quote.h"
using namespace std;

int main()
{
	Bulk_Quote bq1("C++", 69, 8, 0.1);
	Bulk_Quote bq2("C", 69, 2, 0.1);
	vector<Quote> qvec{ bq1, bq2 };
	double total = 0.0;
	for (const auto &k : qvec)
		total += k.net_price(5);
	cout << total << endl;


	vector<shared_ptr<Quote>> pvec;
	pvec.push_back(make_shared<Bulk_Quote>(bq1));
	pvec.push_back(make_shared<Bulk_Quote>(bq2));
	double total2 = 0.0;
	for (const auto &k : pvec)
		total2 += k->net_price(5);
	cout << total2 << endl;
}
~~~
###15.30
~~~c
class Basket {
public:
	void add_item(const Quote &sale) { items.insert(shared_ptr<Quote>(sale.clone())); }
	void add_item(Quote &&sale) { items.insert(shared_ptr<Quote>(std::move(sale).clone())); }
	double total_receipt(ostream&) const;
private:
	static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
};
~~~

