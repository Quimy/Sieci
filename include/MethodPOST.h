#pragma once
#include "MethodInterface.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Constants.h"

using namespace std;

class MethodPOST: public MethodInterface{

public:
	string getResponse(string url,bool isDir);
};