#include <iostream>
#include <errno.h>
#include <string>
#include <sys/time.h>
#include "apue.h"
using namespace std;

unsigned long long count = 0;
struct timeval end;

void checktime(const string &);

int main(int argc, char *argv[])
{
	pid_t pid;
	string s;
	int nzero, ret;
	int adj = 0;
	
	setbuf(stdout, NULL);
	nzero = sysconf(_SC_NZERO);
	cout << "_SC_NZERO = " << nzero << endl;
	if(argc == 2)
		adj = strtol(argv[1], NULL, 10);
	gettimeofday(&end, NULL);
	end.tv_sec += 10;

	if((pid = fork()) < 0){
		cerr << "Fork() Error" << endl;
		return -1;
	}
	else if(pid == 0){
		s = "Child Process";
		cout << "Current nice value in child is " << nice(0) + nzero
			<<", adjusting by " << adj << endl;
		errno = 0;
		if((ret = nice(adj)) == -1 && errno != 0){
			cerr << "Child Set Scheduling Priority" << endl;
			return -1;
		}
		cout << "Now child nice value is " << ret + nzero << endl;
	}
	else{
		s = "Parent Process";
		cout << "Current nice valu in parent is " << nice(0) + nzero
			<<endl;
	}
	
	if(++count == 0){
		cout << s << " counter wrap." << endl;
		return -1;
	}
	checktime(s);
	

	return 0;
}

void checktime(const string& str)
{
	struct timeval tempval;

	gettimeofday(&tempval, NULL);
	if(tempval.tv_sec >= end.tv_sec && tempval.tv_usec >= end.tv_usec){
		cout << str << ", " << count << endl;
		return;
	}
}
