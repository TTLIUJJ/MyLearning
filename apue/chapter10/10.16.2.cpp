#include <iostream>
#include "apue.h"
using namespace std;

volatile sig_atomic_t quitflag = 0;
static void sig_int(int);

int main()
{
	sigset_t newmask, oldmask, zeromask;

	if(signal(SIGINT, sig_int) == SIG_ERR){
		cerr << "Signal(INT) Error" << endl;
		return -1;
	}
	if(signal(SIGQUIT, sig_int) == SIG_ERR){
		cerr << "Signal(QUIT) Error" << endl;
		return -1;	
	}

	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask, SIGINT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		cerr << "Sigprocmask() Error" << endl;
		return -1;
	}
	while(quitflag == 0)
		sigsuspend(&zeromask);
	quitflag = 0;
	
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		cerr << "Sigprocmask() Error" << endl;
		return -1;
	}

	return 0;
}

static void sig_int(int signo)
{
	if(signo == SIGINT)
		cout << "\nINTERRPUT" << endl;
	else if(signo == SIGQUIT)
		quitflag = 1;
}


