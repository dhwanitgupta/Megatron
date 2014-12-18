#include "Join.h"


Join::Join(string table1 , string table2 ,vector<string> col , vector<string> conditions)
{
	//cout << "HERE"<<endl;
	vector<string> t1_col = get_table_col(col , table1);
	vector<string> t2_col = get_table_col(col,table2);
	string t1_cond = get_table_con(conditions,table1);
	string t2_cond = get_table_con(conditions,table2);
	vector<string>::iterator it;
	/*for(it = t1_col.begin() ; it < t1_col.end() ;it++)
	cout << *(it) << endl;
	cout<<t1_cond<<endl;
	for(it = t2_col.begin() ; it < t2_col.end() ;it++)
	cout << *(it) << endl;
	cout << t2_cond << endl;*/

	//cout << table1 << " " << table2 << endl;
	process p1(table1);
	process p2(table2);
	int t1_cond_col = p1.get_col(t1_cond);
	int t2_cond_col = p2.get_col(t2_cond);
	int sel_col1[100];
	int sel_col2[100];
	int i;
	char fields[1000];
	fields[0] = '\0';
	string op = conditions[1];
	int j;
	for(i= 0 ;i < p1.no_attributes;i++)
		sel_col1[i] = -1;
	for(i= 0 ;i < p2.no_attributes;i++)
		sel_col2[i] = -1;
	if(col[0].compare("*" ) != 0){
		for(i = 0 ; i < t1_col.size() ; i++){
			sel_col1[i] = p1.get_col(t1_col[i]);
			//cout << t1_col[i] << " ";
		}
		//cout <<endl;
		for(i=0;i<t2_col.size();i++){
			sel_col2[i] = p2.get_col(t2_col[i]);
			//cout << t2_col[i] <<endl;
		}
		//cout << endl;
	}
	else{
		for(i = 0 ; i < p1.no_attributes ; i++){
			sel_col1[i] = p1.get_col(p1.attribute[i]);
			//cout << sel_col1[i] <<endl;
			//printf("%d \n",sel_col1[i]);
		}
		for(i=0;i<p2.no_attributes;i++)
			sel_col2[i] = p2.get_col(p2.attribute[i]);
	}
	for(i=0 ; i < p1.no_attributes ; i++){
		if(p1.check_if(sel_col1,i)){
			strcat(fields,table1.c_str());
			strcat(fields,".");
			strcat(fields,p1.attribute[i]);
			strcat(fields,"\t");
		}
	}
	for(i=0 ; i < p2.no_attributes ; i++){
		if(p2.check_if(sel_col1,i)){
			strcat(fields,table2.c_str());
			strcat(fields,".");
			strcat(fields,p2.attribute[i]);
			strcat(fields,"\t");
		}
	}
	FILE *f1 = fopen(p1.file_table,"r");
	FILE *f2 = fopen(p2.file_table,"r");
	char buffer1[1000] , buffer2[1000];
	char display_buffer1[1000] , display_buffer2[1000];
	vector<string> buff;
	it = buff.begin();
	int count1 , count2;
	int show = 0;
	int line1 = 0 ; 
	int temp = 0;
	int line2 = 0;
	string t1 , t2;
	while(fgets(buffer1,1000,f1)!=NULL){
		if(line1 == 0 ){
			line1 = 1;
			cout << fields <<endl;
			continue;
		}
		show = 0;
		
		display_buffer1[0] = '\0';
		count1 = 0;
		char *pch1;
		char *end1;
		t1 = p1.get_parse_line(buffer1);
		strcpy(buffer1,t1.c_str());
		pch1 = strtok_r(buffer1,"@",&end1);
		j = 0;
		while (pch1 != NULL){
			//printf("d_count %d temp %d\n",count1,temp);
			if(p1.check_if(sel_col1,count1)){
				//	cout << "II " <<endl;
				//printf("pch1  %s count %d \n",pch1,count1);
				strcat(display_buffer1,p1.get_str(pch1).c_str());
				strcat(display_buffer1,"\t");
				//printf("displ %s\n",display_buffer1);
			}
			//printf("d1_count %d\n",count1);
			if(count1 == t1_cond_col){
				line2 = 0;
				while(fgets(buffer2,1000,f2) != NULL){
					if(line2 == 0){
						line2 = 1;
						continue;
					}
					t2 = p1.get_parse_line(buffer2);
					strcpy(buffer2,t2.c_str());
					//display_buffer2[0] = '\0';
					char *pch2;
					char *end2;
					count2 = 0;
					int show2= 0;
					pch2 = strtok_r (buffer2,"@",&end2);
					display_buffer2[0] = '\0';
					while(pch2 != NULL){

						if(p2.check_if(sel_col2, count2)){
							//cout << "INNN " <<endl;
							strcat(display_buffer2,p1.get_str(pch2).c_str());
							strcat(display_buffer2,"\t");
							//cout << j << endl;
						}
						if(count2 == t2_cond_col){
							//	cout <<"OP = " << op << "  " << pch1 << "  " << pch2;
							if(p1.datatype[count1] == 1 && p1.valid_attribute_int(pch1,op,pch2)){
								//cout <<"OP = " << op << "  " << pch1 << "  " << pch2 <<endl;
								show = 1;
								show2 = 1;
							}
							else if(p1.datatype[count1] == 0 && p1.valid_attribute(pch2,op,pch1)){
								show = 1;
								show2 = 1;
							}
						}
						count2++;
						pch2 = strtok_r(NULL,"@",&end2);
					}
					if(show2 == 1){
						string pushstr(display_buffer2);
						it = buff.insert(it,pushstr);
						j++;
					}
					//cout << show <<endl;
				}
			}
			count1++;
			pch1 = strtok_r (NULL, "@",&end1);
			rewind(f2);
		}
		if(j > 0){
			it = buff.begin();
			for(it= buff.begin();it<buff.end();it++){
				//cout<< display_buffer1 << " lol " << display_buffer2[i]<<endl;
				string temp(*it);
				cout << display_buffer1 << temp << endl;
				//printf("%s %s\n",display_buffer1,temp);
			}
		}
	}
	fclose(f1);
	fclose(f2);
	//cout << "Next " << endl;
}
string Join::get_table_con(vector<string> conditions , string table){
	size_t pos;
	unsigned i;
	for(i = 0 ; i < conditions.size() ; i++){
		//string temp(*it);
		pos = conditions[i].find(".");
		if(conditions[i].find(table) != string::npos && pos  != string::npos)
			return conditions[i].substr(pos+1);
	}
}
vector<string> Join::get_table_col(vector<string> col,string table){
	vector<string> temp;
	vector<string>::iterator it;
	size_t pos;
	unsigned i;
	it = temp.begin();
	for(i = 0 ; i < col.size() ; i++){
		//string temp(*it);
		pos = col[i].find(".");
		if(col[i].find(table) != string::npos && pos  != string::npos){
			//temp[i] = temp[i].substr(pos+1);
			it = temp.insert(it,col[i].substr(pos+1));
			//cout << col[i] << endl;
			//*(it) = temp.substr(pos+1);
			//cout << *(it) << endl;
		}
	}
	return temp;
}

Join::~Join(void)
{
}
