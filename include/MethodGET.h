#pragma once
#include "MethodInterface.h"

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#include <sys/stat.h> //mode_t
#include <dirent.h>

#include "Constants.h"

using namespace std;

class MethodGET:public MethodInterface{

public:
	string getResponse(string url,bool isDir);
};