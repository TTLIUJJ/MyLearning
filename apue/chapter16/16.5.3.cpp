#include <iostream>
#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sts/socket.h>
#include <sys/wait.h>
using namespace std;

#define QLEN 10
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void server(int sockfd)
{
	int clfd, status;
	pid_t pid;

	set_cloexec(sockfd);
	for( ; ; ){
		if((clfd = accept(sockfd, NULL, NULL)) < 0){
			syslog(LOG_ERR, "ruptime: accept error: %s", strerror(errno));
			exit(1);
		}
		if((pid = fork()) < 0){
			syslog(LOG_ERR, "ruptimed: fork error: %s", strerror(errno));
			exit(1);
		}
		else if(pid == 0){
			if(dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO ||
					dup2(clfd, STDERR_FILENO) != STDERR_FILENO){
				syslog(LOG_ERR, "ruptimed: unexpected error");
				exit(1);
			}
			close(clfd);
			execl("/usr/bin/uptime", "uptime", (char *)0);
			syslog(LOG_ERR, "ruptimed: unexpected return from exec: %s", strerror(errno));
		}
		else{
			close(clfd);
			waitpid(pid, &status, 0);
		}
	}	
}

int main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int sockfd, err, n;
	char *host;

	if(argc != 1){
		cerr << "usage: ruptimed" << endl;
		return -1;
	}
	if((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;
	if((host = (char *)malloc(n)) == NULL){
		cerr << "malloc() error" << endl;
		return -1;
	}
	if(gethostname(host, n) < 0){
		cerr << "gethostname error" << endl;
		return -1;
	}
	daemonize("ruptime");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0){
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
		exit(1);
	}
	for(aip = ailist; aip != NULL; aip = ailist->next){
		if((sockfd = initservers(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN)) > 0){
			serve(sockfd);
			exit(0);
		}
	}
	exit(1);
}
