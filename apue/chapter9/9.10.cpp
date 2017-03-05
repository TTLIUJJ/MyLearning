#include <iostream>
#include <errno.h>
#include "apue.h"
using namespace std;

inline void sig_hup(int);
inline void pr_ids(const string &);

int main()
{
	char c;
	pid_t pid;
	
	pr_ids("Parent");
	if((pid = fork()) < 0){
		cerr << "Fork() Error" << endl;
		return -1;
	}
	else if(pid > 0)
		sleep(5);
	else{
		pr_ids("Child");
		signal(SIGHUP, sig_hup);
		kill(getpid(), SIGTSTP);
		pr_ids("Child-2");
		if(read(STDIN_FILENO, &c, 1) != 1)
			cerr << "Read error " << errno
				<< " on controlling TTY" << endl; 
	}
	return 0;
}

inline void sig_hup(int signo)
{
	cout << "SIGHUP received, pid = " << getpid() << "\n";
}	
inline void pr_ids(const string &name)
{
	cout << name  
		<< ": pid = " << getpid() 
		<< ", ppid = " << getppid()
		<< ", pgrp = " << tcgetpgrp(STDIN_FILENO)
		<< endl;	
}
