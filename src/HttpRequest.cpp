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

HttpRequest::HttpRequest(string req){

	vector<string> message_head_and_body = split(req,"\r\n\r\n");
	if(message_head_and_body.size() < 1 || message_head_and_body.size() > 2)
		throw runtime_error(string("Request wrong format."));

	vector<string> splitted_msg = split(message_head_and_body[0],"\r\n");
	cout<<"Number of rows: "<<splitted_msg.size()<<endl;
	if(splitted_msg.size() < 1)
		throw runtime_error(string("Request wrong format."));

	parseFirstLine(splitted_msg[0]);

	parseRemainingLines(vector<string>(splitted_msg.begin()+1,splitted_msg.end()));

	for(auto x: extraHeaders){
		cout<<x.first<<"=>"<<x.second<<endl;
	}
	int is_body=isBody();
	if(is_body>0 && message_head_and_body.size() == 2){
		body = message_head_and_body[1];
		if(body.size()!=is_body)
			throw runtime_error(string("Invalid body length."));
	}

}
int HttpRequest::isBody(){
	map<string,string>::iterator i = extraHeaders.find("Content-Length");
	if (i != extraHeaders.end()) {
		return atoi(i->second.c_str());
	}
	else{
		return -1;
	}
}
void HttpRequest::parseFirstLine(string& s){
	istringstream ss(s);
	string http;

	ss >> methodName >> uri >> http;
	if(!regex_match(http, std::regex("HTTP/[0-9].[0-9]")))
		throw runtime_error(string("First line is not valid"));

	if(uri.find("/.")!= string::npos || uri[0]!='/')
		throw runtime_error(string("Url is not valid"));

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

	for_each(vs.begin(),vs.end(),std::bind(&HttpRequest::parseHeader, this, std::placeholders::_1));

}
string HttpRequest::interpretHeaders(){
	string ret{""};
	map<string,string>::iterator i = extraHeaders.find("If-Modified-Since");
	if (i != extraHeaders.end() && methodName!="HEAD") {
		ret = modifiedSinceHeader(fileStats.st_mtime,i->second);
	}
	i = extraHeaders.find("User-Agent");
	if(i != extraHeaders.end()){
		userAgentHeader(i->second);
	}
	i = extraHeaders.find("Referer");
	if(i != extraHeaders.end()){
		refererHeader(i->second);
	}
	i = extraHeaders.find("From");
	if(i != extraHeaders.end()){
		fromHeader(i->second);
	}
	return ret;
}
string HttpRequest::generateHeaders(){
	string ret;
	auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%a %b %d %H:%M:%S %Y");
    auto str = oss.str();

	ret+="Location: localhost"+uri+"\r\n";
	ret+="Date: +"+str+"\r\n";

	auto tma = *std::localtime(&fileStats.st_mtime);

    std::ostringstream ossa;
    ossa << std::put_time(&tma, "%a %b %d %H:%M:%S %Y");
    auto stra= ossa.str();
    ret+="Last-Modified: "+stra+"\r\n";
	return ret;
}

string HttpRequest::getResponseMessage(){
	string status_line,body_ret,headers;
	string filePath(SERVER_ROOT+uri);
	if(stat (filePath.c_str(), &fileStats)==-1){
		status_line = "404 Not Found";
	}
	else{
		status_line = interpretHeaders();
		if(status_line==""){
			status_line = "200 OK";
			MethodInterface *method = MethodFactory().getMethod(methodName);
			body_ret = method->getResponse(uri,S_ISDIR(fileStats.st_mode));
			if(methodName!="HEAD")
				headers+= "Content-Length: "+std::to_string(body_ret.size())+"\r\n";
		}		
	}
	headers += generateHeaders();
	string to_ret = string("HTTP/")+major+"."+minor+" "+status_line+"\r\n"+ headers;
	if(body_ret==""){
		return  to_ret+"\r\n\r\n";
	}
	else{
		return to_ret+"\r\n"+ body_ret+"\r\n\r\n";
	}
	
}
