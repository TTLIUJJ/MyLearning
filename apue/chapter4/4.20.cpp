#include <iostream>
#include <fcntl.h>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	int i, fd;
	struct stat statbuf;
	struct timespec times[2];

	for(i = 1; i < argc; ++i){
		if(stat(argv[i], &statbuf) < 0){
			cerr << argv[i] << " stat error"<< endl;
			continue;
		}
		if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0){
			cerr << "Open error for " << argv[i] << endl;
			continue;
		}
		times[0] = statbuf.st_atim;
		times[1] = statbuf.st_mtim;
		if(futimens(fd, times) < 0){
			cerr << "Futimens error" << endl;
			return -1;
		}
		close(fd);
	}
	return 0;
}
