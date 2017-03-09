#include <iostream>
#include "apue.h"
#include <sys/wait.h>

#define PAGER "${PAGER:-more}"

int main(int argc, char *argv[])
{
	char line[MAXLINE];
	FILE *fpin, *fpout;

	if(argc != 2){
		cerr << "Usage: a.out <pathname>" << endl;
		return -1;
	}

	if(fpin = popen(argv[1], "r") == NULL){
		cerr << "popen() error for fpin" << endl;
		return -1;
	}
	if((fpout = popen(PARGE, "w")) == NULL){
		cerr << "popen() error for fpout" << endl;
		return -1;
	}

	while(fgets(line, MAXLINE, fpin) != NULL){
		if(fputs(line, fpout) == EOF){
			cerr << "fputs() error to pipe" << endl;
			return -1;
		}
	}
	
	if(pclose(fpout) == -1){
		cerr << "pclose() error for fpout" << endl;
		return -1;
	}

	return 0;
}
