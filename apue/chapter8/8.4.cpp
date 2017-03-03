#include <iostream>
#include "apue.h"
using namespace std;
int globalvar = 8;

int main()
{
	int var = 88;
	pid_t pid;

	if((pid = vfork()) < 0){
		cerr << "Vfork Error" << endl;
		return -1;
	}
	if(pid == 0){
		cout << "Child Process: ";
		++globalvar;
		++var;
		 cout << "Id = " << getpid() << ", globalvar = " 
			 << globalvar << ", var = " << var << endl;
		exit(0);
	}
	else
		cout << "Parent Process: ";
	
	cout << "Id = " << getpid() << ", globalvar = " << globalvar
	       << ", var = " << var << endl;

	return 0;	
}
