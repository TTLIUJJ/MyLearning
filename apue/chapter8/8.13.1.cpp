#include <iostream>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
void pr_exit(int);
int main()
{
	int status;

	if((status = system("date")) < 0){
		cerr << "System()1 Error" << endl;
		return -1;
	}
	pr_exit(status);

	if((status = system("nosuchcommand")) < 0){
		cerr << "System()2 Error" << endl;
		return -1;
	}
	pr_exit(status);

	if((status = system("who; exit 44")) < 0){
		cerr << "System()3 Error" << endl;
		return -1;
	}
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
		cout << "Child stopped, signal number = "			                     	 << WSTOPSIG(status) << endl;
       	if(WCOREDUMP(status))
		cout << "&&Core File Generate" << endl;
}

