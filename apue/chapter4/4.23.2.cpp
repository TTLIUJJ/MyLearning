#include <iostream>
#include <string>
#include "apue.h"
using namespace std;
int main()
{
	char *ptr;
	size_t size = 1024;
	if(chdir("/home/ttlj/code/apue/chapter1") < 0){
		cerr << "Chdir error" << endl;
		return -1;
	}
	if(getcwd(ptr, size) < 0){
		cerr << "Getcwd failded" << endl;
		return -1;
	}
	cout << "cwd = " << ptr << endl;

	return 0;
}

