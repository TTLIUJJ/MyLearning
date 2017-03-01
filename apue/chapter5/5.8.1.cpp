#include <iostream>
#include "apue.h"
using namespace std;
int main()
{	
	int c;
	while((c = getc(stdin)) != EOF)
		if(putc(c, stdout) == EOF)
			cerr << "Output Error" << endl;
	if(ferror(stdin))
		cerr << "Input Error" << endl;

	return 0;
}
