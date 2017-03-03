#include <iostream>
#include <string>
#include "apue.h"
using namespace std;

static void charatatime( char *);
static void stringtime(const string&);

int main()
{
	pid_t pid;

	if((pid = fork()) < 0){
		cerr << "Fork() Error" << endl;
		return -1;
	}
	else if(pid == 0){
		char str[] = "Chilid Process of Char";
		charatatime(str);
		stringtime("Child Process of String");
	}
	else{
		char str[] = "Parent Process of Char";
		charatatime(str);
		stringtime("Parent Process of String");
	}
}

static void charatatime( char *str)
{
	char *ptr;
	int c;

	setbuf(stdout, NULL);
	for(ptr = str; (c = *ptr) != 0; ++ptr)
		putc(c, stdout);
	cout << endl;
}

static void stringtime(const string& str)
{
	size_t size = str.size();

	for(size_t i = 0; i < size; ++i)
		cout << str[i] << flush;
	cout << endl;
}
