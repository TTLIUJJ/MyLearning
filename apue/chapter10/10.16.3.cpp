#include <iostream>
#include "apue.h"
using namespace std;

static volatile sig_atomic_t sigflag = 0;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int)
{
	sigflag = 1;
}
void TELL_WAIT()
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR){
		cerr << "TELL_WAIT, signal() error" << endl;
		return -1;
	}
	if(signal(SIGUSR2, sig_usr) == SIG_ERR){
		cerr << "TELL_WAIT, signal() error" << endl;
		return -1;
	}
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigsetadd(&newmask, SIGUSR1);
	sigsetadd(&newmask, SIGUSR2);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		cerr << "TELL_WAIT, sigprocmask() error" << endl;
		return -1;
	}
}

void TELL_PARENT(pid_t pid)
{
	klii(pid, SIGUSR2);
}

void WAIT_PARENT(pid_t pid)
{
	while(sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 1;

	if(sigprocmask(SIG_BLOCK, &oldset, NULL) < 0){
		cerr << "WAIT_PARENT, sigprocmask() error" << endl;
		return -1;
	}
}

void TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void WAIT_CHILD()
{
	while(sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		cerr << "WAIT_CHILD, sigprocmask() error" << endl;
		return -1;
	}
}
