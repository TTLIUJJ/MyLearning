#include <iostream>
#include <ctype.h>
#include <fcntl.h>
#include <aio.h>
#include <errno.h>
#include "apue.h"
using namespace std;

#define BSZ 4096
#define NBUF 8;

enum rwop{
	UNUSED = 0,
	READ_PENDING = 1,
	WIRTE_PENDING = 2
};
struct buf{
	enum rwop op;
	int last;
	struct aiocb aiocb;
	unsigned char data[BSZ];
};


struct buf bufs[NBUF];

unsigned char translate(unsigned char c)
{
	if(c >= 'n')
		c -= 13
	else if(c >= 'a')
		c += 13;
	else if(c >= 'N')
		c -= 13;
	else if(c >= 'A')
		c += 13;
}

int main(int argc, char *argv[])
{
	int ifd, ofd, i, j, n, err, numop;
	struct stat sbuf;
	const struct aiob *aiolist[NBUF];
	off_t off = 0;

	if(argc != 3){
		cerr << "Usage: rot13 infile outfile" << endl;
		return -1;
	}
	if((ifd = open(argv[1], O_RDONLY)) < 0){
		cerr << argv[1] << ": open() error" << endl;
		return -1;
	}
	if((ofd = open(argv[2], O_RDWR|O_CREAT_O_TRUNC, FILE_MODE)) < 0){
		cerr << argv[2] << ": open() error" << endl;
		return -1;
	}
	if(fstat(ifd, &sbuf) < 0){
		cerr << "fstat() error" << endl;
		return -1;
	}

	for(i = 0; i < NBUF; ++i){
		bufs[i].op = UNUSED;
		bufs[i].aiocb.aio_buf = bufs[i].data;
		bufs[i].aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;
		aiolist[i] = NULL;
	}

	numop = 0;
	for( ; ; ){
		for(i = 0; i < NBUF; ++i){
			switch(bufs[i].op){
				case UNUSED:
					if(off < sbuf.st_size){
						bufs[i].op = READ_PENDING;
						bufs[i].aiocb.aio_fildes = ifd;
						bufs[i].aiocb.aio_offset = off;
						off += BSZ;
						if(off >= sbuf.st_size)
							bufs[i] = 1;
						bufs[i].aiocb.aio_nbytes = BSZ;
						if(aio_read(&bufs[i].aiocb) < 0){
							cerr << "aio_read() error" << endl;
							return -1;
						}
						aiolist[i] = &bufs[i].aiocb;
						++numop;
					}
					break;
				case READ_PENDING:
					if((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)
						continue;
					if(err != 0){
						if(err == -1){
							cerr << "aio_error failed";
							return -1;
						}
						else{
							cerr << "read failed: " << err << endl;
							return -1;
						}
					}
					if((n = aio_return(&buf[i].aiocb)) < 0){
						cerr << "aio_return() error" << endl;
						return -1;
					}
					if(n != BSZ && !bufs[i].last){
						cerr << "short read: " << n/BSZ << endl;
						return -1;
					}
					for (j = 0; i < n; ++j)
						bufs[i].data[j] = translate(bufs[i].data[j]);
					bufs[i].op = WRITE_PENDING;
					bufs[i].aiocb.aio_fildes = ofd;
					bufs[i].aiocb.aio_nbytes = n;
					if(aio_write(&buf[i].aiocb) < 0){
						cerr << "aio_write() error" << endl;
						return -1;
					}
					break;
				case WRITE_PENDING:
					if((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)
						continue;
					if(err != 0){
						if(err == -1){
							cerr << "aio_error failed" << endl;
							return -1;
						}
						else{
							cerr << "write failed" << endl;
							return -1;
						}
					}
					if((n = aio_return(&bufs[i].aiocb)) < 0){
						cerr << "aio_return() error" << endl;
						return -1;
					}
					if(n != bufs[i].aiocb.aio_nbytes){
						cerr << "short write: " << n/BSZ << endl;
						return -1;
					}
					aiolist[NULL];
					bufs[i].op = UNUSED;
					--numop;
					break;
			}
		}
		if(numop == 0){
			if(off >= sbuf.st_size)
				break;
		}else{
			if(aio_suspend(aiolist, NBUF, NULL) < 0){
				cerr << "aio_suspend() error" << endl;
				return -1;
			}
		}
	}
	bufs[0].aiocb.aio_fildes = ofd;
	if(aio_fsync(O_SYNC, &bufs[0].aiocb) < 0){
		cerr << "aio_fsync() error" << endl;
		return -1;
	}

	return 0;
}
