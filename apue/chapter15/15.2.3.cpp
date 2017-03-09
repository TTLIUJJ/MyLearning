#include <iostream>
#include "apue.h"
using namespace std;

static int pfd1[2], pfd2[2];

void TELL_WAIT(void)
{
	if(pipe(pfd1) < 0 || pipe(pfd2) < 0){
		cerr << "pipe() error" << endl;
		return;
	}
}

void TELL_PARENT(pid_t pid)
{
	if(write(pfd2[1], "c", 1) != 1){
		cerr << "write() error" << endl;
		return;
	}
}

void WAIT_PARENT(void)
{
	char c;
	
	if(read(pfd1[1], &c, 1) != 1){
		cerr << "read() error" << endl;
		return ;
	}
	if(c != 'p'){
		cerr << "WAIT_PARENT: incorrect data" << endl;
		return;	
	}
}

void TELL_CHILD(pid_t pid)
{
	if(write(pfd1[0], "p", 1) != 1){
		cerr << "write() error" << endl;
		return;
	}
}

void WAIT_CHILD(void)
{
	char c;

	if(read(pfd2[0], &c, 1) != 1){
		cerr << "read() error" << endl;
		return;
	}

	if(c != 'c'){
		cerr << "WAIT_CHILD: incorrect data" << endl;
		return;
	}
}
