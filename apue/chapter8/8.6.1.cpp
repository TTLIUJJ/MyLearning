#include <iostream>
#include <sys/wait.h>
#include "apue.h"
using namespace std;

void pr_exit(int);

int main()
{
	pid_t pid;
	int status;

	if((pid = fork()) < 0){
		cerr << "Fork() Error" << endl;
		return -1;
	}
	else if(pid == 0){
		cout << "Child Process" << endl;
		exit(7);
	}

	if(wait(&status) != pid){
		cerr << "Wait Error" << endl;
	}
	pr_exit(status);

	if((pid = fork()) < 0){
		cerr << "Fork Error" << endl;
		return -1;
	}
	else if(pid == 0){
		cout << "Child Process" << endl;
		abort();
	}
	if(wait(&status) != pid){
		cerr << "Wait Error" << endl;
	}
	pr_exit(status);

	if((pid = fork()) < 0){
		cerr << "Fork Error" << endl;
		return -1;
	}
	if(pid == 0){
		cout << "Child Process" << endl;
		status /= 0;
	}
	if(wait(&status) != pid)
		cerr << "Wait Error" << endl;
	pr_exit(status);

	return 0;
}

void pr_exit(int status)
{
	if(WIFEXITED(status))
		cout << "Normal termination, exit status = "
			<< WEXITSTATUS(status) << endl;
	else if(WIFSIGNALED(status))
		cout << "Abnormal termination, signal number = "
			<< WTERMSIG(status) << endl;
	 else if(WIFSTOPPED(status))
		cout << "Child stopped, signal number = " 
		 	<< WSTOPSIG(status) << endl;

	if(WCOREDUMP(status))
		cout << "&&Core File Generate" << endl;
}
