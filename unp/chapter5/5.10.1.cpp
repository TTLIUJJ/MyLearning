#include <iostream>
#include "unp.h"
using namespace std;

void sig_chld(int);
void str_echo(int);
void str_echo2(int);

int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	signal(SIGCHLD, sig_chld);

	for( ; ; ){
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd, (SA *)&cliaddr, &clilen)) < 0){
			if(errno == EINTR)
				continue;
			else{
				cerr << "accept error" << endl;
				return -1;
			}
		}
		if((childpid = fork()) == 0){
			close(listenfd);
			//str_echo(connfd);
			str_echo2(connfd);
			exit(0);
		}
		close(connfd);
	}
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		cout << "child " << pid << "terminated" << endl;
	return;
}

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n = read(sockfd, buf, MAXLINE)) > 0)
		write(sockfd, buf, n);
	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0){
		cerr << "str_echo: read error" << endl;
		exit(-1);
	}
}

void str_echo2(int sockfd)
{
	long arg1, arg2;
	ssize_t n;
	char line[MAXLINE];

	for( ; ; ){
		if((n = read(sockfd, line, MAXLINE)) == 0)
			return;
		if(sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
			snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
		else
			snprintf(line, sizeof(line), "input error\n");
		n = strlen(line);
		write(sockfd, line, n);
	}
}
