#include <iostream>
#include <pthread.h>
#include <string>
#include "apue.h"
using namespace std;

//void cleanup(const string *arg);
int* thr_fn1(int *arg);
int* thr_fn2(int *arg);

int main()
{
	pthread_t tid1, tid2;
	int err;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL)
		cerr << "create error of 1" << endl;
}

void cleanup(const string *arg)
{
	cout << "cleanup(): " << *arg << endl;
}

int* thr_fn1(int *arg)
{
	cout << "thread 1 start" << endl;
	thread_cleanup_push(cleanup, string("thread 1 first handler"));
	thread_cleanup_push(cleanup, string("thread 1 second handler"));
	cout << "thread 1 push complete!" << endl;
	
//	pthread_cleanup_pop(0);
//	pthread_cleanup_pop(0);

	return (int *)1;
}
