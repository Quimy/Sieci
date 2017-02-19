#include "../include/HeaderInterpreters.h"

string modifiedSinceHeader(string url,string header){
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
    	time_t t = time(0);
    	cout<< seconds <<"|"<<t<<endl;
	return "";
}