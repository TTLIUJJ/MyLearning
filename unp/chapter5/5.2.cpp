#include <iostream>
#include "unp.h"
using namespace std;

void str_echo(int);

int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t clipid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	for( ; ;){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *)&cliaddr, &clilen);
		if((clipid = fork()) == 0){
			close(listenfd);
			str_echo(connfd);
			close(connfd);
			exit(0);
		}
		close(connfd);
	}
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
