#include <iostream>
#include <fcntl.h>
#include "apue.h"
using namespace std;
void set_fl(int fd, int flags)
{
	int val;
	if((val = fcntl(fd, F_GETFL, 0)) < 0)
		cerr << "FCNTL_GET_ERROR" << endl;
	val |= flags;
	if(fcntl(fd, F_SETFL, val) < 0)
		cerr << "FCNTL_SET_ERROR" << endl;
}
