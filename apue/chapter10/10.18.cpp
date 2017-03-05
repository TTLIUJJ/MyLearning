#include <iostream>
#include "apue.h"
using namespace std;

static void sig_int(int);
static void sig_child(int);

int main()
{
	if(signal(SIGINT, sig_int) == SIG_ERR)
		cerr << "signal(SIGINT) error" << endl;
	if(signal(SIGCHLD, sig_child) == SIG_ERR)
		cout << "signal(SIGCHLD) error" << endl;
	if(system("/bin/ed") < 0)
		cerr << "system() error" << endl;

	return 0;
}
static void sig_int(int)
{
	cout << "Sig_int()" << endl;
}
static void sig_child(int)
{
	cout << "Sig_child" << endl;
}

