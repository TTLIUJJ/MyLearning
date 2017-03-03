#include <iostream>
#include <sys/wait.h>
#include "apue.h"
using namespace std;

int main()
{
	pid_t pid1, pid2;
	
	if((pid1 = fork()) < 0){
		cerr << "Fork1 Error" << endl;
		return -1;
	}
	else if(pid1 == 0){
		if((pid2 = fork()) < 0){
			cerr << "Fork2 Error" << endl;
			return -1;
		}
		else if(pid2 > 0)
			exit(0);

		sleep(20);
		
		cout << "Second Child() = " << getppid() << endl;
	}

	if(waitpid(pid1, NULL, 0) != pid1)
		cerr << "Waitpid Error" << endl;

	return 0;

}
