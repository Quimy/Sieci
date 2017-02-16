#include <string>
#include <stdexcept>
#include <iostream>
#include "Constants.h"
#include <vector>
#include <map>
#include <string.h>
#include "HttpResponse.h"
#include <stdio.h>
#include <stdlib.h>

#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;

vector<string> split(string text,string separator);

enum class Method{GET};
class HttpRequest{
	
	string method;
	string uri;
	char major;
	char minor;
	map<string,string> extraHeaders;

	vector<string> acceptedMethods;

	void parseFirstLine(string&);
	void parseSecondLine(string&);
	void parseRemainingLines(vector<string>);
public:
	HttpRequest(string req);
	string getResponseMessage();
	

};