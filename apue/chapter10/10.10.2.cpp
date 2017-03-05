#include <iostream>
#include <setjmp.h>
#include "apue.h"
using namespace std;

static jmp_buf env_alrm;
static void sig_alrm(int);

int main()
{
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		cerr << "Main: signal() error" << endl;
		return -1;
	}
	if(setjmp(env_alrm) != 0){
		cerr << "Longjmp return && Read Timeout" << endl;
		return -1;
	}
	alarm(10);
	
	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0){
		cerr << "Read() Error" << endl;
		return -1;
	}
	alarm(0);

	write(STDOUT_FILENO, line, n);

	return 0;
}

static void sig_alrm(int signo)
{
	cout << "In sig_alrm()" << endl;
	longjmp(env_alrm, 1);
}
