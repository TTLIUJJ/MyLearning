#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sys/times.h>
#include "apue.h"
using namespace std;

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(const string&);
int main(int argc, char *argv[])
{
	int i;

	cout << unitbuf;
	for(i = 1; i < argc; ++i)
		do_cmd(argv[i]);

	return 0;
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
	static long clktck = 0;

	if(clktck == 0)
		if((clktck = sysconf(_SC_CLK_TCK)) < 0){
			cerr << "Sysconf Error" << endl;
			return ;
		}
	cout << setw(10) << setprecision(2) 
	     << "       real: " << static_cast<double>(real) / clktck << "\n";
	cout << "       user: " << (tmsend->tms_utime - tmsstart->tms_utime)/
				static_cast<double>(clktck) << "\n";
	cout << "        sys: " << (tmsend->tms_stime - tmsstart->tms_stime)/
				static_cast<double>(clktck) << "\n";
	cout << " child user: " << (tmsend->tms_cutime - tmsstart->tms_cutime)/
				static_cast<double>(clktck) << "\n";
	cout << "  child sys: " << (tmsend->tms_cstime - tmsstart->tms_cstime)/
				static_cast<double>(clktck) << "\n";
}
static void do_cmd(const string &cmd)
{
	struct tms tmsstart, tmsend;
	clock_t start, end;
	int status;

	cout << "\n" << "Command: " << cmd << endl;

	if((start = times(&tmsstart)) == -1){
		cerr << "Times1() Error" << endl;
		return ;
	}
	if((status = system(cmd.c_str())) < 0){
		cerr << "System() Error" << endl;
		return ;
	}
	if((end = times(&tmsend)) == -1){
		cerr << "Times2() Error" << endl;
		return ;
	}
	pr_times(end - start, &tmsstart, &tmsend);
}
