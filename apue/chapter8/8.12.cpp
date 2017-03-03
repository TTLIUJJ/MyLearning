#include <iostream>
#include <sys/wait.h>
#include "apue.h"
using namespace std;

int main()
{
	pid_t pid;

	if((pid = fork()) < 0){
		cerr << "Fork() Error" << endl;
		return -1;
	}
	else if(pid == 0){
		if(execl("/home/ttlj/code/apue/chapter8/xxx", "xxx",
				"ARG1", "ARG2", (char*)0) < 0){
			cerr << "Execl Error" << endl;
			return -1;
		}
	}
	if(waitpid(pid, NULL, 0) < 0){
		cerr << "Waitpid() Error" << endl;
		return -1;
	}

	return 0;
}
