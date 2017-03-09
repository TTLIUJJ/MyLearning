#include <iostream>
#include "apue.h"
#include <sys/wait.h>

int main()
{
	char line[MAXLINE];
	FILE *fpin;

	if((fpin = popen("myuclc", "r")) == NULL){
		cerr << "popen() error" << endl;
		return -1;
	}
	for( ; ; ){
		fputs("prompt> ", stdout);
		fflush(stdout);
		if(fgets(line, MAXLINE, fpin) == NULL)
			break;
		if(fputs(line, stdout) == EOF){
			cerr << "fputs() error" << endl;
			return -1;
		}
	}
	if(pclose(fpin) == -1){
		cerr << "pclose() error" << endl;
		return -1;	
	}
	putchar('\n');
	return 0;
}
