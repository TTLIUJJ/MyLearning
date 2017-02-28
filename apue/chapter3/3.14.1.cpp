#include <iostream>
#include <fcntl.h>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	int val;
	if (argc != 2)
		cerr << "Usage: a.out<descriptor#>"<<endl;
	if((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
		cerr << "Fcntl error for fd " << argv[1] << endl;
	switch(val & O_ACCMODE){
		case O_RDONLY:
			cout<<"Read Only";
			break;
		case O_WRONLY:
			cout << "Write Only";
			break;
		case O_RDWR:
			cout << "Read & Write";
			break;
		default:
			cerr << "Unknown Acess Mode";
			break;
	}
	if(val & O_APPEND)
		cout << ", append";
	if(val & O_NONBLOCK)
		cout << ", nonblocking";
	if(val & O_SYNC)
		cout << ", synchronous writes";
	if(val & O_FSYNC)
		cout << ", fsynchornous writes";
	cout<<endl;
	return 0;
}
