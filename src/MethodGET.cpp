#include "../include/MethodGET.h"

extern const std::string SERVER_ROOT;
string MethodGET::getResponse(string url){

	if(S_ISDIR(fileStats.st_mode)){
		//jest katalogiem, wypisz pliki
	}
	else{
		std::ifstream t(filePath);
		std::stringstream buffer;
		buffer << t.rdbuf();
		string a =buffer.str();
		cout<<a<<endl;
		return a;
	}
}