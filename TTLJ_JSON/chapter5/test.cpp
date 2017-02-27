#include <iostream>
#include <string>
#include <cstdlib>
#include "ttlj_json.h"
using namespace std;

static int mian_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual)\
	do{\
		++test_count;\
		if(equality)\
			++test_pass;\
		else{\
			cerr<<__FILE__<< "  line: "<< __LINE__<<"  expect: "<<expect<<" actual :"<<actual<<endl;\
			mian_ret = 1;\
		}\
	}while(0)
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect)==(actual), expect, actual)
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect)==(actual), expect, actual)
#define TEST_NUMBER(expect, json)\
	do{\
		Lept_value lvvv;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lvvv.lept_parse(json));\
		EXPECT_EQ_INT(LEPT_NUMBER, lvvv.lept_get_type());\
		EXPECT_EQ_DOUBLE(expect, lvvv.lept_get_number());\
	}while(0)
#define TEST_ERROR(error, json)\
	do{\
		Lept_value lv;\
		lv.lept_set_type(LEPT_FALSE);\
		EXPECT_EQ_INT(error, lv.lept_parse(json));\
		EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());\
	}while(0)
#define TEST_STRING(expect, json)\
	do{\
		Lept_value lv(LEPT_NULL);\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse(json));\
		EXPECT_EQ_INT(LEPT_STRING, lv.lept_get_type());\
		EXPECT_EQ_BASE((string(expect)).size() == lv.lept_get_string_length(), expect, lv.lept_get_string());\
	}while(0)


static void	test_parse_null()
{
	Lept_value lv(LEPT_NULL);
	EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse("null"));
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());
}
static void test_parse_true()
{
	Lept_value lv;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse("true"));
	EXPECT_EQ_INT(LEPT_TRUE, lv.lept_get_type());
}
static void test_parse_false()
{
	Lept_value lv;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse("false"));
	EXPECT_EQ_INT(LEPT_FALSE, lv.lept_get_type());
}
static void test_parse_root_not_singluar()
{
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "null    x");
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0123");
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x0");
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x123");
}
static void test_parse_expect_value()
{
	TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, "");
	TEST_ERROR(LEPT_PARSE_EXPECT_VALUE, " ");
}
static void test_parse_invalid_value()
{
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "treu");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "nul");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "?");

	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+0");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+1");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, ".123");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "1.");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "inf");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "NAN");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "INF");
}
static void test_number()
{
	TEST_NUMBER(0.0, "0");
	TEST_NUMBER(0.0, "-0");
	TEST_NUMBER(0.0, "-0.0");
	TEST_NUMBER(1.0, "1");
	TEST_NUMBER(-1.0, "-1");
	TEST_NUMBER(1.5, "1.5");
	TEST_NUMBER(-1.5, "-1.5");
	TEST_NUMBER(3.1416, "3.1416");
	TEST_NUMBER(1E10, "1E10");
	TEST_NUMBER(1e10, "1e10");
	TEST_NUMBER(1E+10, "1E+10");
	TEST_NUMBER(1E-10, "1E-10");
	TEST_NUMBER(-1e10, "-1e10");
	TEST_NUMBER(-1e-10, "-1E-10");
	TEST_NUMBER(1.234E+10, "1.234E+10");
	TEST_NUMBER(1.234E-10, "1.234E-10");
	TEST_NUMBER(0.0, "1e-999999");
}
static void test_parse_number_too_big()
{
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "1e30999999");
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
}
static void test_parse_string()
{
	TEST_STRING("", "\"\"");
	TEST_STRING("hello", "\"hello\"");
	TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
	TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");

	TEST_STRING("Hello World", "\"Hello\\u0000World\"");	// \u0000对应的ASCII值为NULL 在C++string中用' '或0表示
	TEST_STRING("Hello0World", "\"Hello\\u0000World\"");	
	TEST_STRING("\x24", "\"\\u0024\"");						
	TEST_STRING("\xC2\xA2", "\"\\u00A2\"");					
	TEST_STRING("\xE2\x82\xAC", "\"\\u20AC\"");
	TEST_STRING("\xF0\x9D\x84\x9E", "\"\\uD834\\uDD1E\"");		
}
static void test_parse_miss_quotation_mark()
{
	TEST_ERROR(LEPT_PARSE_MISS_QUOTATION_MARK, "\"");
	TEST_ERROR(LEPT_PARSE_MISS_QUOTATION_MARK, "\"abc");
}
static void test_parse_invalid_string_char()
{
	TEST_ERROR(LEPT_PARSE_INVALID_STRING_CHAR, "\"\x01\"");
	TEST_ERROR(LEPT_PARSE_INVALID_STRING_CHAR, "\"\xF\"");
}
static void test_parse_invalid_string_escape()
{
	TEST_ERROR(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\v\"");
	TEST_ERROR(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\'\"");
	TEST_ERROR(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\0\"");
	TEST_ERROR(LEPT_PARSE_INVALID_STRING_ESCAPE, "\"\\x12\"");
}
static void test_parse_invalid_unicode_hex() 
{
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u0\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u01\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u012\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u/000\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\uG000\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u0/00\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u0G00\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u0/00\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u00G0\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u000/\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u000G\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_HEX, "\"\\u 123\"");
}
static void test_parse_invalid_unicode_surrogate() 
{
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uDBFF\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\\\\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uDBFF\"");
	TEST_ERROR(LEPT_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uE000\"");
}
static void test_acess_null()
{
	Lept_value lv("aaa");
	lv.lept_set_null();
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());
}
static void test_acess_true()
{
	Lept_value lv("aaa");
	lv.lept_set_boolean(11);
	EXPECT_EQ_INT(LEPT_TRUE, lv.lept_get_boolean());
}
static void test_acess_false()
{
	Lept_value lv("aaa");
	lv.lept_set_null();
	lv.lept_set_boolean(0);
	EXPECT_EQ_INT(LEPT_FALSE, lv.lept_get_boolean());
}

static void test_lept_parse_array()
{
	Lept_value lv;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse("[]"));
	EXPECT_EQ_INT(LEPT_ARRAY, lv.lept_get_type());
	EXPECT_EQ_INT(0, lv.lept_get_array_size());

	lv.lept_set_null();
	EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse("[ null , false , true ,    123 , \"abc\"  ]"));
	EXPECT_EQ_INT(LEPT_ARRAY, lv.lept_get_type());
	EXPECT_EQ_INT(5, lv.lept_get_array_size());
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_array_element(0).lept_get_type());
	EXPECT_EQ_INT(LEPT_FALSE, lv.lept_get_array_element(1).lept_get_type());
	EXPECT_EQ_INT(LEPT_TRUE, lv.lept_get_array_element(2).lept_get_type());
	EXPECT_EQ_INT(LEPT_NUMBER, lv.lept_get_array_element(3).lept_get_type());
	EXPECT_EQ_INT(LEPT_STRING, lv.lept_get_array_element(4).lept_get_type());
	TEST_NUMBER(123.0, to_string((lv.lept_get_array_element(3)).lept_get_number()));

	lv.lept_set_null();
	EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse("[ [ ] , [ 0 ] , [ 0 , 1 ] , [ 0 , 1 , 2 ] ]"));
	EXPECT_EQ_INT(LEPT_ARRAY, lv.lept_get_type());
	EXPECT_EQ_INT(4, lv.lept_get_array_size());
	for (size_t i = 0; i < 4; ++i) {
		Lept_value a = lv.lept_get_array_element(i);
		EXPECT_EQ_INT(LEPT_ARRAY, a.lept_get_type());
		EXPECT_EQ_INT(i, a.lept_get_array_size());
		for (size_t j = 0; j < i; ++j) {
			Lept_value e = a.lept_get_array_element(j);
			EXPECT_EQ_INT(LEPT_NUMBER, e.lept_get_type());
			EXPECT_EQ_DOUBLE(j, e.lept_get_number());
		}
	}
}

static void test_parse()
{
	test_parse_null();
	test_parse_true();
	test_parse_false();
	test_parse_root_not_singluar();
	test_parse_expect_value();
	test_parse_invalid_value();

	test_number();
	//test_parse_number_too_big();	//invalid

	test_parse_string();
	test_parse_miss_quotation_mark();
	test_parse_invalid_string_char();
	test_parse_invalid_string_escape();
	test_acess_null();
	test_acess_true();
	test_acess_false();

	test_parse_invalid_unicode_hex();
	test_parse_invalid_unicode_surrogate();

	test_lept_parse_array();
}

int main()
{
	test_parse();
	cout << test_pass << " " << test_count << " " << test_pass * 100.0 / test_count << "%" << endl;
}