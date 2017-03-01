#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	char buf[MAXLINE];

	while(fgets(buf, MAXLINE, stdin) != NULL)
		if(fputs(buf, stdout) == EOF)
			cerr << "Fputs Error" << endl;
	if(ferror(stdin))
		cerr << "Fgets Error" << endl;

	return 0;
}
