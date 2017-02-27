#include <cerrno>
#include <cmath>
#include "ttlj_json.h"

#define EXPECT(lc, ch) do{assert((*(lc.json))[0] == (ch)); }while(0)
#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch) ((ch) >= '1' && (ch) <= '9')
#define SUBSTRING(s) (s.erase(0, 1))
#define ADD_TO_STRING(target_string, ch) ((target_string) += (ch))

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
	for (size_t i = s.size() - 1; i > 0; --i) {
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
bool lept_parse_hex4(string &str, unsigned &u)
{
	for (size_t i = 0; i < 4; ++i) {
		char ch = str[0];
		SUBSTRING(str);
		u <<= 4;
		if (ch >= '0' && ch <= '9') u |= (ch - '0');
		else if (ch >= 'A' && ch <= 'F') u |= (ch - 'A' + 10);
		else if (ch >= 'a' && ch <= 'f') u |= (ch - 'a' + 10);
		else
			return false;
	}
	return true;
}
void lept_encode_utf8(lept_context &lc, unsigned u)
{
	if (u <= 0x7F) {
		lc.clst.push_back(u & 0xFF);
	}
	else if (u <= 0x07FF) {
		lc.clst.push_back(0xC0 | ((u >> 6) & 0xFF));
		lc.clst.push_back(0x80 | (u & 0x3F));
	}
	else if (u <= 0xFFFF) {
		lc.clst.push_back(0xE0 | ((u >> 12) & 0xFF));
		lc.clst.push_back(0x80 | ((u >> 6) & 0x3F));
		lc.clst.push_back(0x80 | (u & 0x3F));
	}
	else {
		assert(u <= 0x10FFFF);
		lc.clst.push_back(0xF0 | ((u >> 18) & 0xFF));
		lc.clst.push_back(0x80 | ((u >> 12) & 0x3F));
		lc.clst.push_back(0x80 | ((u >> 6)  & 0x3F));
		lc.clst.push_back(0x80 | ( u        & 0x3F));
	}
	
}
int lept_parse_string(lept_context &lc, Lept_value &lv)
{
	EXPECT(lc, '\"');
	string str = *lc.json;
	string target;
	SUBSTRING(str);
	unsigned u1 = 0, u2 = 0;
	for (;;) {
		switch (str[0]) {
		case '\"':
			SUBSTRING(str);
			while (!lc.clst.empty()) {
				target += lc.clst.front();
				lc.clst.pop_front();
			}
			lv.lept_set_string(target);
			lv.lept_set_type(LEPT_STRING);
			lc.json = make_shared<const string>(str);
			return LEPT_PARSE_OK;
		case '\\':
			SUBSTRING(str);
			switch (str[0]) {
				case 'b': lc.clst.push_back('\b'); SUBSTRING(str); break;
				case 'f': lc.clst.push_back('\f'); SUBSTRING(str); break;
				case 'r': lc.clst.push_back('\r'); SUBSTRING(str); break;
				case 't': lc.clst.push_back('\t'); SUBSTRING(str); break;
				case 'n': lc.clst.push_back('\n'); SUBSTRING(str); break;
				case '\"':lc.clst.push_back('\"'); SUBSTRING(str); break;
				case '\\':lc.clst.push_back('\\'); SUBSTRING(str); break;
				case '/': lc.clst.push_back('/');  SUBSTRING(str); break;
				case 'u':
					SUBSTRING(str);
					if (!lept_parse_hex4(str, u1)) 
						return LEPT_PARSE_INVALID_UNICODE_HEX;
					if (u1 >= 0xD800 && u1 <= 0xDBFF) {
						if (str[0] != '\\')
							return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
						SUBSTRING(str);
						if (str[0] != 'u')
							return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
						SUBSTRING(str);
						if (!lept_parse_hex4(str, u2))
							return LEPT_PARSE_INVALID_UNICODE_HEX;
						if (u2 < 0xDC00 || u2 > 0xDFFF)
							return LEPT_PARSE_INVALID_UNICODE_SURROGATE;
						u1 = 0x10000 + (((u1 - 0xD800) << 10) + (u2 - 0xDC00));
					}
					lept_encode_utf8(lc, u1);
					break;
				default:
					return LEPT_PARSE_INVALID_STRING_ESCAPE;
			}
			break;
		case '\0':
			return LEPT_PARSE_MISS_QUOTATION_MARK;
		default:
			if (static_cast<unsigned int>(str[0]) < 0x20)
				return LEPT_PARSE_INVALID_STRING_CHAR;
			lc.target_string += str[0];
			lc.clst.push_back(str[0]);
			SUBSTRING(str);
		}
	}
}
int lept_parse_array(lept_context &lc, Lept_value &lv)
{
	EXPECT(lc, '[');
	string str = *lc.json;
	SUBSTRING(str);
	lc.json = make_shared<const string>(str);
	lept_parse_whitespace(lc);
	str = *lc.json; 
	vector<Lept_value> lvec;

	if (str[0] == ']') {
		SUBSTRING(str);
		lc.json = make_shared<const string>(str);
		lv.lept_set_type(LEPT_ARRAY);
		return LEPT_PARSE_OK;
	}
	for (;;) {
		Lept_value e;
		int ret = 0;
		if ((ret = lept_parse_value(lc, e)) != LEPT_PARSE_OK)
			return ret;
		lept_parse_whitespace(lc);
		string s = *lc.json;
		lvec.push_back(e);
		if (s[0] == ',') {
			SUBSTRING(s);
			lc.json = make_shared<const string>(s);
			lept_parse_whitespace(lc);
		}
		else if (s[0] == ']') {
			SUBSTRING(s);
			lc.json = make_shared<const string>(s);
			lv.lept_set_type(LEPT_ARRAY);
			lv.lept_store_to_array(lvec);
			return LEPT_PARSE_OK;
		}
		else
			return LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET;
	}
}
int lept_parse_value(lept_context &lc, Lept_value &lv)
{
	switch ((*lc.json)[0]) {
		case 'n': return lept_parse_literal(lc, lv, "null", LEPT_NULL);
		case 't': return lept_parse_literal(lc, lv, "true", LEPT_TRUE);
		case 'f': return lept_parse_literal(lc, lv, "false", LEPT_FALSE);
		case '"': return lept_parse_string(lc, lv);
		case '[': return lept_parse_array(lc, lv);
		case '\0':return LEPT_PARSE_EXPECT_VALUE;
		default: return lept_parse_number(lc, lv);
	}
}

int Lept_value::lept_parse(const string& json)
{
	lept_context lc;
	int ret = LEPT_PARSE_OK;
	assert(this != nullptr);
	lc.json = make_shared<const string>(json);
	this->type = LEPT_NULL;
	lept_parse_whitespace(lc);
	if ((ret = lept_parse_value(lc, *this)) == LEPT_PARSE_OK) {
		lept_parse_whitespace(lc);
		if (lc.json && !lc.json->empty()) {
			type = LEPT_NULL;
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
		}
	}
	return ret;
}

lept_type Lept_value::lept_get_type() const
{
	assert(this != nullptr);
	return type;
}
Lept_value& Lept_value::lept_set_type(lept_type t)
{
	assert(this != nullptr);
	type = t;
	return *this;
}
double Lept_value::lept_get_number() const
{
	assert(this != nullptr && type == LEPT_NUMBER);
	return n;
}
Lept_value& Lept_value::lept_set_number(double d)
{
	assert(this != nullptr);
	n = d;
	return *this;
}
string Lept_value::lept_get_string()const
{
	assert(this != nullptr && type == LEPT_STRING);
	return s;
}
Lept_value& Lept_value::lept_set_string(const string &str)
{
	assert(this != nullptr);
	s = str;
	return *this;
}
string::size_type Lept_value::lept_get_string_length()const
{
	assert(this != nullptr && type == LEPT_STRING);
	return s.size();
}
int Lept_value::lept_get_boolean() const
{
	assert(this != nullptr && (type == LEPT_FALSE || type == LEPT_TRUE));
	return type == LEPT_FALSE ? LEPT_FALSE : LEPT_TRUE;
}
Lept_value& Lept_value::lept_set_boolean(int b)
{
	assert(this != nullptr);
	this->type = (b ? LEPT_TRUE : LEPT_FALSE);
	return *this;
}
Lept_value& Lept_value::lept_set_null()
{
	assert(this != nullptr);
	s = "";
	n = 0.0;
	a = nullptr;
	type = LEPT_NULL;
	return *this;
}
size_t Lept_value::lept_get_array_size() const
{
	assert(this != nullptr && type == LEPT_ARRAY);
	return a->size();
}
Lept_value Lept_value::lept_get_array_element(size_t index) const 
{
	assert(this != nullptr && type == LEPT_ARRAY);
	assert(index < a->size());
	return (*a)[index];
}
void Lept_value::lept_store_to_array(const vector<Lept_value> &lvec)
{
	assert(this != nullptr);
	a = make_shared<vector<Lept_value>>(lvec);
}