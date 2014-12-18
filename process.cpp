#include "process.h"


process::process(string table)
{
	//cout << "YEEYE " <<endl;
	FILE *fp;
	char filename[100];
	char buffer[1000];
	char fields[100];
	filename[0] = '\0';
	strcat(filename,table.c_str());
	strcpy(file_table,filename);
	strcat(file_table,".csv");
	strcat(filename,".txt");
	//cout << filename <<endl;
	fp = fopen(filename,"r");
	failed = 0;
	if(fp == NULL){
		cout << "Table Doesn't Exist :D" <<endl;
		failed = 1;
		return ;
	}
	int i = 0;
	int j = 0;
	int count = 0;
	int line = 0;
	while(fgets(buffer,1000,fp)!=NULL){
		char *pch;
		//cout << buffer << endl;
		pch = strtok (buffer,"|");
		count = 0;
		while (pch != NULL){
			//printf ("%s\n",pch);
			i = 0;
			j = 0;
			while(pch[i] == ' '){
				i++;
			}
			while(pch[i] != '\0'){
				if(pch[i] == ' ')
					break;
				fields[j] = pch[i];
				j++;
				i++;
			}
			fields[j] = '\0';
			//cout << fields << " " << count << endl;
			if(count == 0){
				strcpy(attribute[line],fields);

			}
			else if(count == 1){
				if(fields[0] == 'i' || fields[0] == 'I')
					datatype[line] = 1;
				else
					datatype[line] = 0;
			}
			else if(count == 3){
				if(strcmp(fields,"PRI") == 0)
					primarykey = line;
			}
			count++;
			pch = strtok (NULL, "|");
		}
		line++;
	}
	no_attributes = line;
	fclose(fp);
}
int process::check_col(string var){
	int i;
	for(i = 0; i < no_attributes ; i++){
		if(strcmp(attribute[i],var.c_str()) ==0)
			return 1;
	}
	return 0;
}
int process::get_col(string col){
	for(int i = 0 ; i < no_attributes;i++){
		//cout << attribute[i] << " " << col.c_str() << endl;
		//cout << strlen(attribute[i]) << " " << strlen(col.c_str()) <<endl;
		//cout << attribute[i] << "  " << col << endl;
		//cout << trimspace(attribute[i]).size() << "  " << col.size() << endl;
		if(strcmp(attribute[i],col.c_str()) == 0)
			return i;
	}
	return -1;
}
int process::valid_attribute_int(string ipstr,string op,string var){
	//cout << "TOP " << ipstr << " " << var <<endl;
	int num2 = atoi(get_str(var).c_str());
	char temp[100];
	int i = 0;
	while(ipstr[i] == '"'){
		i++;
	}
	int j = 0;
	while(ipstr[i] != '"'){
		if(ipstr[i] == '\0')
			break;
		temp[j] = ipstr[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	int num1 = atoi(temp);
	//cout << num1  << " " << num2 <<endl;
	if(op.compare("=") == 0){
		if(num1 == num2)
			return 1;
		else
			return 0;
	}
	if(op.compare(">=") == 0){
		if(num1 >= num2)
			return 1;
		else
			return 0;
	}
	if(op.compare("<=") == 0){
		if( num1 <= num2)
			return 1;
		else
			return 0;
	}
	if(op.compare(">") == 0){
		if(num1	> num2)
			return 1;
		else
			return 0;
	}
	if(op.compare("<") == 0){
		if(num1	< num2)
			return 1;
		else
			return 0;
	}
}
string process::get_str(string str){
	char temp[100];
	int i = 0;
	while(str[i] == ' ')
		i++;
	while(str[i] != '"'){
		if(str[i] == '\0'){
			while(str[i-1] == ' ')
				i--;
			str[i] = '\0';
			return str;
		}
		i++;

	}
	int  j = 0;
	i++;
	//cout << "i = " << i << endl;
	while(str[i] != '"'){
		if(str[i] == '\0')
			break;
		temp[j] = str[i];
		i++;
		j++;
		//cout << i << endl;
	}
	temp[j] = '\0';
	while(temp[j-1] == ' ')
		j--;
	temp[j] = '\0';
	//cout << "temp = " << temp << endl;
	string ret(temp);
	return ret;

}
string process::trimspace(string str){
	char temp[100];
	int i = 0;
	while(str[i] == ' ')
		i++;

	int j = 0;
	while(str[i] != ' ' && str[i] != '\0' && str[i] != '\n'){
		temp[j] = str[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	while(temp[j-1] == ' ')
		j--;
	temp[j] = '\0';
	//if(temp[j-1] == '\n' || temp[j-1] == ' ' )
		//cout << "yes" <<endl;
	//cout << temp[j-1] <<endl;
	string ret(temp);
	return ret;
}
int process::valid_attribute(string ipstr,string op,string var){

	ipstr = get_str(ipstr);
	var = get_str(var);
	ipstr = trimspace(ipstr);
	var = trimspace(var);
	//cout << "zz = " << ipstr.size()  <<  " " <<var[2] <<endl;

	if(op.compare("=") == 0){
		if(ipstr.compare(var) == 0)
			return 1;
		else
			return 0;
	}
	if(op.compare(">=") == 0){
		if(ipstr.compare(var)	>= 0)
			return 1;
		else
			return 0;
	}
	if(op.compare("<=") == 0){
		if(ipstr.compare(var)	<= 0)
			return 1;
		else
			return 0;
	}
	if(op.compare(">") == 0){
		if(ipstr.compare(var)	> 0)
			return 1;
		else
			return 0;
	}
	if(op.compare("<") == 0){
		if(ipstr.compare(var)	< 0)
			return 1;
		else
			return 0;
	}
}
int process::apply_conditions(string col, string op , string var){

	//cout <<" zz " <<  col << " " << op << " " <<var<<endl;
	int flag_col = check_col(var);
	int count = 0;
	int test = 0;
	if(flag_col == 0){
		int col_num = get_col(col);
		//cout << "num " << col_num << endl;
		FILE *fp = fopen(file_table,"r");
		char buffer[1000];
		int line = 0;
		while(fgets(buffer,1000,fp)!=NULL){
			//cout << "GG " << " " <<datatype[0] <<endl;
			if(line == 0){
				line++;
				continue;
			}
			char *pch;
			pch = strtok (buffer,",");
			count = 0;
			while (pch != NULL){
				//cout << col_num << " " << count<<endl;
				if(count == col_num){
					//cout << pch <<endl;
					if(datatype[col_num] == 0 && valid_attribute(pch,op,var)  ){
						Ids[line] = 1;
						test++;
						//cout << pch << endl;
					}
					else if(datatype[col_num] == 1 && valid_attribute_int(pch,op,var)){
				//		cout << "DDD " <<endl;
						Ids[line] = 1;
						test++;
					}
					else{
						Ids[line] = 0;
					}
				}
				count++;
				pch = strtok (NULL, ",");
			}
			line++;

		}
			fclose(fp);
	}
	else{
		int col1_num = get_col(col);
		int col2_num = get_col(var);
		if(datatype[col1_num] != datatype[col2_num]){
			return 0;
		}
		else{
			//cout << "num " << col_num << endl;
			FILE *fp = fopen(file_table,"r");
			char buffer[1000];
			int line = 0;
			while(fgets(buffer,1000,fp)!=NULL){
				if(line == 0){
					line++;
					continue;
				}
				char *pch;
				char *val1 ,*val2;
				pch = strtok (buffer,",");
				count = 0;
				while (pch != NULL){
					if(count == col1_num){
						val1 = pch;
					}
					else if(count == col2_num)
						val2 = pch;
					count++;
					pch = strtok (NULL, ",");
				}
				//	cout << "vals " << val1  << " " << val2 <<endl;
				if(valid_attribute(val1,op,val2)){
					Ids[line] = 1;
				//cout << val1 << "  " << val2 << endl;
					test++;
				}
				else
					Ids[line]  = 0;
				line++;
			}
				fclose(fp);
		}
	}
	return 1;
	//cout << "NO OF ROWS SELECTED : " << test << endl;
}
int process::check_if(int cols[100],int count){
	int i = 0;
	for(i=0;i<no_attributes;i++)
		if(cols[i] == count)
			return 1;

	return 0;
}
string process::get_parse_line(char buffer[1000]){
	int i = 1;
	int j = 0;
	char ret[1000];
	//cout << buffer <<endl;
	while(buffer[i] != '\0'){
		if(buffer[i] == '"' && buffer[i+1] == ',' && buffer[i+2] == '"'){
			ret[j] = '@';
			i = i + 2;
		}
		else
			ret[j] = buffer[i];
		j++;
		i++;
	}
	while(ret[j] != '"')
		j--;
	ret[j] = '\0';
	//cout << "Z z " << ret <<endl;
	string temp(ret);
	return temp;
}
void process::select(vector<string> coloumns,int dist_flag , string dist_col,int con_flag){
	int col_number[100];
	int i = 0;
	int flag = 0;
	map<string,int> distincts;
	pair<std::map<string,int>::iterator,bool> ret;
	char display_buffer[10000];
	int dist_col_no;
	//cout << "ASDSA "<<  dist_flag << " " << dist_col << endl;
	if(dist_flag == 1){
		dist_col_no = get_col(dist_col);
		
	}
	vector<string>::iterator it;
	for(i=0;i<no_attributes;i++)
		col_number[i] = - 2;
	i = 0;
	display_buffer[0] = '\0';
	for(it = coloumns.begin() ; it < coloumns.end() ;it++){
		string temp(*(it));
		if( temp.compare("*")== 0){
			flag = 1;
			for(i=0;i<no_attributes;i++){
				strcat(display_buffer,attribute[i]);
				strcat(display_buffer,"\t");
			}
			break;
		}
		col_number[i++] = get_col(temp);
		strcat(display_buffer,temp.c_str());
		strcat(display_buffer,"\t");
		if( col_number[i-1] == -1){
			cout << "No coloumn Name " << temp << endl;
			return;
		}
	//	cout << "col " << temp << " " <<col_number[i-1] << endl;
	}

	FILE *fp = fopen(file_table,"r");
	char buffer[10000];
	int line = 0;
//	cout << file_table <<endl;
	string temp;
	while(fgets(buffer,1000,fp)!=NULL){
		if(line == 0 && flag == 1){
			cout << display_buffer << endl;
		}
		if(Ids[line]  == 0 && con_flag != 10000){
			line++;
			continue;
		}
		temp = get_parse_line(buffer);
		strcpy(buffer,temp.c_str());
		char *pch;
		char *val1 ,*val2;
		pch = strtok (buffer,"@");
		int count = 0;
		int show = 1;
		display_buffer[0] ='\0';
		while (pch != NULL){
			if(count == dist_col_no){
				 ret = distincts.insert ( std::pair<string,int>(pch,5) );
				 if(ret.second == false){
					 show = 0;
				 }
			}
			if(check_if(col_number,count) && flag == 0){
				//cout << pch << "\t";
				strcat(display_buffer,pch);
				strcat(display_buffer,"\t");
			}
			else if(flag == 1){
				//cout << pch << "\t";
				strcat(display_buffer,pch);	
				strcat(display_buffer,"\t");
			}
			count++;
			pch = strtok (NULL, "@");
		}
		if(show == 1){
			//cout << temp <<endl;
			cout <<   display_buffer <<endl;
			
		}
		line++;
		//break;
	}
}
process::~process(void)
{
}
