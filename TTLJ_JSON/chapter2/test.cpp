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
		Lept_value lv;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lv.lept_parse(json));\
		EXPECT_EQ_INT(LEPT_NUMBER, lv.lept_get_type());\
		EXPECT_EQ_DOUBLE(expect, lv.lept_get_number());\
	}while(0)
#define TEST_ERROR(error, json)\
	do{\
		Lept_value lv;\
		lv.lept_set_type(LEPT_FALSE);\
		EXPECT_EQ_INT(error, lv.lept_parse(json));\
		EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());\
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
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG , "1e30999999");
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
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
}
int main()
{
	test_parse();
	cout << test_pass << " " << test_count << " " << test_pass * 100.0 / test_count << "%" << endl;
}