#include <iostream>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	int i;
	char **ptr;
	extern char **environ;

	for(i = 0; i < argc; ++i)
		cout << "argv[" << i << "]: " << argv[i] << endl;

	for(ptr = environ; *ptr != 0; ++ptr)
		cout << *ptr << endl;

	return 0;
}
