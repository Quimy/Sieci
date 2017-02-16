#pragma once
#include <sstream>
#include <string>

using namespace std;

class HttpResponse{

  int status;
  string reason_phrase;
public:
	HttpResponse(int s,string rp):status{s},reason_phrase{rp}{};
	string getResponseMessage();
};