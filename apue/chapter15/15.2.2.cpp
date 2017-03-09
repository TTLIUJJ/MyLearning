#include <iostream>
#include <sys/wait.h>
#include "apue.h"
using namespace std;

#define DEF_PAGER "bin/more"

int main(int argc, char *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char *pager, argv0;
	char line[MAXLINE];
	FILE *fp;

	if(argc != 2){
		cerr << "Usage: a.out <pathname>" << endl;
		return -1;
	}

	if((fp = fopen(argv[1], "r")) == NULL){
		cerr << "fopen() error for " << argv[1] << endl;
	       	return -1;
	}
	if(pipe(fd) < 0){
		cerr << "pipe() error" << endl;
		return -1;
	}
	else if(pid > 0){
		close(fd[0]);
		while(fgets(line, MAXLINE, fp) != NULL){
			n = strlen(line);
			if(write(fd[1], line, n) != n){
				cerr << "write() error" << endl;
				return -1;
			}
		}
		if(ferror(fp)){
			cerr << "ferror() error" << endl;
			return -1;
		}

		close(fd[1]);

		if(waitpid(pid, NULL, 0) < 0){
			cerr << "waitpid" << endl;
			return -1;
		}

		return 0;
	}
	else{
		close(fd[1]);
		if(fd[0] != STDIN_FILENO){
			if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO){
				cerr << "dup2() error for stdin" << endl;
				return -1;
			}
			close(fd[0]);
		}
		
		if((pager = getenv("PARGER")) == NULL)
			pager = DEF_PAGER;
		if((argv0 = strrchr(pager, '/')) != NULL)
			++argv0;
		else 
			argv0 = pager;

		if(excel(parge, argv0, (char *)0) < 0){
			cerr << "excel() error" << endl;
			return -1;
		}
	}
	return 0;
}
