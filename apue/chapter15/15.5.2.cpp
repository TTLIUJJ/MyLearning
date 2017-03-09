#include <iostream>
#include "apue.h"

static void sig_pipe(int)
{
	cout << "SIGPIPE caught" << endl;
}

static int _err(const char *s)
{
	cout << s << endl;
	return -1;
}

int main()
{
	int n, fd1[2], fd[2];
	pid_t pid;
	char line[MAXLINE];

	if(signal(SIGPIPE, sig_pipe) == SIG_ERR)
		_err("signal() error");
	if(pipe(fd1) < 0 || pipe(fd2) < 0)
		_err("pipe() error");
	if((pid = fork()) < 0)
		_err("fork() error");
	else if(pid > 0){
		close(fd1[0]);
		close(fd2[1]);

		while(fgets(line, MAXLINE, stdin) != NULL){
			n = strlen(line);
			if(write(fd1[1], line, n) != n)
				_err("write() error");
			if((n = read(fd2[0], line, MAXLINE)) < 0)
				_err("read() error");
			if(n == 0){
				cerr << "Child Closed pipe" << endl;
				break;
			}
			line[n] = 0;
			if(fputs(line, stdout) == EOF)
				_err("fputs() error");
		}
		if(ferror(stdin))
			_err("ferror on stdin");
		return 0;
	}
	else{
		close(fd1[1]);
		close(fd2[0]);
		if(fd1[0] != STDIN_FILENO){
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				_err("dup2() error");
			close(fd1[0]);
		}
		if(excel("./15.4.1.cpp", "15.4.2.cpp", (char *)0) < 0)
			_err("execl() error");
	}
	return 0;
}
