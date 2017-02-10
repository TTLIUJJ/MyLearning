#include <cerrno>
#include <cmath>
#include "ttlj_json.h"

#define EXPECT(lc, ch) do{assert((*(lc.json))[0] == (ch)); }while(0)
#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch) ((ch) >= '1' && (ch) <= '9')
#define SUBSTRING(s) (s = s.substr(1, s.size()))

void lept_parse_whitespace(lept_context &lc)
{
	string s = *(lc.json);
	if (s.size()) {
		while (s[0] == ' ' || s[0] == '\t' || s[0] == '\n' || s[0] == '\r')
			s = s.substr(1, s.size());
	}
	lc.json = make_shared<const string>(s);
}

int lept_parse_literal(lept_context& lc, Lept_value &lv, const string &s, lept_type lt)
{
	EXPECT(lc, s[0]);
	size_t size = s.size();
	for (size_t i = s.size()-1; i > 0; --i) {
		if ((*lc.json)[i] != s[i])
			return LEPT_PARSE_INVALID_VALUE;
	}
	string str(lc.json->begin() + size, lc.json->end());
	lc.json = make_shared<const string>(str);
	lv.lept_set_type(lt);
	return LEPT_PARSE_OK;
}

int lept_parse_number(lept_context &lc, Lept_value &lv)
{
	string s = *lc.json;
	if (s[0] == '-')
		SUBSTRING(s);
	if (s[0] == '0')
		SUBSTRING(s);
	else {
		if (!ISDIGIT1TO9(s[0]))
			return LEPT_PARSE_INVALID_VALUE;
		for (SUBSTRING(s); ISDIGIT(s[0]); SUBSTRING(s))
			;
	}
	if (s[0] == '.') {
		SUBSTRING(s);
		if (!ISDIGIT(s[0]))
			return LEPT_PARSE_INVALID_VALUE;
		for (SUBSTRING(s); ISDIGIT(s[0]); SUBSTRING(s))
			;
	}
	if (s[0] == 'e' || s[0] == 'E') {
		SUBSTRING(s);
		if (s[0] == '-' || s[0] == '+')
			SUBSTRING(s);
		if (!ISDIGIT(s[0]))
			return LEPT_PARSE_INVALID_VALUE;
		for (SUBSTRING(s); ISDIGIT(s[0]); SUBSTRING(s))
			;
	}
	errno = 0;
	double d = atof((*lc.json).c_str());
	if (*lc.json == s)
		return LEPT_PARSE_INVALID_VALUE;
	if (errno == ERANGE && (d == HUGE_VAL || d == -HUGE_VAL))
		return LEPT_PARSE_NUMBER_TOO_BIG;
	lv.lept_set_number(d);
	lc.json = make_shared<const string>(s);
	lv.lept_set_type(LEPT_NUMBER);
	return LEPT_PARSE_OK;
}

int lept_parse_value(lept_context &lc, Lept_value &lv)
{
	switch ((*lc.json)[0]) {
		case 'n': return lept_parse_literal(lc, lv, "null", LEPT_NULL);
		case 't': return lept_parse_literal(lc, lv, "true", LEPT_TRUE);
		case 'f': return lept_parse_literal(lc, lv, "false", LEPT_FALSE);
		case '\0':return LEPT_PARSE_EXPECT_VALUE;
		default: return lept_parse_number(lc, lv);
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
		if (lc.json->end() != lc.json->begin()) {
			this->type = LEPT_NULL;
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
		}
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
double Lept_value::lept_get_number() const
{
	assert(this != NULL && type == LEPT_NUMBER);
	return n;
}
Lept_value& Lept_value::lept_set_number(double d)
{
	assert(this != NULL);
	n = d;
	return *this;
}