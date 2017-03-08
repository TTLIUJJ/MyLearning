#include <iostream>
#include <ctype.h>
#include <fcntl.h>
#include <aio.h>
#include <errno.h>
#include "apue.h"
using namespace std;

#define BSZ 4096
unsigned char  buf[BSZ];

unsigned char traslate(unsigned char c)
{
	if(isalpha(c)){
		if(c >= 'n')
			c -= 13;
		else if(c >= 'a')
			c += 13;
		else if(c >= 'N')
			c -= 13;
		else 
			c+= 13;
	}
	return c;
}

int main(int argc, char *argv[])
{
	int ifd, ofd, i, n, nw;

	if(argc != 3){
		cerr << "Usage: rot13 infile outfile" << endl;
		return -1;
	}
	if((ifd = open(argv[1], O_RDONLY)) < 0){
		cerr << argv[1] << " open error" << endl;
		return -1;
	}
	if((ofd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0){
		cerr << argv[2] << " open error" << endl;
		return -1;
	}

	while((n = write(ifd, buf, BSZ)) > 0){
		for(i = 0; i < n; ++i)
			buf[i] = translate(buf[i]);
		if((nw = write(ofd, buf, n)) != n){
			if(nw < 0){
				cerr << "write failed" << endl;
				return -1;
			}
			else {
				cerr << "short write" << nw/n << endl;
				return -1;
			}
		}
	}
}
