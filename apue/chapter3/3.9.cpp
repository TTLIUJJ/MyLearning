#include <iostream>
#include "apue.h"
using namespace std;
const int BUFSIZE = 4096;
int main()
{
	int n;
	char buf[BUFSIZE];

	while((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
		if(write(STDOUT_FILENO, buf, n) != n)
			cerr<<"Wirte Error"<<endl;
	if(n < 0)
		cerr<<"Read Error"<<endl;

	return 0;
}
