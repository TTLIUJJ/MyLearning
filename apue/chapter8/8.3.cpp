#include <iostream>
#include "apue.h"
using namespace std;

int globalvar = 8;
char buf[] = "A write to stdout.\n";

int main()
{
	int var;
	pid_t pid;

	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1){
		cerr << "Write Error" << endl;
		return -1;
	}
	cout << "Before fork: " << endl;

	if((pid = fork()) < 0){
		cerr << "Fork Error" << endl;
		return -1;
	}
	else if(pid == 0){
		cout << "Child Process: ";
		++globalvar;
		++var;
	}
	else{
		cout << "Parent Process: ";
	}
	cout << "pid = " << getpid() << ", " << "globalvar = "
	      << globalvar << ", " << "var = " << var <<endl;

	return 0;	
}
