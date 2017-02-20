#include "../include/HeaderInterpreters.h"

string modifiedSinceHeader(const time_t mTime,const string header){
		cout<<"Interpretacja nagłówka "<<header<<endl;

		std::istringstream date_s(header);
		struct tm date_c = {};
		date_s >> get_time( &date_c, "%a %b %d %H:%M:%S %Y" );
		time_t seconds = std::mktime( & date_c );
		if (date_s.fail()) {
        	std::cout << "Parse failed\n";
    	} else {
        	std::cout << std::put_time(&date_c, "%c") << '\n';
    	}

    	cout<< seconds <<"|"<<mTime<<endl;
    	if(mTime <= seconds)
    		return "304 Not Modified";
    	else
    		return "";
}
void userAgentHeader(const string ua){
	cout<<"-----------------------------"<<endl;
	cout<<"User-Agent zawiera: "<< ua<<endl;
	cout<<"Używany do celów statystycznych i automatycznego rozpoznawania"<<endl;
	cout<<"-----------------------------"<<endl;
}
void refererHeader(const string ua){
	cout<<"-----------------------------"<<endl;
	cout<<"Referer zawiera: "<< ua<<endl;
	cout<<"Używany do generacji listy powrotnych linków."<<endl;
	cout<<"-----------------------------"<<endl;
}
void fromHeader(const string ua){
	cout<<"-----------------------------"<<endl;
	cout<<"From zawiera: "<< ua<<endl;
	cout<<"Zawiera email klienta."<<endl;
	cout<<"-----------------------------"<<endl;
}

