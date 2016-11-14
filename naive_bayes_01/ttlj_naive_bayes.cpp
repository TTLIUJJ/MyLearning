#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cassert>
#include <utility>
#include <cmath>
#include "ttlj_naive_bayes.h"
using namespace std;

static  void melon_parse_color(melon_attribute& melon, vector<string>& vec)
{
	if (vec[0] == "Ç³°×")
		melon.color = COLOR_WHITE;
	else if (vec[1] == "ÇàÂÌ")
		melon.color = COLOR_GREEN;
	else
		melon.color = COLOR_BLACK;
}

static  void melon_parse_root(melon_attribute& melon, vector<string>& vec)
{
	if (vec[1] == "ÉÔòé")
		melon.root = ROOT_LITTLE_CURL;
	else if (vec[1] == "òéËõ")
		melon.root = ROOT_CURL;
	else
		melon.root = ROOT_HARD;
}

static  void melon_parse_sound(melon_attribute& melon, vector<string>& vec)
{
	if (vec[2] == "Çå´à")
		melon.sound = SOUND_CLEAR;
	else if (vec[2] == "×ÇÏì")
		melon.sound = SOUND_MUDDY;
	else
		melon.sound = SOUND_BORED;
}

static  void melon_parse_vein(melon_attribute& melon, vector<string>& vec)
{
	if (vec[3] == "ÇåÎú")
		melon.vein = VEIN_CLEAR;
	else if (vec[3] == "ÉÔºý")
		melon.vein = VEIN_LITTLE_VAGUE;
	else
		melon.vein = VEIN_VAGUE;
}

static void melon_parse_funicle(melon_attribute& melon, vector<string>& vec)
{
	if (vec[4] == "Æ½Ì¹")
		melon.funicle = FUNICLE_PLAT;
	else if (vec[4] == "ÉÔ°¼")
		melon.funicle = FUNICLE_LITTLE_HOLLOW;
	else
		melon.funicle = FUNICLE_HOLLOW;
}

static  void melon_parse_feel(melon_attribute& melon, vector<string>& vec)
{
	melon.feel = (vec[5] == "Ó²»¬") ? FEEL_HARD : FEEL_SOFT;
}

static void melon_parse_proportion(melon_attribute& melon, vector<string>& vec)
{
	melon.density = atof(vec[6].c_str());
	melon.sugar = atof(vec[7].c_str());
}

static void melon_parse_whether(melon_attribute& melon, vector<string>& vec)
{
	melon.good_or_bad = (vec[8] == "ÊÇ") ? true : false;
}

static melon_attribute melon_input_sample()
{
	vector<string> input;
	melon_attribute melon;
	string data;

	while (cin >> data)
		input.push_back(data);
	melon = melon_parse_attribute(input);

	return melon;
}

static double avriance_function(const double& average, const vector<melon_attribute>& vec_melon, const size_t& n, const bool& b)
{
	size_t size = vec_melon.size();
	int cnt = 0;
	double total = 0;

	for (size_t i = 0; i < size; ++i) {
		if (n == 6) {
			if (vec_melon[i].good_or_bad == b) {
				total += ((average - vec_melon[i].density)*(average - vec_melon[i].density));
				++cnt;
			}
		}
		else if (n == 7) {
			if (vec_melon[i].good_or_bad == b) {
				total+= ((average - vec_melon[i].sugar)*(average - vec_melon[i].sugar));
				++cnt;
			}
		}
	}
	assert(cnt != 0);

	return total / cnt;
}

static inline
double gauss_function_probablity(const double& x, const double& average, const double& variance)
{
	double ret = (1 / sqrt(2 * M_PI*variance))*(exp(-((x - average)*(x - average)) / (2*variance)));

	return ret;
}

static pair<vector<double>, vector<double>>
melon_attribute_probablity(const melon_attribute& melon, const vector<melon_attribute>& vec_melon)
{
	double melon_good_cnt = 0;
	double melon_bad_cnt = 0;
	double color_good_cnt = 0, root_good_cnt = 0, sound_good_cnt = 0, vein_good_cnt = 0, funicle_good_cnt = 0, feel_good_cnt = 0;
	double color_bad_cnt = 0, root_bad_cnt = 0, sound_bad_cnt = 0, vein_bad_cnt = 0, funicle_bad_cnt = 0, feel_bad_cnt = 0;
	double density_good_total = 0, density_bad_total = 0;
	double sugar_good_total = 0, sugar_bad_total = 0;
	size_t size = vec_melon.size();
	   
	for (size_t i = 0; i < size; ++i) {
		melon_attribute temp = vec_melon[i];
		if (temp.good_or_bad == true) {
			++melon_good_cnt;
			if (melon.color == temp.color)
				++color_good_cnt;
			if (melon.root == temp.root)
				++root_good_cnt;
			if (melon.sound == temp.sound)
				++sound_good_cnt;
			if (melon.vein == temp.vein)
				++vein_good_cnt;
			if (melon.funicle == temp.funicle)
				++funicle_good_cnt;
			if (melon.feel == temp.feel)
				++feel_good_cnt;
			density_good_total += temp.density;
			sugar_good_total += temp.sugar;
		}
		else {
			++melon_bad_cnt;
			if (melon.color == temp.color)
				++color_bad_cnt;
			if (melon.root == temp.root)
				++root_bad_cnt;
			if (melon.sound == temp.sound)
				++sound_bad_cnt;
			if (melon.vein == temp.vein)
				++vein_bad_cnt;
			if (melon.funicle == temp.funicle)
				++funicle_bad_cnt;
			if (melon.feel == temp.feel)
				++feel_bad_cnt;
			density_bad_total += temp.density;
			sugar_bad_total += temp.sugar;
		}
	}
	double density_good_average = density_good_total / melon_good_cnt;
	double density_bad_average = density_bad_total / melon_bad_cnt;
	double sugar_good_average = sugar_good_total / melon_good_cnt;
	double sugar_bad_average = sugar_bad_total / melon_bad_cnt;

	double density_good_variance = avriance_function(density_good_average, vec_melon, 6, true);
	double density_bad_variance = avriance_function(density_bad_average, vec_melon, 6, false);
	double sugar_good_variance = avriance_function(sugar_good_average, vec_melon, 7, true);
	double sugar_bad_variance = avriance_function(sugar_bad_average, vec_melon, 7, false);

	double density_good_pobablity = gauss_function_probablity(melon.density, density_good_average, density_good_variance);
	double density_bad_probablity = gauss_function_probablity(melon.density, density_bad_average, density_bad_variance);
	double sugar_good_probablity = gauss_function_probablity(melon.sugar, sugar_good_average, sugar_good_variance);
	double sugar_bad_probablity = gauss_function_probablity(melon.sugar, sugar_bad_average, sugar_bad_variance);

	vector<double> attribute_good_probablity{ color_good_cnt / melon_good_cnt,
											root_good_cnt / melon_good_cnt,
											sound_good_cnt / melon_good_cnt,
											vein_good_cnt / melon_good_cnt,
											funicle_good_cnt / melon_good_cnt,
											feel_good_cnt / melon_good_cnt,
											density_good_pobablity,
											sugar_good_probablity
	};
	vector<double> attribute_bad_probablity{ color_bad_cnt / melon_bad_cnt,
											root_bad_cnt / melon_bad_cnt,
											sound_bad_cnt / melon_bad_cnt,
											vein_bad_cnt / melon_bad_cnt,
											funicle_bad_cnt / melon_bad_cnt,
											feel_bad_cnt / melon_bad_cnt,
											density_bad_probablity,
											sugar_bad_probablity
	};

	return make_pair(attribute_good_probablity, attribute_bad_probablity);
}


melon_attribute melon_parse_attribute(vector<string>& vec)
{
	melon_attribute melon;
	for (size_t i = 0; i < vec.size(); ++i) {
		switch (i) {
			case 0:	melon_parse_color(melon, vec); break;
			case 1: melon_parse_root(melon, vec); break;
			case 2: melon_parse_sound(melon, vec); break;
			case 3: melon_parse_vein(melon, vec); break;
			case 4: melon_parse_funicle(melon, vec); break;
			case 5:	melon_parse_feel(melon, vec); break;
			case 6:
			case 7: melon_parse_proportion(melon, vec); break;
			default:melon_parse_whether(melon, vec); break;
		}
	}

	return melon;
}

vector<vector<string>> input_raw_data()
{
	vector<vector<string>> vv;
	ifstream input("data.txt");
	string line;

	while (getline(input, line)) {
		vector<string> v;
		string word;
		istringstream recode(line);
		while (recode >> word)
			v.push_back(word);
		vv.push_back(v);
	}

	return vv;
}

vector<melon_attribute> melon_handle_raw_data()
{
	vector<vector<string>> &raw_data = input_raw_data();
	vector<melon_attribute> melon_attri;

	for (size_t i = 0; i < raw_data.size(); ++i) {
		vector<string> v = raw_data[i];
		melon_attribute melon = melon_parse_attribute(v);
		melon_attri.push_back(melon);
	}
	assert(melon_attri.size() == raw_data.size());

	return melon_attri;
}

pair<vector<double>, vector<double>> pvv;
pair<vector<double>, vector<double>> melon_parse_probablity()
{
	melon_attribute &melon = melon_input_sample();
	vector<melon_attribute> &vec_melon = melon_handle_raw_data();
	pvv = melon_attribute_probablity(melon, vec_melon);

	return pvv;
}


void melon_good_or_bad()
{

	double melon_good_probablity = 1;
	double melon_bad_probablity = 1;

	auto first = pvv.first;
	for (auto& i : first)
		melon_good_probablity *= i;

	auto second = pvv.second;
	for (auto& i : second)
		melon_bad_probablity *= i;

	cout << "ºÃ¹ÏµÄ¸ÅÂÊ£º " << melon_good_probablity << endl;
	cout << "»µ¹ÏµÄ¸ÅÂÊ£º " << melon_bad_probablity << endl;

	bool b = (melon_good_probablity > melon_bad_probablity) ? true : false;
	if (b)
		cout << "ÕâÊÇ¸öºÃ¹Ï°¡" << endl;
	else
		cout << "ÕâÊÇ¸ö»µ¹Ï°¡" << endl;
}
