#include "../include/HttpResponse.h"
extern const int MINOR = 1;
extern const int MAJOR = 1;
string HttpResponse::getResponseMessage(){
	ostringstream ss;
	ss << "HTTP/" << MAJOR<<"."<<MINOR<<" ";
	ss << status << " " << reason_phrase << "\r\n";

	return ss.str();
}
