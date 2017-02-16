#include "../include/HttpRequest.h"

extern const int REQUEST_MAX_BUFFER_SIZE;
extern const int REQUEST_MIN_BUFFER_SIZE;
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

HttpRequest::HttpRequest(string req):acceptedMethods{"GET"}{
	cout<< "Message size: "<<req.size()<<endl;
	if(req.size() > REQUEST_BUFFER_SIZE || req.size() < 2)
		throw runtime_error(string("Request too long"));

	cout<<req;
	vector<string> splitted_msg = split(req,"\r\n");
	cout<<"Number of rows: "<<splitted_msg.size()<<endl;
	if(splitted_msg.size()<1)
		throw runtime_error(string("Request wrong format."));

	parseFirstLine(splitted_msg[0]);
	cout<<minor<<major<<endl;

	parseRemainingLines(vector<string>(splitted_msg.begin()+1,splitted_msg.end()));

	for(auto x: extraHeaders){
		cout<<x.first<<"=>"<<x.second<<endl;
	}
}

void HttpRequest::parseFirstLine(string& s){
	ostringstream ss(s);
	string http,cEof;

	ss >> method >> uri >> http;

	if(find(acceptedMethods.begin(),acceptedMethods.end(), method) != acceptedMethods.end())
		throw runtime_error(string("Method name is not valid"));

	//if((string("HTTP/").compare(0,5,http) != 0) || http[6]!='.' || !isdigit(http[5]) || !isdigit(http[7]) || !(ss>>cEof))
	if(!regex_match(http, std::regex("HTTP/[0-9].[0-9]") || !(ss>>cEof)))
		throw runtime_error(string("First line is not valid"));

	major = http[5];
	minor = http[7];

}
void HttpRequest::parseHeader(string& s){
	size_t found = s.find(":");
	if(found==string::npos)
		throw runtime_error(string("Extra headers are not valid"));

	extraHeaders.insert(pair<string,string>(s.substr(0,found),s.substr(found+2,s.size()-found)));
}
void HttpRequest::parseRemainingLines(vector<string> vs){
	if(vs.size() == 0)
		return;

	for_each(vs.begin(),vs.end(),parseHeader);

}
string HttpRequest::getResponseMessage(){
	return HttpResponse(200,"OK").getResponseMessage();
}
