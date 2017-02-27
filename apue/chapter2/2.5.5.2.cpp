#include <iostream>
#include <cerrno>
#include <climits>
#include "apue.h"
using namespace std;
#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max()
{
	if(openmax == 0){
		errno = 0;
		if((openmax = sysconf(_SC_OPEN_MAX)) < 0)
			openmax = OPEN_MAX_GUESS;
		else
			cerr<<"sysconf error for _SC_OPEN_MAX"<<endl;
	}
	return (openmax);
}
int main()
{
	return 0;
}
