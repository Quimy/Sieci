#pragma once
#include <string>

using namespace std;

class MethodInterface{

public:
	virtual string getResponse(string url)=0;
};