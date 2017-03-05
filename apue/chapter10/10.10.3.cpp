#include <iostream>
#include "apue.h"
#include <setjmp.h>
#include <unistd.h>
using namespace std;

static jmp_buf env_alrm;
static void sig_alrm(int);
static void sig_int(int);
static unsigned int sleep2(unsigned int);

int main()
{
	unsigned int unslept = 0;

	if(signal(SIGINT, sig_int) == SIG_ERR){
		cerr << "main: signal() error" << endl;
		return -1;
	}
	unslept = sleep2(5);
	cout << "sleep2 returned " << unslept << " seconds" << endl;
	return 0;
}
static void sig_alrm(int)
{
	longjmp(env_alrm, 1);
}
static void sig_int(int)
{
	int i, j;
	volatile int k;

	cout << "\nsig_int starting" << endl;

	for(i = 0; i < 99999; ++i)
		for(j = 0; j < 99999; ++j)
			k += i * j;
	cout << "sig_int finished" << endl;
}
static unsigned int sleep2(unsigned int seconds)
{
	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		cerr << "sleep2: signal() error" << endl;
		return -1;
	}
	if(setjmp(env_alrm) == 0){
		alarm(seconds);
		pause();
	}
	return (alarm(0));
}

