#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <iomanip>
#include "ttlj_naive_bayes.h"
using namespace std;

static void test_parse_input_data()
{
	vector<vector<string>> vv = input_raw_data();

	for (size_t i = 0; i < vv.size(); ++i) {
		for (size_t j = 0; j < vv[i].size(); ++j) {
			cout << vv[i][j] << " ";
		}
		cout << endl;
	}
}

static void test_parse_data()
{
	vector<melon_attribute> melon = melon_handle_raw_data();

	for (size_t i = 0; i < melon.size(); ++i) {
		cout <<fixed<< setprecision(3) << setw(0) << melon[i].color << " " << melon[i].root << " " << melon[i].sound << " " << melon[i].vein << " "
			<< melon[i].funicle << " " << melon[i].feel << " " << melon[i].density << " " << melon[i].sugar << " "
			<< melon[i].good_or_bad << endl;
	}
}

void test_melon_probablity()
{
	pair<vector<double>, vector<double>> pvv = melon_parse_probablity();
	auto first = pvv.first;
	cout << "probablity of good melon's attribute: " << endl;
	for (auto &i : first)
		cout << i << " ";
	cout << endl;

	auto second = pvv.second;
	cout << "probablity of bad melon's attribute: " << endl;
	for (auto &i : second)
		cout << i << " ";
	cout << '\n';
}

 void test()
{
	 test_parse_input_data();
	 test_parse_data();
	 test_melon_probablity();
	 melon_good_or_bad();
}

int main()
{
	test();

	
}
	