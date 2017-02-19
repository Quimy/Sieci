#pragma once

#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <sys/stat.h> //mode_t

using namespace std;


string modifiedSinceHeader(string url,string header);