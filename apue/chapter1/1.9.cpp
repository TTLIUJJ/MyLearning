#include <iostream>
#include "apue.h"
#include <sys/wait.h>
using namespace std;

static void sig_int(int);

int main()
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	if(signal(SIGINT, sig_int) == SIG_ERR)
		cerr<<"signal error"<<endl;
	cout<<"% ";
	while(fgets(buf,MAXLINE,stdin) != NULL){
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1] =0;
		if((pid = fork()) < 0)
			cerr<<"fork error"<<endl;
		else if(pid == 0){
			execlp(buf, buf, (char*)0);
			cerr<<"Coundn't execute"<<buf<<endl;	
		}
		if((pid = waitpid(pid, &status, 0)) < 0)
			cerr<<"waitpid error"<<endl;
		cout<<"% ";
	}
	return 0;
}
void sig_int(int signo)
{
	cout<<"interrupt\n%";	
}
