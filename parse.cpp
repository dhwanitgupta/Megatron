#include "parse.h"


parse::parse(string query)
{
	myquery = query;
	int i = 0;
	int j = 0;
	while(query[i] == ' ')
		i++;

	while(query[i] != '\0'){
		myquery[j] =  query[i];
		i++;
		j++;
	}
	myquery[j] = '\0';
	lower_myquery = myquery;
	transform(lower_myquery.begin(),lower_myquery.end(),lower_myquery.begin(),::tolower);
	dist_flag = 0;
	//cout<<lower_myquery<<endl;
	//cout << myquery <<endl;
}
string parse::get_dist(string str){
	char temp[100];
	size_t pos = str.find("distinct");
	int i = pos+7;
	while(str[i] != '(')
		i++;
	i++;

	int j = 0;
	while(str[i] != ')'){
		temp[j] = str[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	string ret(temp);
	return ret;
}
int parse::check_dist(string str){
	if(str.find("distinct(") != string::npos)
		return 1;
	return 0;
}
vector<string> parse::getselect_coloumns(){

	vector<string> coloumns;
	vector<string>::iterator it;
	char getcol[1000];
	string cols;
	it = coloumns.begin();
	int i = 0;
	int j = 0;
	while(myquery[i] != ' ')
		i++;

	while(true){
		while(myquery[i] == ' ')
			i++;
		j = 0;

		while(myquery[i] != ' '){

			if(myquery[i] == ',')
				break;

			getcol[j] = myquery[i];
			i++;
			j++;
		}
		getcol[j] = '\0';
		string col(getcol);
		if(check_dist(col)){
			dist_col  = get_dist(col);
			col = dist_col;
			dist_flag = 1;
		}
		it = coloumns.insert(it,col);
		//cout << col << endl;
		while(myquery[i] == ' ')
			i++;

		if(myquery[i] != ',')
			break;
		i++;
	}
	return coloumns;
}

vector<string> parse::get_tables(){

	string tablequery;
	//string lowercase_myquery();
	size_t pos;
	vector<string> tables;
	
	if(lower_myquery.find("from") != string::npos){
		pos = lower_myquery.find("from");
		tablequery = myquery.substr(pos + 4);
	}
	else{
		return tables;
	}
	vector<string>::iterator it;
	char gettable[1000];
	string tab;
	it = tables.begin();
	int i = 0;
	int j = 0;
	while(tablequery[i] != ' ')
		i++;

	while(true){


		while(tablequery[i] == ' ')
			i++;
		j = 0;

		while(tablequery[i] != ' '){

			if(tablequery[i] == ',' || tablequery[i] == '\0')
				break;

			gettable[j] = tablequery[i];
			i++;
			j++;
		}
		gettable[j] = '\0';
		string tab(gettable);
		it = tables.insert(it,tab);
		//cout << tab << endl;
		while(tablequery[i] == ' '){
			if(tablequery[i] == '\0')
				break;
			i++;
		}
		if(tablequery[i] != ',' || tablequery[i] == '\0')
			break;
		i++;
	}
	//cout << tablequery << endl;
	return tables;
}

vector<string> parse::get_conditions(){
	string wherequery;
	size_t pos;
	vector<string> conditions;;
	
	
	if(lower_myquery.find("where") != string::npos){
		pos = lower_myquery.find("where");
		wherequery = myquery.substr(pos + 5);
		//	cout << wherequery << endl;
	}
	else{
		return conditions;
	}
	int len = 1;
	string my_operator;
	if( wherequery.find(">=") != string::npos){
		pos = wherequery.find(">=");
		my_operator = ">=";
		len = 2;
	}
	else if( wherequery.find("<=") != string::npos){
		pos = wherequery.find("<=");
		my_operator = "<=";
		len = 2;
	}
	else if ( wherequery.find("=") != string::npos){
		pos = wherequery.find("=");
		my_operator = "=";
	}
	else if(wherequery.find(">") != string::npos){
		pos = wherequery.find(">");
		my_operator = ">";
	}
	else if(wherequery.find("<") != string::npos){
		pos = wherequery.find("<");
		my_operator = "<";
	}
	int i = 0;
	int j = 0;
	char col_name[100];
	char val_col[100];
	while(wherequery[i] == ' ')
		i++;

	while(i < pos){
		if(wherequery[i] == ' ')
			break;
		col_name[j] = wherequery[i];
		i++;
		j++;
	}
	col_name[j] = '\0';
	j  = 0;
	i = pos + len;
	while(wherequery[i] == ' ')
		i++;

	while(wherequery[i] != '\0'){
		val_col[j] = wherequery[i];
		i++;
		j++;
	}
	val_col[j] = '\0';
	vector<string>::iterator it;
	it = conditions.begin();
	string col1(col_name);
	string col2(val_col);
	it = conditions.insert(it,col_name);
	it = conditions.insert(it,my_operator);
	it = conditions.insert(it,val_col);
	//cout << my_operator << " " <<  pos <<endl;
	return conditions;
}

bool  parse::is_validquery(){

	size_t pos_select;
	size_t pos_from;
	size_t pos_where;
	pos_select = lower_myquery.find("select");
	pos_from = lower_myquery.find("from");
	pos_where = lower_myquery.find("where");
	if(pos_select == string::npos || pos_from == string::npos){
		return false;
	}
	if(pos_select > pos_from){
		return false;
	}
	if(pos_where != string::npos && pos_from > pos_where)
		return false;

	return true;
}

parse::~parse(void)
{
}
