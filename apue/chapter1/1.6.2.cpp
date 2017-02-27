#include <iostream>
#include "apue.h"
#include <sys/wait.h>
using namespace std;
int main()
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	cout<<"%";
	while(fgets(buf, MAXLINE, stdin) != NULL){
		if(buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = 0;
	
		if((pid = fork()) < 0)
			cerr<<"fork error"<<endl;
		else if(pid == 0){
			execlp(buf, buf, (char*)0);
			cerr<<"Counldn't execute"<<buf<<endl;
		}
		if((pid = waitpid(pid, &status, 0)) < 0)
			cerr<<"waitpid error"<<endl;
		cout<<"%";
	}
	return 0;
}
