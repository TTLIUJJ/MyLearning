#include <iostream>
#include <pthread.h>
#include "apue.h"
using namespace std;


pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void)
{
	int err;

	cout << "preparing locks..." << endl;
	if((err == pthread_mutex_lock(&lock1)) != 0)
		cerr << "In prepare() lock1 error" << endl;
	if((err == pthread_mutex_lock(&lock2)) != 0)
		cerr << "In prepare() lock2 error" << endl;
}

void parent(void)
{
	cout << "parent unlocking..." << endl;
	if(pthread_mutex_unlock(&lock1) != 0)
		cerr << "In parent() unlock1 error" << endl;
	if(pthread_mutex_unlock(&lock2) != 0)
		cerr << "In parent() unlock2 error" << endl;
}	

void child(void)
{
	cout << "child unlocking..."<< endl;
	if(pthread_mutex_unlock(&lock1) != 0)
		cerr << "In child() unlock1 error" << endl;
	if(pthread_mutex_unlock(&lock2) != 0)
		cerr << "In child() unlock2 error" << endl;
}

void *thr_fn(void *arg)
{
	cout << "thread started..." << endl;
	pause();
	return 0;
}

int main()
{
	int err;
	pid_t pid;
	pthread_t tid;

	if(pthread_atfork(prepare, parent, child) != 0)
		cerr << "pthread_atfork() error" << endl;
	if(pthread_create(&tid, NULL, thr_fn, 0) < 0)
		cerr << "pthread_create() error" << endl;
	sleep(2);

	cout << "parent about to fork()..." << endl;
	if((pid = fork()) < 0)
		cerr << "fork() error" << endl;
	else if(pid == 0) 
		cout << "child returned from fork()" << endl;
	else
		cout << "parent return from fork()" << endl;

	return 0;
}
