#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	int c;
	while((c = getc(stdin)) != EOF)
		if(putc(c, stdout) == EOF)
			cerr<<"output errror"<<endl;
	if(ferror(stdin))
		cerr<<"input error"<<endl;

	return 0;
}
