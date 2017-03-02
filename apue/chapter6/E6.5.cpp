#include <iostream>
#include <time.h>
#include "apue.h"
using namespace std;
int main()
{
	time_t caltime;
	struct tm *temp;
	char line[MAXLINE];

	if(time(&caltime) == -1){
		cerr << "Time Error" << endl;
		return -1;
	}
	if((temp = localtime(&caltime)) == NULL){
		cerr << "Localtime Error" << endl;
		return -1;
	}
	if(strftime(line, MAXLINE, "Date & Time: %a %b %d %X %Z %Y", temp) == 0){
		cerr << "Strftime Error" << endl;
		return -1;
	}
	cout << line << endl;
	return 0;

}
