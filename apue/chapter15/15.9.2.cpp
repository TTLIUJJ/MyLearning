#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include "apue.h"
#include <string>
using namespace std;

#define NLOOPS 1000
#define SIZE sizeof(long)

static int update(long *ptr)
{
	return (*ptr)++;
}

static int _err(const string& s)
{
	cerr << s << endl;
	return -1;
}

int main()
{
	int fd, i, counter;
	pid_t pid;
	void *area;

	if((fd = open("/dev/zero", O_RDWR)) < 0)
		_err("open() error");
	if((area = mmap(0, SIZE, PROT_READ|PROT_WRITE|MAP_SHARED, fd, 0)) == MAP_FAILD)
		_err("mmap() error");
	close(fd);

	TELL_WAIT();

	if((pid = fork()) < 0)
		_err("fork() error");
	else if(pid > 0){
		for(i = 0; i < NLOOPS; i += 2){
			if(counter = update((long *)area) != i)
				_err("")
		}
	}
}
