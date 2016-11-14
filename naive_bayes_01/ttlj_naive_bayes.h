#pragma once
#ifndef _TTLJ_NAIVE_BAYES_H_
#define _TTLJ_NAIVE_BAYES_H_
#ifndef M_PI
#define M_PI 3.141592657
#endif
#include <vector>
#include <string>
using namespace std;

typedef enum { COLOR_WHITE, COLOR_GREEN, COLOR_BLACK }melon_color;
typedef enum { ROOT_LITTLE_CURL, ROOT_CURL, ROOT_HARD }melon_root;
typedef enum { SOUND_CLEAR, SOUND_MUDDY, SOUND_BORED }melon_sound;
typedef enum { VEIN_CLEAR, VEIN_LITTLE_VAGUE, VEIN_VAGUE }melon_vein;
typedef enum { FUNICLE_PLAT, FUNICLE_LITTLE_HOLLOW, FUNICLE_HOLLOW }melon_funicle;
typedef enum { FEEL_HARD, FEEL_SOFT }melon_feel;

typedef struct melon_attribute melon_attribute;
struct melon_attribute{
	melon_color color;
	melon_root root;
	melon_sound sound;
	melon_vein vein;
	melon_funicle funicle;
	melon_feel feel;

	double density;
	double sugar;

	bool good_or_bad;
};


vector<vector<string>> input_raw_data();
vector<melon_attribute> melon_handle_raw_data();
melon_attribute melon_parse_attribute(vector<string>& vec);
melon_attribute melon_input_sample();
pair<vector<double>, vector<double>>  melon_parse_probablity();
void melon_good_or_bad();

#endif