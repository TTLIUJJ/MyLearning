#include <iostream>
#include "apue.h"
using namespace std;
const int BSZ = 48;
int main()
{
	FILE *fp;
	char buf[BSZ];

	memset(buf, 'a', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	if((fp = fmemopen(buf, BSZ, "w+")) == NULL){
		cerr << "Fmemopen Error" << endl;
		return -1;
	}
	cout << "Initial buffer contents: " << buf << endl;
	fprintf(fp, "Hello World");
	cout << "Before flush: " << buf << endl;
	fflush(fp);
	cout << "After flush: " << buf << endl;
	cout << "Length of buf: " << strlen(buf) << endl;
	
	memset(buf, 'b', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "hello world!!!");
	fseek(fp, 0, SEEK_SET);
	cout << "After fseek: " << buf << endl;
	cout << "Length of buf: " << strlen(buf) << endl;
	
	memset(buf, 'c', BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp, "Hello World***");
	fclose(fp);
	cout << "After fclose: " << buf << endl;
	cout << "Length of buf: " << strlen(buf) << endl;

	return 0;
}
