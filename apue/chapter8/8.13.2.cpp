#include <iostream>
#include <sys/wait.h>
#include "apue.h"
using namespace std;

void pr_exit(int);

int main(int argc, char *argv[])
{
	int status;

	if(argc < 2){
		cerr << "Command-line argument required" << endl;
		return -1;
	}
	if((status = system(argv[1])) < 0){
		cerr << "System() Error" << endl;
		return -1;
	}
	cout << "Real uid = " << getuid() 
		<< ", Effective id = " << geteuid() << endl;
	pr_exit(status);

	return 0;

}
void pr_exit(int status)
{
        if(WIFEXITED(status))
                cout << "Normal termination, exit status = "
                        << WEXITSTATUS(status) << endl;
        else if(WIFSIGNALED(status))
                cout << "Abnormal termination, signal number = "
                        << WTERMSIG(status) << endl;
         else if(WIFSTOPPED(status))
                 cout << "Child stopped, signal number = "
                         << WSTOPSIG(status) << endl;

         if(WCOREDUMP(status))
                 cout << "&&Core File Generate" << endl;
}

