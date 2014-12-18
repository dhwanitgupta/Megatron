#pragma once
#include<string>
#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
class parse
{

public:
	string myquery;
	string dist_col;
	int dist_flag;
	string lower_myquery;
	parse(string query);
	~parse(void);
	bool is_validquery();
	int check_dist(string str);
	string get_dist(string str);
	vector<string> getselect_coloumns();
	vector<string> get_tables();
	vector<string> get_conditions();
};

