#pragma once
#include "MethodGET.h"
#include "MethodHEAD.h"
#include "MethodPOST.h"

#include <string>

class MethodFactory{
public:
	MethodInterface* getMethod(string meth);
};