//#include "HttpRequest.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{	
	int i = 0;
	while(i<3) {
		string* s = new string();
		cout<< *s<<endl;
		*s = "HAHHA";
		if(i==1)
			*s = "A";
		cout<< *s<<" "<<s<<endl;
		i++;
		delete s;
	}
	
	return 0;
}