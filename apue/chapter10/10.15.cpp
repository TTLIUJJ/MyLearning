#include <iostream>
#include <setjmp.h>
#include <time.h>
#include "apue.h"
using namespace std;

static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main()
{
	if(signal(SIGUSR1, sig_usr1) == SIG_ERR){
		cerr << "signal() error of sig_usr1" << endl;
		return -1;
	}
	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		cerr << "signal() error of sig_larm" << endl;
		return -1;
	}
	pr_mask("staring main: ");
	if(sigsetjmp(jmpbuf, 1)){
		pr_mask("ending main: ");

		return 0;
	}
	canjump = 1;

	for(; ;)
		pause();
}

static void sig_usr1(int)
{
	time_t starttime;
	
	if(canjump == 0)
		return;

	pr_mask("starting sig_sur1: ");

	alarm(3);
	starttime = time(NULL);

	for( ; ; )
		if(time(NULL) > starttime+5)
			break;

	pr_mask("finishing sig_sur1: ");

	canjump = 0;
	siglongjmp(jmpbuf, 1);
}
static void sig_alrm(int signo)
{
	pr_mask("in sig_alrm: ");
}
