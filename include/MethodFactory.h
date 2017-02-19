#pragma once
#include "MethodGET.h"
#include <string>

class MethodFactory{
public:
	MethodInterface* getMethod(string meth);
};