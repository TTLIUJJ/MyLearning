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
	Lept_value lv;
	EXPECT_EQ_INT(LEPT_PARSE_ROOT_NOT_SINGULAR, lv.lept_parse("null     x"));
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());
}
static void test_parse_expect_value()
{
	Lept_value lv;

	lv.lept_set_type(LEPT_FALSE);
	EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lv.lept_parse(""));
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());

	lv.lept_set_type(LEPT_FALSE);
	EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lv.lept_parse(" "));
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());
}
static void test_parse_invalid_value()
{
	Lept_value lv;
	lv.lept_set_type(LEPT_FALSE);
	EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lv.lept_parse("treu"));
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());

	lv.lept_set_type(LEPT_FALSE);
	EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lv.lept_parse("nul"));
	EXPECT_EQ_INT(LEPT_NULL, lv.lept_get_type());
}
static void test_parse()
{
	test_parse_null();
	test_parse_true();
	test_parse_false();
	test_parse_root_not_singluar();
	test_parse_expect_value();
	test_parse_invalid_value();
}
int main()
{
	test_parse();
	cout << test_pass << " " << test_count << " " << test_pass * 100.0 / test_count << "%" << endl;
}