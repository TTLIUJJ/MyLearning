#include <iostream>
#include <errno.h>
#include "apue.h"
using namespace std;

int make_temp(char *);

int main()
{
	char tempname[] = "/home/XXXXXX";
	char tempname2[] = "/home/dirXXXXXX";
	cout << "Tring to create first temp file" << endl;
	make_temp(tempname);
	cout << "Tring to cerate second temp file" << endl;
	make_temp(tempname2);

	return 0;

}

int make_temp(char *tempname)
{
	int fd;
	struct stat sbuf;
	
	if((fd = mkstemp(tempname)) < 0){
		cerr << "Mkstemp() Error" << endl;
		return -1;
	}
	cout << "Temp file name: " << tempname << endl;
	close(fd);
	if(stat(tempname, &sbuf) < 0){
		if(errno == ENOENT)
			cerr << "File doesn't exist" << endl;
		else{
			cerr << "Stat faild" << endl;
			return -1;
		}
	}
	else{
		cout << "File Exist!!!" << endl;
		unlink(tempname);
	}

	return 0;
}

