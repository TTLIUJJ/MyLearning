#include <iostream>
#include "apue.h"
using namespace std;

static void sig_quit(int);

int main()
{
	sigset_t newmask, oldmask, pendmask;

	if(signal(SIGQUIT, sig_quit) < SIG_ERR){
		cerr << "main: signal() error, can't catch SIGQUIT" << endl;
		return -1;
	}
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		cerr << "sigprocmask() error" << endl;
		return -1;
	}
	
	sleep(5);
	
	if(sigpending(&pendmask) < 0){
		cerr << "sigpending() error" << endl;
		return -1;
	}
	if(sigismember(&pendmask, SIGQUIT) < 0)
		cout << "\nSIGQUIT pending" << endl;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		cerr << "sigprocmask() oldmask" << endl;
		return -1;
	}
	cout << "SIGQUIT unblocked" << endl;

	sleep(5);

	return 0;
}

static void sig_quit(int signo)
{
	cout << "Caught SIGQUIT" << endl;
	if(signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		cerr << "sig_quit: signal() error" << endl;
}	

