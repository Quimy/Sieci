#include "../include/MethodFactory.h"

MethodInterface* MethodFactory::getMethod(string meth){
	if(meth=="GET"){
		return new MethodGET;
	}
	else{
		throw runtime_error(string("Not defined"));
	}
}