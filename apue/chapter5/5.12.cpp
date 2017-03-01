#include <iostream>
#include "apue.h"
using namespace std;
void pr_stdio(const char *, FILE *);
int  is_unbuffered(FILE *);
int  is_linebuffered(FILE *);
int  buffer_size(FILE *);

int main()
{
	FILE *fp;

	cout << "Enter any character." << endl;
	if(getchar() == EOF){
		cerr << "Getchar Error" << endl;
		return -1;
	}
	cerr << "one line to standard error" << endl;
	
	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if((fp = fopen("test", "r")) == NULL){
		cerr << "Fopen Error" << endl;
		return -1;
	}
	if(getc(fp) == EOF){
		cerr << "Getc() Error" << endl;
		return -1;
	}
	pr_stdio("test", fp);

	return 0;
}

void pr_stdio(const char *name, FILE *fp)
{
	cout << "stream = " << name;
	if(is_unbuffered(fp))
		cout << " unbuffered";
	else if(is_linebuffered(fp))
		cout << " linebuffered";
	else
		cout << " fully buffered";
	cout << ", buffsize = " << buffer_size(fp) << endl;
}
#if defined(_IO_UNBUFFERED)
int is_unbuffered(FILE *fp)
{
	return (fp->_flags & _IO_UNBUFFERED);
}
int is_linebuffered(FILE *fp)
{
	return (fp->_flags & _IO_LINE_BUF);
}
int buffer_size(FILE *fp)
{
	return (fp->_IO_buf_end - fp->_IO_buf_base);
}
#elif defined(_SNBF)
int is_unbuffered(FILE *fp)
{
	return (fp->_flags & __SNBF);
}
int is_linebuffered(FILE *fp)
{
	return (fp->_flags & __SLBF);
}
int buffer_size(FILE *fp)
{
	return (fp->bf._size);
}

#elif defined(_IONBF)
#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif

int is_unbuffered(FILE *fp)
{
	return (fp->_flag & _IONBF);
}	
int is_linebuffered(FILE *fp)
{
	return (fp->_flag & _IOLBF);
}
int buffer_size(FILE *fp)
{
#ifdef _LP64
	return (fp->_base - fp->_ptr);
#else
	return (BUFSIZ);
#endif
}

#else
#error unknown stdio implementation!
#endif
