#include <iostream>
#include "apue.h"
#include <ctype.h>
using namespace std;

int main()
{
	int c;

	while((c = getchar()) != EOF){
		if(isupper(c))
			c = tolower(c);
		if(putchar(c) == EOF){
			cerr << "output error"<< endl;
			return -1;
		}
		if(c == '\n')
			fflush(stdout);
	}
	exit(0);
}
