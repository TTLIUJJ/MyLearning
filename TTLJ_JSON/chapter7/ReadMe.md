#TTLJ_JSON
##Chapter_7
1. 在类中有成员是智能指针时候，必须在创建时执行显示初始化，所以将lept_context重写
~~~c
class lept_context {
public:
	lept_context() :json(make_shared<const string>()) {}
	shared_ptr<const string> json;
	list<char> clst;
};
~~~
2. 在test_stringify_array()和test_stringify_object()中，存入的double型数据要精确到小数点后面6位
~~~c
static void test_stringify_array()
{
	TEST_ROUNDTRIP("[]");
	TEST_ROUNDTRIP("[null,true,false,123.000000,\"abc\",[1.000000,2.000000,3.000000]]");
}
static void test_stringify_object()
{
	TEST_ROUNDTRIP("{}");
	TEST_ROUNDTRIP("{\"n\":null,\"f\":false,\"t\":true,\"i\":123.000000,\"s\":\"abc\",\"a\":[1.000000,2.000000,3.000000],\"o\":{\"1\":1.000000,\"2\":2.000000,\"3\":3.000000}}");
}
~~~
例如当解析
~~~c
TEST_NUMBER_ROUNDTRIP("0");
~~~
储存在Lept_value中的n实际表示为0.000000。