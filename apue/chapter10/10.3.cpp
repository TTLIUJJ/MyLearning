#include <iostream>
#include "apue.h"
using namespace std;

static void sig_usr(int);

int main()
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		cout << "Signal() Error 1" << endl;
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		cout << "Signal() Error 2" << endl;
	for( ; ; )
		pause();
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
		cout << "Received SIGUSR1" << endl;
	else if(signo == SIGUSR2)
		cout << "Received SIGUSR2" << endl;
	else
		cout << "Received signal " << signo << endl;
}
