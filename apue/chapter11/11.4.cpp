#include <iostream>
#include <pthread.h>
#include "apue.h"
#include <iomanip>
#include <string>
using namespace std;

pthread_t ntid;
void printids(const string &);
void* thr_fn(void*);

int main()
{
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if(err != 0)
		cerr << "pthread_create() error" << endl;
	printids(string("main thread"));
	sleep(1);

	return 0;
}

void printids(const string &str)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	cout << str << ": pid = " << pid << ", tid = " << tid 
		<< hex <<", "<< tid <<endl;
}
void* thr_fn(void*)
{
	printids(string("new thread"));
	return ((void*)0);
}
