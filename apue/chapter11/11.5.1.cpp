#include <iostream>
#include <pthread.h>
#include "apue.h"
using namespace std;

void *thr_fn1(void *arg)
{
	cout << "thread 1 returning" << endl;
	return ((void*)11);
}
void *thr_fn2(void *arg)
{
	cout << "thread 2 returning" << endl;
	return ((void*)22);
}

int main()
{
	int err;
	pthread_t tid1, tid2;
	void *tret;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0)
		cerr << "Pthread_Create() Error" << endl;
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0)
		cerr << "Pthread_Create() Error" << endl;
	
	err = pthread_join(tid1, &tret);
	if(err != 0)
		cerr <<"pthread_join() error" << endl;
	cout << "pthread 1 exit code" << tret << endl;
	
	err = pthread_join(tid2, &tret);
	if(err != 0)
		cerr << "pthread_join() error" << endl;
	cout << "pthread 2 exit code" << tret << endl;

	return 0;
}
