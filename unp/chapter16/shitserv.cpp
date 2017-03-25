#include <iostream>
#include "unp.h"
using namespace std;

void str_echo(int);

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(50000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	for( ; ; ){
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *)&servaddr, &len);
		if(fork() == 0){
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
	size_t n;
	char send[MAXLINE], recv[MAXLINE];

	while((n = read(sockfd, recv, MAXLINE)) > 0){
		switch(recv[0]){
			case '1': strcpy(send, "Micgraddy\r\n");   break;
			case '2': strcpy(send, "Kwaii\r\n");       break;
			case '3': strcpy(send, "Crist Paul\r\n");  break;
		}
		write(sockfd, send, strlen(send));
	}
}
