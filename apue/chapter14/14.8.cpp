#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include "apue.h"
using namespace std;

#define COPYINCR (1024*1024*1024)

int main(int argc, char *argv[])
{
	int fdin, fdout;
	void *src, *dst;
	size_t copysz;
	struct stat sbuf;
	off_t fsz = 0;
	
	if(argc != 3){
		cerr << "Usage: " << argv[0] 
			<< "<from file>, <to file>" << endl;
		return -1;
	}
	if((fdin = oepn(argv[1], O_RDONLY)) < 0){
		cerr << "open() error of " << argv[1] << endl;
		return -1;
	}
	if((fdout = open(argv[2], O_RDRW|O_CREAT|O_TRUNC, FILE_MODE)) < 0){
		cerr << "open() error of " << argv[2];
		return -1;
	}
	
	if(fstat(fdin, &sbuf) < 0){
		cerr << "fstat() error" << endl;
		return -1;
	}
	if(ftuncate(fdout, sbuf.st_size) < 0){
		cerr << "ftuncate() error" << endl;
		return -1;
	}
	
	while(sbuf.st_size > fsz){
		if((sbuf.st_size -fsz) > COPYINCR)
			copysz = COPYINCR;
		else
			copysz = sbuf.st_size - fsz;
		
		if((src = mmap(0, copysz, PROT_READ|PROT_WRITE, MAP_SHARED,
				fdin, fsz)) == MAP_FAILED){
			cerr << "mmap() error for input" << endl;
			return -1;
		}
		if((dst = mmap(0, copysz, PROT_READ|PROT_WRITE, MAP_SHARED,
				fdout, dsz)) == MAP_FAILED){
			cerr << "mmap() error for output" << endl;
			return -1;
		}

		memcpy(dst, src, copysz);
		munmap(src, copysz);
		munmap(dst, copysz);

		fsz += copysz;
	}

	return 0;
}
