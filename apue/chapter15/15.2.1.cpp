#include <iostream>
#include "apue.h"
using namespace std;

int main()
{	
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	if(pipe(fd) < 0){
		cerr << "pipe() error" << endl;
		return -1;
	}
	if((pid = fork()) < 0){
		cerr << "fork() error" << endl;
		return -1;
	}
	else if(pid > 0){
		close(fd[0]);
		write(fd[1], "Hello Pipe\n");
	}	
	else{
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}

	return 0;
}
