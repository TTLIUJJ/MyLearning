#include <iostream>
#include <fcntl.h>
#include "apue.h"
using namespace std;

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;

	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lokc.l_len = len;

	return (fcntl(fd, cmd, &lock));
}

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;

	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	if(fcntl(fd, F_GETLK, &lock) < 0){
		cerr << "fcntl() error" << endl;
		exit(-1);
	}

	if(lock.l_type == F_UNLCK)
		return 0;

	return lock.l_pid;
}

static void lockabyte(const string &name, int fd, off_t offset)
{
	if(write_wlock(fd, offset, SEEK_SET, 1) < 0){
		cerr << name << ": write_wlock() error" << endl;
		return -1;
	}
	cout << name << ": got the lock, byte " << offset << endl; 
}

int main()
{
	int fd;
	pid_t pid;

	if((fd = creat("templock", FILE_MODE)) < 0){
		cerr << "creat() error" << endl;
		return -1;
	}
	if(write(fd, "ab", 2) != 2){
		cerr << "write() error" << endl;
		return -1;
	}

	TELL_WAIT();

	if((pid = fork()) < 0){
		cerr << "fork() error" << endl;
		return -1;
	}
	else if(pid == 0){
		lockabyte("child", fd, 0);
		TELL_PARENT(getpid());
		WAIT_PARENT();
		lockabtype("child", fd, 1);
	}
	else{
		lockatype("parent", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}
	exit(0);
}
