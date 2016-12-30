#include "HttpRequest.h"

extern const int REQUEST_BUFFER_SIZE;
extern const int URL_MAX_SIZE;
extern const int METHOD_NAME_MAX_SIZE;
extern const string SERVER_ROOT;

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

HttpRequest::HttpRequest(string req){
	cout<< "Message size: "<<req.size()<<endl;
	if(req.size() == REQUEST_BUFFER_SIZE)
		throw runtime_error(string("Request too long"));
	if(req.size() < 2)
		throw runtime_error(string("Request too short"));
	cout<<req;
	vector<string> splitted_msg = split(req,"\r\n");
	cout<<"Number of rows: "<<splitted_msg.size()<<endl;
	if(splitted_msg.size()<1)
		throw runtime_error(string("Request wrong format."));

	parseFirstLine(splitted_msg[0]);
	cout<<minor<<major<<endl;

	if(req.size()>1){
		parseRemainingLines(vector<string>(splitted_msg.begin()+1,splitted_msg.end()));
	}
	for(auto x: extraHeaders){
		cout<<x.first<<"=>"<<x.second<<endl;
	}
}
void HttpRequest::parseFirstLine(string& s){
	char met[METHOD_NAME_MAX_SIZE],ur[URL_MAX_SIZE];
	auto err = sscanf(s.c_str(),"%s %s HTTP/%hd.%hd",met,ur,&major,&minor);
	if(err != 4)
		throw runtime_error(string("First line is not valid"));
	string meth(met);
	if(meth=="GET")
		method = Method::GET;
	else
		throw runtime_error(string("Method name is not valid"));
	
	uri = string(ur);

}
void HttpRequest::parseRemainingLines(vector<string> vs){
	char tmp1[URL_MAX_SIZE],tmp2[URL_MAX_SIZE];
	for (auto i = vs.begin(); i < vs.end(); ++i){
		if((*i).size()==0)continue;
		memset(&tmp1, 0, URL_MAX_SIZE);
		memset(&tmp2, 0, URL_MAX_SIZE);
		auto err = sscanf((*i).c_str(),"%s %s",tmp1,tmp2);
		if(err!=2)
			throw runtime_error(string("Extra headers are not valid"));
		string x = tmp1;
		extraHeaders.insert(pair<string,string>(string(x.begin(),x.end()-1),string(tmp2)));

	}
}
string HttpRequest::getResponseMessage(){
	
}
