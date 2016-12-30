#include <string>
#include <stdexcept>
#include <iostream>
#include "Constants.h"
#include <vector>
#include <map>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<string> split(string text,string separator);

enum class Method{GET};
class HttpRequest{
	
	Method method;
	string uri;
	short major;
	short minor;
	map<string,string> extraHeaders;

	void parseFirstLine(string&);
	void parseSecondLine(string&);
	void parseRemainingLines(vector<string>);
public:
	HttpRequest(string req);
	string getResponseMessage();
	

};