#include <string>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <sstream>
using namespace std;

inline bool exists_test3 (const std::string& name) {
  struct stat buffer;
  int a = stat (name.c_str(), &buffer);
  cout<< S_ISDIR(buffer.st_mode)<<"|"<<buffer.st_size<<"|"<<a<<endl;
  perror(NULL);
  return (a==0); 
}	

int main(int argc, char const *argv[])
{	//int a = exists_test3("serverRoot/heldsd.txt");
//cout<<endl<<a;
	if(exists_test3("serverRoot"))
		cout<<"Istnieje taki plik"<<endl;


	return 0;
}