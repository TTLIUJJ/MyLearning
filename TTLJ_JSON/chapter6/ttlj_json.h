#pragma once
#ifndef TTLJ_JSON_H__
#define TTLJ_JSON_H__
#include <iostream>
#include <cassert>
#include <string>
#include <memory>
#include <list>
#include <vector>
using namespace std;
typedef enum {
	LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
}lept_type;

enum {
	LEPT_PARSE_OK,
	LEPT_PARSE_EXPECT_VALUE,
	LEPT_PARSE_INVALID_VALUE,
	LEPT_PARSE_ROOT_NOT_SINGULAR,
	LEPT_PARSE_NUMBER_TOO_BIG,
	LEPT_PARSE_MISS_QUOTATION_MARK,
	LEPT_PARSE_INVALID_STRING_ESCAPE,
	LEPT_PARSE_INVALID_STRING_CHAR,
	LEPT_PARSE_INVALID_UNICODE_HEX,
	LEPT_PARSE_INVALID_UNICODE_SURROGATE,
	LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
	LEPT_PARSE_MISS_KEY,
	LEPT_PARSE_MISS_COLON,
	LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET
};


typedef struct {
	shared_ptr<const string> json;
	list<char> clst;
}lept_context;

class Lept_value;
class lept_member;
class Lept_value {
public:
	Lept_value() : type(LEPT_NULL), 
		a(make_shared<vector<Lept_value>>()), o(make_shared<vector<lept_member>>()) {}
	Lept_value(lept_type t) :type(t) {}
	Lept_value(double d) :type(LEPT_NUMBER), n(d) {}
	Lept_value(const string& str) :type(LEPT_STRING), s(str) {}
	Lept_value(const vector<Lept_value> &v) :a(make_shared<vector<Lept_value>>(v)) {}
	Lept_value(const vector<lept_member> &v) : o(make_shared<vector<lept_member>>(v)) {}
	Lept_value(const Lept_value &lv) :type(lv.type), n(lv.n), s(lv.s), a(lv.a), o(lv.o) {}
	Lept_value& operator= (const Lept_value &lv)
	{
		if (this != &lv) {
			type = lv.type;  n = lv.n;  s = lv.s;  a = make_shared<vector<Lept_value>>(*lv.a);
			o = make_shared<vector<lept_member>>(*lv.o);
		}
		return *this;
	}

	int lept_parse(const string&);
	Lept_value& lept_set_null();

	lept_type lept_get_type() const;
	Lept_value& lept_set_type(lept_type);

	double lept_get_number() const;
	Lept_value& lept_set_number(double);

	string lept_get_string()const;
	Lept_value& lept_set_string(const string&);
	string::size_type lept_get_string_length() const;

	int lept_get_boolean()const;
	Lept_value& lept_set_boolean(int);

	size_t lept_get_array_size() const;
	Lept_value lept_get_array_element(size_t) const;
	void lept_store_to_array(const vector<Lept_value>&);

	size_t lept_get_object_size() const;
	const string lept_get_object_key(size_t) const;
	size_t lept_get_object_key_length(size_t) const;
	Lept_value lept_get_object_value(size_t) const;
	void lept_store_to_object(const vector<lept_member>&);
private:
	lept_type type;
	double n = 0.0;
	string s;
	shared_ptr<vector<Lept_value>> a;
	shared_ptr<vector<lept_member>> o;
};
class lept_member {
public:
	string k;
	Lept_value v;
};

static void lept_parse_whitespace(lept_context&);
static int lept_parse_value(lept_context &, Lept_value&);
static int lept_parse_number(lept_context&, Lept_value&);
static int lept_parse_literal(lept_context&, Lept_value&, const string&, lept_type);
static int lept_parse_string(lept_context&, Lept_value&);
static bool lept_parse_hex4(string&, unsigned &);
static void lept_encode_utf8(lept_context &, unsigned);
static int lept_parse_array(lept_context&, Lept_value&);
static int lept_parse_string_raw(lept_context&, string&);
static int lept_parse_object(lept_context&, Lept_value&);
#endif 
