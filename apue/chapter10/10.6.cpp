#include <iostream>
#include "apue.h"
#include <pwd.h>
using namespace std;

static void my_alarm(int);

int main()
{
	struct passwd *ptr;

	signal(SIGALRM, my_alarm);
	alarm(1);

	for( ; ; ) {
		if((ptr = getpwnam("bin")) == NULL){
			cerr << "main: Getpwnam() Error" << endl;
			return -1;
		}
		if(strcmp(ptr->pw_name, "bin") != 0){
			cout << "Return value corrupted! pw_name = "
				<< ptr->pw_name << endl;
		}
	}	
}
static void my_alarm(int signo)
{
	struct passwd *rootptr;

	cout << "In singal handler" << endl;
	if((rootptr = getpwnam("root")) == NULL){
		cerr << "Getpwnam() Error" << endl;
		return ;
	}
	alarm(1);
}

