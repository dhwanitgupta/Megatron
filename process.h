#pragma once
#include<string>
#include<iostream>
#include<stdio.h>
#include <vector>
#include<cstring>
#include <algorithm>
#include<map>

using namespace std;

class process
{
	
public:
	char attribute[100][100];
	int datatype[100];
	int primarykey;
	int no_attributes;
	char file_table[100];
	int Ids[60000];
	int failed;
	process(string table);
	int apply_conditions(string col , string op , string var);
	int check_col(string var);
	int get_col(string col);
	int valid_attribute(string ipstr,string op,string var);
	int valid_attribute_int(string ipstr,string op,string var);
	string get_str(string str);
	string trimspace(string str);
	void select(vector<string> coloumns,int dist_flag , string dist_col,int con_flag);
	int check_if(int col[100],int count);
	string get_parse_line(char buffer[1000]);
	~process(void);
};

