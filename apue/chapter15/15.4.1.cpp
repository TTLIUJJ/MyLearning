#include <iostream>
#include "apue.h"
using namespace std;

int main()
{
	int n, int1, int2;
	char line[MAXLINE];

	while((n = read(STDIN_FILENO, line, MAXLINE)) > 0){
		line[0] = NULL;
		if(sscanf(line, "%d%d", &int1, &int2) == 2){
			sprinf(line, "%d\n", int1 + int2);
			n = strlen(line);
			if(write(STDOUT_FILENO, line, n) != n){
				cerr << "write() error" << endl;
				return -1;
			}
		}
		else{
			if(write(STDOUT_FILENO, "invalid args\n", 13) != 13){
				cerr << "write() error" << endl;
				return -1;
			}
		}
	}

	exit(0);
}
