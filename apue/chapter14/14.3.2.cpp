#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "apue.h"
using namespace std;

int main(int argc, char *argv[])
{
	int fd;
	pid_t pid;
	char buf[5];
	struct stat statbuf;

	if(argc != 2){
		cerr << "usage: " << argv[0] << " filename" << endl;
		return -1;
	}
	if((fd = open(argv[1], O_RDWR|O_CREAT|OTRUNC, FILE_MODE)) < 0){
		cerr << "open() error" << endl;
		return -1;
	}
	if(write(fd, "abcdef", 6) != 6){
		cerr << "write() error" << endl;
		return -1;
	}
	if(fstat(fd, &statbuf) < 0){
		cerr << "fstat() error" << endl;
		return -1;
	}
	if(fchmod(fd, (statbuf.st_mode & ~S_IXGRP)|S_ISGID) < 0){
		cerr << "fchmode() error" << endl;
		return -1;
	}
	
	TELL_WAIT();

	if((pid = fork()) < 0){
		cerr << "forK() error" << endl;
		return -1;
	}else if(pid > 0){
		if(write_lock(fd, 0, SEEK_SET, 0) < 0){
			cerr << "write_lock() error" << endl;
			return -1;
		}

		TELL_CHILD(pid);

		if(waitpid(pid, NULL, 0) < 0){
			cerr << "waitpid() error" << endl;
			return -1;
		}
	}
	else{
		WAIT_PARENT();

		set_fl(fd, O_NONBLOCK);

		if(read_lock(fd, 0, SEEK_SET, 0) != -1){
			cerr << "child: read_locked() succeed" << endl;
		}

		cout << "read_lock of already-locked region returns " << errno;

		if(lseek(fd, 0, SEEK_SET) == -1){
			cerr << "lseek() error" << endl;
			return -1;
		}
		if(read(fd, buf, 2) < 0){
			cerr << "read() faild (mandatory locking works)" << endl;
			return -1;
		}
		else{
			cout << "read() ok!!! no mandatory locking" ;
			cout << "the buf = " << buf << endl;
		}

	}
	return 0;
}
