#pragma once

#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <sys/stat.h> //mode_t

#include "SendMessageException.h"

using namespace std;


string modifiedSinceHeader(const time_t mTime,const string header);
void userAgentHeader(const string ua);
void refererHeader(const string ua);
void fromHeader(const string ua);