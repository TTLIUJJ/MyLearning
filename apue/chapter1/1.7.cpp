#include <iostream>
#include <errno.h>
#include <string.h>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	return 0;
}
