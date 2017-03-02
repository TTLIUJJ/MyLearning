//setjmp and longjmp do not support C++ object semantics
#include <iostream>
#include "apue.h"
#include <setjmp.h>
using namespace std;

const int TOK_ADD = 5;
void do_line(char *);
void cmd_add();
int get_token();

__jmp_buf jmpbuff;
int main()
{
	char line[MAXLINE];
	
	if(_setjmp(jmpbuff) != 0){
		cerr << "Setjmp Error" << endl;
		return -1;
	}
	while(fgets(line, MAXLINE, stdin) != NULL)
		do_line(line);
	exit(0);
}
char *tok_ptr;
void do_line(char *ptr)
{
	int cmd;

	tok_ptr = ptr;
	if((cmd = get_token()) != 0){
		switch(cmd){
			case TOK_ADD:
				cmd_add();
				break;
			default:
				break;
		}
	}
}

void cmd_add()
{
	int token;
	token = get_token();
	if(token < 0)
		longjmp(jmpbuff, 1);
	cout << "Cmd_add(): " << tok_ptr <<endl;
}
int get_token()
{
	int token;
	cin >> token;
	return token;
}

