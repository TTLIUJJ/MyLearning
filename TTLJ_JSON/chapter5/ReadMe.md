#TTLJ_JSON
##Chapter 5

1. 在类成员有智能指针时，必须以显示的形式初始化智能指针
2. 得再次巩固智能指针的使用方法
3. 在测试样例中
~~~c
#define TEST_NUMBER(expect, json)\
	do{\
		Lept_value lvvv;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lvvv.lept_parse(json));\
		EXPECT_EQ_INT(LEPT_NUMBER, lvvv.lept_get_type());\
		EXPECT_EQ_DOUBLE(expect, lvvv.lept_get_number());\
	}while(0)
~~~

因为宏定义是在使用处展开，所以要把原本的Lept_value lv替换成Lept_value lvvv，否则宏定义将会与以下测试有名字冲突
~~~c
TEST_NUMBER(123.0, to_string((lv.lept_get_array_element(3)).lept_get_number()));
~~~