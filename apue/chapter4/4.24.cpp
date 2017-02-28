#include <iostream>
#include <sys/sysmacros.h>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	for(i = 1; i < argc; ++i){
		cout << argv[i] << " ";
		if(stat(argv[i], &buf) < 0){
			cerr << "Stat error" << endl;
			continue;
		}
		cout << "dev = " << major(buf.st_dev) 
			<<  "/"<< minor(buf.st_dev)<<endl;
		if(S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
			cout << "rdev = " 
			 << (S_ISCHR(buf.st_mode) ? "character" : "block")
			 << major(buf.st_rdev) << "/"
			 << minor(buf.st_rdev)<<endl;
	}
	return 0;
}
