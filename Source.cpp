#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include "parse.h"
#include "process.h"
#include "Join.h"
using namespace std;

int main(){

	char input_query[1000];
	int i;
	while(true){
		printf("Megatron$$$... ");
		input_query[0] = '\0';
		scanf(" %[^;]",input_query);
		getchar();
		string pipe(input_query);
		int fp,fd;
		size_t pos = pipe.find("|");
		fpos_t fp_std;
		if(pos != string::npos){
			fgetpos(stdout,&fp_std);
			fd = dup(fileno(stdout));
			input_query[pos] = '\0';
			string filename = pipe.substr(pos+1);
			fp = open(filename.c_str(),O_WRONLY);
			//cout << "fp = " << fp <<endl;
			if(fp < 0 ){
				pipe = "touch " + filename;
				system(pipe.c_str());
				int pos = 0;
				while(filename[pos] == ' ')
					pos++;
				//	cout << "ppp " << filename.substr(pos) << "  " << filename.substr(pos).size() << endl;
				fp = open(filename.substr(pos).c_str(),O_WRONLY);
			}
			//cout << fp <<endl;
			dup2(fp,1);
		}
		//	cout << input_query <<endl;
		string query(input_query);
		if(query.find("quitpls") != string::npos)
			break;
		memset(input_query,'\0',0);
		//cout << query <<endl;
		parse Obj(query);
		//cout << Obj.is_validquery() <<endl;
		if(Obj.is_validquery()){

			vector<string> cols = Obj.getselect_coloumns();
			vector<string>::iterator it;
			//for(it = cols.end() ; it > cols.begin() ;it--)
			//cout << *(it-1) << endl;
			vector<string> tables = Obj.get_tables();

			for(it = tables.end() ; it > tables.begin() ;it--){
				//cout << *(it-1) << endl;

				//for(i = 0 ; i < P1.no_attributes ; i++){
				//	cout << P1.attribute[i]  << "  " << P1.datatype[i] <<endl;
				//}
				//cout << P1.primarykey << endl;
			}
			if(tables.size() == 1){
				process P1(*(it));
				if(P1.failed == 1){
					if(pos != string::npos){
						dup2(fd,fileno(stdout));
						close(fd);
						fsetpos(stdout,&fp_std);
					}
					continue;
				}
				if(Obj.lower_myquery.find("where") != string::npos){

					vector<string> conditions = Obj.get_conditions();
					if(P1.apply_conditions(conditions[2],conditions[1],conditions[0]) == 0 ){
						cout << "Datatype Must Be SAME" <<endl;
						if(pos != string::npos){
							dup2(fd,fileno(stdout));
							close(fd);
							fsetpos(stdout,&fp_std);
						}
						continue;
					}
					P1.select(cols,Obj.dist_flag,Obj.dist_col,1);
				}
				else
					P1.select(cols,Obj.dist_flag,Obj.dist_col,10000);
			}
			else{
				//cout << "ImHEre " <<endl;
				vector<string> conditions = Obj.get_conditions();
				//cout << *(it  + 1) <<endl;
				Join J( *(it) , *(it+1),cols,conditions);
				if(pos != string::npos){
					dup2(fd,fileno(stdout));
					close(fd);
					fsetpos(stdout,&fp_std);
				}
			}
		}
		else{
			cout << "Invalid Query" <<endl;
			if(pos != string::npos){
				dup2(fd,fileno(stdout));
				close(fd);
				fsetpos(stdout,&fp_std);
			}
			continue;
		}
		if(pos != string::npos){
			dup2(fd,fileno(stdout));
			close(fd);
			fsetpos(stdout,&fp_std);
		}

	}
	return 0;
}
