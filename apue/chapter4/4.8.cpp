#include <iostream>
#include <fcntl.h>
#include "apue.h"
using namespace std;
#define RWRWRW (S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP)

int main()
{
	umask(0);
	if(creat("foo", RWRWRW) < 0){
		cerr << "Create error for foo" << endl;
		return -1;
	}	
	umask(S_IRGRP | S_IWGRP);
	if(creat("bar", RWRWRW) < 0){
		cerr << "Create error for bar"<<endl;
		return -1;
	}
	return 0;
}
