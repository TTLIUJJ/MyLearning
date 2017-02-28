#include <iostream>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	
	for(i = 1; i < argc; ++i){
		cout << argv[i] << " ";
		if(lstat(argv[i], &buf) < 0){
			cerr << "Lstat Error"<<endl;
			continue;
		}
		if(S_ISREG(buf.st_mode))
			cout << "regular";
		else if(S_ISDIR(buf.st_mode))
			cout << "directory";
		else if(S_ISCHR(buf.st_mode))
			cout << "character special";
		else if(S_ISBLK(buf.st_mode))
			cout << "block special";
		else if(S_ISFIFO(buf.st_mode))
			cout << "fifo";
		else if(S_ISLNK(buf.st_mode))
			cout << "symbolic link";
		else if(S_ISSOCK(buf.st_mode))
			cout << "socket";
		else
			cout << "__unknown mode__";
		cout<<endl;
	}
	return 0;
}
