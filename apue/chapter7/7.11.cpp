#include <iostream>
#include <string>
#include <sys/resource.h>
#include "apue.h"
using namespace std;
inline void doit(string, int);
static void pr_limits(string, int);
int main()
{
	#ifdef RLIMIT_AS
		doit("RLIMIT_AS", RLIMIT_AS);
	#endif
		doit("RLIMIT_CORE", RLIMIT_CORE);
		doit("RLIMIT_CPU", RLIMIT_CPU);
		doit("RLIMIT_DATA", RLIMIT_DATA);
		doit("RLIMIT_DSIZE", RLIMIT_FSIZE);
		doit("RLIMIT_MEMLOCK", RLIMIT_MEMLOCK);
		doit("RLIMIT_MSGQUEUE", RLIMIT_MSGQUEUE);
		doit("RLIMIT_NICE", RLIMIT_NICE);
		doit("RLIMIT_NOFILE", RLIMIT_NOFILE);
		doit("RLIMIT_NPROC", RLIMIT_NPROC);
		doit("RLIMIT_RSS", RLIMIT_RSS);
		doit("RLIMIT_SIGPENDING", RLIMIT_SIGPENDING);
		doit("RLIMIT_STACK", RLIMIT_STACK);
}
inline void doit(string name, int rec)
{
	pr_limits(name, rec);
}
static void pr_limits(string name, int resource)
{
	struct rlimit limit;
	unsigned long long lim;

	if(getrlimit(resource, &limit) < 0){
		cerr << "Getrlimit Error" << endl;
		return;
	}
	printf("%-20s", name.c_str());
	cout << "Soft: ";
	if(limit.rlim_cur == RLIM_INFINITY)
		cout << "(Infinity), ";
      	else{
		lim = limit.rlim_cur;
		printf("%10lld, ", lim);
	}
	cout << "Hard: ";
	if(limit.rlim_max == RLIM_INFINITY)
		cout << "(Infinity), ";
	else{
		lim = limit.rlim_max;
		printf("%10lld, ", lim);
	}	
	cout << endl;
}
