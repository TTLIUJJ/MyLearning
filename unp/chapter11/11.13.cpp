#include <iostream>
#include <time.h>
#include "unp.h"
using namespace std;

int tcp_listen(const char *, const char *, socklen_t *);

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t len;
	char buff[MAXLINE];
	time_t ticks;
	struct sockaddr_in cliaddr;

	if(argc != 2){
		cerr << "usage: daytimetcpserv1 <service/port #>" << endl;
		return -1;
	}
	listenfd = tcp_listen(NULL, argv[1], NULL);
	
	for( ; ; ){
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *)&cliaddr, &len);
		char b[MAXLINE];
		cout << "connection from " << inet_ntop(cliaddr.sin_family, &cliaddr.sin_addr, b, sizeof(b));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));

		close(connfd);
	}
}

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	int listenfd, n;
	const int on = 1;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0){
		cerr << "tcp_listen error for " << host << ", " << serv << ": " << gai_strerror(n) << endl;
		return -1;
	}
	ressave = res;

	do{
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(listenfd < 0)
			continue;
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;

		close(listenfd);
	}while((res = res->ai_next) != NULL);

	if(res == NULL){
		cerr << "tcp_listen error for " << host << ", " << serv << endl;
		return -1;	
	}
	listen(listenfd, LISTENQ);

	if(addrlenp){
		*addrlenp = res->ai_addrlen;
	}
	
	freeaddrinfo(ressave);

	return listenfd;
}
