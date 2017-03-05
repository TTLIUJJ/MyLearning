#include <iostream>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

static jmp_buf env_alrm;
unsigned int sleep2(unsigned int);
static void sig_int(int);
static void sig_alrm(int);

int main()
{
	unsigned int unslept;
	if(signal(SIGINT, sig_int) == SIG_ERR){
		cerr << "main: signal() error" << endl;
		return -1;
	}
	unslept = sleep2(5);
	cout << "sleep2 returned: " << unslept << " seconds" << endl;
	return 0;
}

static void sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int seconds)
{
	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		cout << "sleep2: signal() error" << endl;
		return seconds;
	}
	if(setjmp(env_alrm) == 0){
		alarm(seconds);
		pause();
	}
	return (alarm(0));
}

static void sig_int(int signo)
{
	int i, j;
	volatile int k;

	cout << "\nsig_int starting" << endl;
	for(i = 0; i < 300000; ++i)
		for(j = 0; j < 4000; ++j)
			k += i*j;
	cout << "sig_int finishing" << endl;
}
