#pragma once
#ifndef TTLJ_JSON_H__
#define TTLJ_JSON_H__
#include <iostream>
#include <cassert>
#include <string>
#include <memory>
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
	LEPT_PARSE_INVALID_STRING_CHAR
};


typedef struct {
	shared_ptr<const string> json;
}lept_context;

class Lept_value {
public:
	Lept_value() = default;
	Lept_value(lept_type t) :type(t) {}
	Lept_value(double d) :type(LEPT_NUMBER), n(d) {}
	Lept_value(const string& str) :type(LEPT_STRING), s(str) {}

	Lept_value(const Lept_value &lv) :type(lv.type), n(lv.n) {}
	Lept_value& operator= (const Lept_value &lv) 
	{
		if (this != &lv) { type = lv.type;  n = lv.n; }
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
private:
	lept_type type;
	double n = 0.0;
	string s;

};


static void lept_parse_whitespace(lept_context&);
static int lept_parse_number(lept_context&, Lept_value&);
static int lept_parse_literal(lept_context&, Lept_value&, const string&, lept_type);
static int lept_parse_string(lept_context&, Lept_value&);
#endif 
  