#include "ttlj_json.h"

#define EXPECT(lc, ch) do{assert((*(lc.json))[0] == (ch)); }while(0)

void lept_parse_whitespace(lept_context &lc)
{
	string s = *(lc.json);
	if (s.size()) {
		while (s[0] == ' ' || s[0] == '\t' || s[0] == '\n' || s[0] == '\r')
			s = s.substr(1, s.size());
	}
	lc.json = make_shared<const string>(s);
}

int lept_parse_null(lept_context &lc, Lept_value &lv)
{
	EXPECT(lc, 'n');
	while ((*lc.json)[1] != 'u' || (*lc.json)[2] != 'l' || (*lc.json)[3] != 'l')
		return LEPT_PARSE_INVALID_VALUE;
	string s(lc.json->begin() + 4, lc.json->end());
	lc.json = make_shared<const string>(s);
	lv.lept_set_type(LEPT_NULL);
	return LEPT_PARSE_OK;
}

int lept_parse_true(lept_context &lc, Lept_value &lv)
{
	EXPECT(lc, 't');
	while ((*lc.json)[1] != 'r' || (*lc.json)[2] != 'u' || (*lc.json)[3] != 'e')
		return LEPT_PARSE_INVALID_VALUE;
	string s(lc.json->begin() + 4, lc.json->end());
	lc.json = make_shared<const string>(s);
	lv.lept_set_type(LEPT_TRUE);
	return LEPT_PARSE_OK;
}

int lept_parse_false(lept_context &lc, Lept_value &lv)
{
	EXPECT(lc, 'f');
	while ((*lc.json)[1] != 'a' || (*lc.json)[2] != 'l' || (*lc.json)[3] != 's' || (*lc.json)[4] != 'e')
		return LEPT_PARSE_INVALID_VALUE;
	string s(lc.json->begin() + 5, lc.json->end());
	lc.json = make_shared<const string>(s);
	lv.lept_set_type(LEPT_FALSE);
	return LEPT_PARSE_OK;
}

int lept_parse_value(lept_context &lc, Lept_value &lv)
{
	switch ((*lc.json)[0]) {
		case 'n': return lept_parse_null(lc, lv);
		case 't': return lept_parse_true(lc, lv);
		case 'f': return lept_parse_false(lc, lv);
		case '\0':return LEPT_PARSE_EXPECT_VALUE;
		default: return LEPT_PARSE_INVALID_VALUE;
	}
}
 
int Lept_value::lept_parse(const string& json)
{
	lept_context lc;
	int ret = LEPT_PARSE_OK;
	assert(this != NULL);
	lc.json = make_shared<const string>(json);
	this->type = LEPT_NULL;
	lept_parse_whitespace(lc);
	if ((ret = lept_parse_value(lc, *this)) == LEPT_PARSE_OK) {
		lept_parse_whitespace(lc);
		if (lc.json->end() != lc.json->begin())
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
	}
	return ret;
}
 
lept_type Lept_value::lept_get_type() const
{
	assert(this != NULL);
	return type;
}

Lept_value& Lept_value::lept_set_type(lept_type t)
{
	assert(this != NULL);
	type = t;
	return *this;
}