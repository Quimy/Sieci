#include <string>
#include <iostream>
#include <vector>
#include <sys/stat.h>
using namespace std;

vector<string> split(string text,string separator){
	vector<string> result;
	size_t x {0};
	for (auto i {text.find(separator)}; i != string::npos; i=text.find(separator,x)){
		string tmp{text.substr(x,i-x)};
		x = i+separator.size();
		if(tmp.size() == 0) continue;
		result.push_back(tmp);
	}
	if(x != text.size()){
		string tmp = text.substr(x,string::npos);
		if(tmp.size()!=0)
			result.push_back(tmp);
	}
	return result;
}
int main(int argc, char const *argv[])
{
	string a{"abdhhefghhabchhhhhhhh"};
	vector<string> result{split(a,"hh")};
	for(auto x: result){
		cout<<x<<endl;
	}
	return 0;
}