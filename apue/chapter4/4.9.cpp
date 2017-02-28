#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	struct stat statbuf;
	if(stat("foo", &statbuf) < 0){
		cerr << "Stat error for foo" << endl;
		return -1;
	}
	if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0){
		cerr << "Chmod error for foo" << endl;
		return -1;
	}
	if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0){
		cerr << "Chmod error for bar" << endl;
		return -1;
	}
	
	return 0;
}
