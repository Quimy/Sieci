#include "../include/MethodFactory.h"

MethodInterface* MethodFactory::getMethod(string meth){
	if(meth=="GET"){
		return new MethodGET;
	}
	else if(meth=="HEAD"){
		return new MethodHEAD;
	}
	else if(meth=="POST"){
		return new MethodPOST;
	}
	else{
		return nullptr;
	}
}