#include <iostream>
#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
using namespace std;

#define BUFLEN 128
#define QLEN 10;
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct *sockaddr, socklen_t, int);

void serve(int sockfd)
{
	int clfd;
	FILE *fp;
	char buf[BUFLEN];

	set_cloexec(sockfd);
	for( ; ; ){
		if((clfd = accept(sockfd, NULL, NULL)) < 0){
			syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(err));
			exit(1);
		}
		set_cloexec(clfd);
		if((fp = popen("/usr/bin/uptime", "r")) == NULL){
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		}
		else{
			while(fgets(buf, BUFLEN, fp) != NULL)
				send(clfd, buf, strlen(buf), 0);
			pclose(fp);
		}
		close(clfd);
	}
}
