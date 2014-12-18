#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<string.h>
#include "process.h"
using namespace std;
class Join
{
public:
	Join(string table1, string table2, vector<string> cols, vector<string> conditions);
	vector<string> get_table_col(vector<string> cols, string table);
	string get_table_con(vector<string> conditions, string table);
	~Join(void);
};

