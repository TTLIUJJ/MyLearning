#include <iostream>
#include <fcntl.h>
#include "apue.h"
using namespace std;
int main()
{
	if(open("tempfile", O_RDWR) < 0){
		cerr << "Open error for tempfile" << endl;
		return -1;
	}
	if(unlink("tempfile") < 0){
		cerr << "Unlink error for tempfile" << endl;
		return -1;
	}
	cout << "Unlink file" << endl;
	sleep(5);
	cout << "Done!!!" <<endl;
	return 0;		
}
