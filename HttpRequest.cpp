//#include "HttpRequest.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;
void func(int a){
	cout<<"OLA"<<&a<<endl;
}
struct tmp{
	int pole;
};
int main(int argc, char const *argv[])
{	
	vector<int*> wsk;
	int i = 0;
	int* s;
	while(i<3) {
		tmp* x = new tmp();
		s = new int;
		cout<< &x->pole<<endl;
		if(i==0)
			*s = 1;
		if(i==1)
			*s = 2;
		cout<< *s<<" "<<s<<endl;
		wsk.push_back(new int);
		func(*s);
		i++;
		delete s;
	}
	for(int i =0;i<wsk.size();i++){
		cout<<wsk[i]<<endl;
	}
	for(int i =0;i<wsk.size();i++){
		cout<<*wsk[i]<<endl;
	}
	*wsk[1]=4;
		for(int i =0;i<wsk.size();i++){
		cout<<*wsk[i]<<endl;
	}
	return 0;
}