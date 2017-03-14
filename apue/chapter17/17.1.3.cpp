#include <iostream>
#include "apue.h"
#include <sys/msg.h>
using namespace std;

#define MAXMSZ 512

struct mymesg{
	long mtype;
	char mtext[MAXMSZ];
};

int main(int argc, char *argv[])
{
	key_t key;
	long qid;
	size_t nbytes;
	struct mymesg m;

	if(argc != 3){
		cerr << "usage: sendmsg KEY message" << endl;
		return -1;
	}
	key = strtol(argv[1], NULL, 0);
	if((qid = msgget(key, 0)) < 0){
		cerr << "msgget error" << endl;
		return -1;
	}

}
