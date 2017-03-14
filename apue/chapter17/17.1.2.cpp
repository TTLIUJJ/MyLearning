#include <iostream>
#include <poll.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include "apue.h"
using namespace std;

#define NQ 3
#define MAXMSG 512
#define KEY 0x123

struct threadinfo{
	int qid;
	int fd;
};

void *helper(void *arg)
{
	int n;
	struct mymesg m;
	struct threadinfo *tip = arg;

	for( ; ; ){
		memset(&m, 0, sizeof(m));
		if((n = msgrcv(tip->qid, &m, MAXMSZ, 0, MSG_NOERROR)) < 0){
			cerr << "msgrcv error" << endl;
			return -1;
		}
		if(write(tip->fd, m.mtext, n) < 0){
			cerr << "write error" << endl;
			return -1;
		}
	}
}

int main()
{
	int i, n, err;
	int fd[2];
	int qid[NQ];
	struct pollfd pfd[NQ];
	struct threadinfo ti[NQ];
	pthread_t tid[NQ];
	char buf[MAXSIZE];

	for(i = 0; i < NQ; ++i){
		if((qid[i] = msgget(KEY+i, IPC_CREAT|0666)) < 0){
			cerr << "msgget error" << endl;
			return -1;
		}
		cout << "queue id " << i << " is " << qid[i] << endl;
		
		if(socketpair(AF_UNIX, SOCK_FGRAM, 0, fd) < 0){
			cerr << "socketpair error" << endl;
			return -1;
		}
		pfd[i].fd = fd[0];
		pfd[i].events = POLLIN;
		ti[i].qid = qid[i];
		ti[i].fd = fd[1];
		
		if((err = pthread_create(&tid[i], NULL, helper. &ti[i])) != 0){
			cerr << "pthread_create error" << endl;
			return -1;
		}
	}

	for( ; ; ){
		if(poll(pfd, NQ, -1) < 0){
			cerr << "poll error" << endl;
			return -1;
		}
		for(i = 0; i < NQ; ++i){
			if(pfd[i].revents & POLLIN){
				if((n = read(pfd[i].fd, buf, sizeof(buf)) < 0){
					cerr << "read error" << endl;
					return -1;
				}
				buf[n] = 0;
				cout << "queue id " << qid[i] << ", message: " << buf << endl; 
			}
		}
	}
	
	exit(0);
}
