#include <iostream>
#include "apue.h"
#include <string>
#include <errno.h>
using namespace std;

static void sig_int(int);
static void pr_mask(const string &);

int main()
{
	sigset_t newmask, oldmask, waitmask;
	
	pr_mask(string("Program start: "));

	if(signal(SIGINT, sig_int) == SIG_ERR){
		cerr << "Signal(SIGINT) Error" << endl;
		return -1;
	}
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		cerr << "Sigprocmask() Error" << endl;
		return -1;
	}
	
	pr_mask(string("In critical region: "));

	if(sigsuspend(&waitmask) != -1){
		cerr << "Sigpending() Error" << endl;
		return -1;
	}
	
	pr_mask(string("After return from sigsuspend"));
	
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		cerr << "Procmask(SIG_SETMASK) Error" << endl;
		return -1;
	}

	pr_mask(string("Proram exit: "));

	return 0;
}

static void sig_int(int signo)
{
	pr_mask(string("In sig_int()"));	
}
static void pr_mask(const string &str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0){
		cout << "pr_mask() -sigprocmask() error" << endl;
		return;
	}
	cout << str << endl;
	if(sigismember(&sigset, SIGINT))
		cout << "SIGINT" << endl;
       	if(sigismember(&sigset, SIGQUIT))
		cout << "SIGQUIT" << endl;
	if(sigismember(&sigset, SIGUSR1))
		cout << "SIGSUR1" << endl;
	if(sigismember(&sigset, SIGALRM))
		cout << "SIGALRM" << endl;

	errno = errno_save;	
}
