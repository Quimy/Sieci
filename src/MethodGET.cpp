#include "../include/MethodGET.h"

extern const std::string SERVER_ROOT;
string MethodGET::getResponse(string url,bool isDir){

	string filePath(SERVER_ROOT+url);
	if(isDir){
		DIR *dpdf;
		struct dirent *epdf;
		string result = "Lista plikow w katalogu:\r\n";
		dpdf = opendir(filePath.c_str());
		if (dpdf != NULL){
		   while (epdf = readdir(dpdf)){
		   	string nazwa{epdf->d_name};
		   	if((nazwa.size()==1 && nazwa[0]=='.') || (nazwa.size()==2 && nazwa[0]=='.' && nazwa[1]=='.' )){
		   		continue;
		   	}
		      result+=nazwa;
		      result+="\r\n";
		   }
		closedir(dpdf);
		}
		return result;
	}
	else{
		std::ifstream t(filePath);
		std::stringstream buffer;
		buffer << t.rdbuf();
		string a =buffer.str();
		return a;
	}
}