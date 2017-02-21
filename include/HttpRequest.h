#pragma once
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
#include <ctime>
#include <iomanip>
#include <sys/stat.h> //mode_t

#include <iomanip>
#include <ctime>

#include "MethodFactory.h"
#include "HeaderInterpreters.h"
#include "SendMessageException.h"
using namespace std;

vector<string> split(string text,string separator);

class HttpRequest{
	
	string methodName;
	string uri;
	char major;
	char minor;
	map<string,string> extraHeaders;
	struct stat fileStats;
	string body;

	void parseFirstLine(string&);
	void parseSecondLine(string&);
	void parseRemainingLines(vector<string>);
	void parseHeader(string& s);
	string interpretHeaders();
	string generateHeaders();
public:
	HttpRequest(string req);
	string getResponseMessage();
	int isBody();
	

};