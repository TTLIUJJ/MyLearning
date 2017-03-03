#include <iostream>
#include <sys/wait.h>
#include "apue.h"
using namespace std;

char *env_init[] = {"USER=unknown", "PATH/tmp", "NULL"};

int main()
{
	pid_t pid;

	if((pid = fork()) < 0){
		cerr << "Fork() Error" << endl;
		return -1;
	}
	else if(pid == 0){
		if(execle("/bin/echo", "echo", "myargl", "My Arg2",
						(char*)0, env_init) < 0){
			cerr << "Execle() Error" << endl;
			return -1;
		}
	}
	if(wait(pid, NULL, 0) < 0){
		cerr << "Wait() Error" << endl;
		return -1;
	}
	if((pid = fork()) < 0){
		cerr << "Fork2() Error" << endl;
		return -1;
	}
	else if(pid == 0){
		if(execlp("echo", "echo", "only 1 arg", (char*)0) < 0){
			cerr << "Execlp() Error" << endl;
			return -1;
		}
	}

	return 0;
]
