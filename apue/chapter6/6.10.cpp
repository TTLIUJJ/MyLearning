#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main()
{
	time_t t;
	struct tm *temp;
	char buf1[64];
	char buf2[64];

	time(&t);
	temp = localtime(&t);
	if(strftime(buf1, 64, "time and date: %r, %a %b %d %Y", temp) == 0)
		cerr << "Strftime Error" << endl;
	else
		cout << buf1 << endl;

	return 0;
}
