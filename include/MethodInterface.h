#pragma once
#include <string>

using namespace std;

class MethodInterface{

public:
	virtual string getResponse(string url,bool isDir)=0;
};